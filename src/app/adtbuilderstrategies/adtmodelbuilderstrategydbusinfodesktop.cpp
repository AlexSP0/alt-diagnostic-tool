#include "adtmodelbuilderstrategydbusinfodesktop.h"
#include "../core/adtdesktopfileparser.h"

#include <QDBusReply>
#include <QDebug>
#include <QJsonDocument>

const QString ADTModelBuilderStrategyDbusInfoDesktop::LIST_METHOD = QString("list");
const QString ADTModelBuilderStrategyDbusInfoDesktop::INFO_METHOD = QString("info");

ADTModelBuilderStrategyDbusInfoDesktop::ADTModelBuilderStrategyDbusInfoDesktop(QString serviceName,
                                                                               QString path,
                                                                               QString interface,
                                                                               QString getMethodName,
                                                                               QString findInterface,
                                                                               TreeModelBuilderInterface *builder)
    : m_serviceName(serviceName)
    , m_path(path)
    , m_interface(interface)
    , m_get_method_name(getMethodName)
    , m_findInterface(findInterface)
    , m_treeModelBuilder(builder)
    , m_implementedInterfacesPath()
    , m_dbus(new QDBusConnection(QDBusConnection::systemBus()))
    , m_dbusInterface(new QDBusInterface(m_serviceName, m_path, m_interface, *m_dbus.get()))
{}

std::unique_ptr<TreeModel> ADTModelBuilderStrategyDbusInfoDesktop::buildModel()
{
    QStringList listOfObjects = getObjectsPathByInterface(m_findInterface);

    if (listOfObjects.isEmpty())
    {
        return nullptr;
    }

    std::vector<std::unique_ptr<ADTExecutable>> adtExecutables;

    for (QString currentPath : listOfObjects)
    {
        std::vector<std::unique_ptr<ADTExecutable>> currentExecutables = std::move(
            buildADTExecutablesFromDesktopFile(currentPath));
        if (!currentExecutables.empty())
        {
            for (auto &currentExe : currentExecutables)
            {
                adtExecutables.push_back(std::move(currentExe));
            }
        }
    }

    return m_treeModelBuilder->buildModel(std::move(adtExecutables));
}

QStringList ADTModelBuilderStrategyDbusInfoDesktop::getObjectsPathByInterface(QString interface)
{
    QDBusReply<QList<QDBusObjectPath>> reply = m_dbusInterface->call(m_get_method_name, interface);

    QList<QDBusObjectPath> pathList = reply.value();

    QStringList paths;

    std::for_each(pathList.begin(), pathList.end(), [&paths](QDBusObjectPath &path) { paths.append(path.path()); });

    return paths;
}

std::vector<std::unique_ptr<ADTExecutable>> ADTModelBuilderStrategyDbusInfoDesktop::buildADTExecutablesFromDesktopFile(
    QString path)
{
    QDBusInterface iface(m_serviceName, path, m_findInterface, *m_dbus.get());

    QDBusReply<QStringList> testsListReply = iface.call(ADTModelBuilderStrategyDbusInfoDesktop::LIST_METHOD);

    QStringList testsList = testsListReply.value();

    if (testsList.empty())
    {
        qWarning() << "ERROR! Can't get list of tests from object with path: " << path;

        return std::vector<std::unique_ptr<ADTExecutable>>();
    }

    QDBusReply<QStringList> reply = iface.call(ADTModelBuilderStrategyDbusInfoDesktop::INFO_METHOD);

    QStringList infoList = reply.value();

    if (infoList.empty())
    {
        qWarning() << "ERROR! Can't get info from object with path: " << path;

        return std::vector<std::unique_ptr<ADTExecutable>>();
    }

    QString resultString;

    for (QString line : infoList)
    {
        resultString.append(line);
    }

    ADTDesktopFileParser parser(resultString, testsList);

    return parser.buildExecutables();
}
