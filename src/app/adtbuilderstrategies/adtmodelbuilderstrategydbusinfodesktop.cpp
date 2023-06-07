#include "adtmodelbuilderstrategydbusinfodesktop.h"

#include <QDBusReply>
#include <QJsonDocument>

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
    return m_treeModelBuilder->buildModel(std::vector<ADTExecutable>{});
}

QStringList ADTModelBuilderStrategyDbusInfoDesktop::getObjectsPathByInterface(QString interface)
{
    QDBusReply<QList<QDBusObjectPath>> reply = m_dbusInterface->call(m_get_method_name, interface);

    QList<QDBusObjectPath> pathList = reply.value();

    QStringList paths;

    std::for_each(pathList.begin(), pathList.end(), [&paths](QDBusObjectPath &path) { paths.append(path.path()); });

    return paths;
}

QJsonDocument ADTModelBuilderStrategyDbusInfoDesktop::getInterfaceInfo(QString path)
{
    return QJsonDocument();
}
