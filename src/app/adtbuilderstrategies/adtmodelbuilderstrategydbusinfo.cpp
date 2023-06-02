#include "adtmodelbuilderstrategydbusinfo.h"

#include <QDBusReply>
#include <QJsonDocument>

ADTModelBuilderStrategyDbusInfo::ADTModelBuilderStrategyDbusInfo(
    QString serviceName, QString path, QString interface, QString getMethodName, QString findInterface)
    : m_serviceName(serviceName)
    , m_path(path)
    , m_interface(interface)
    , m_get_method_name(getMethodName)
    , m_findInterface(findInterface)
    , m_implementedInterfacesPath()
    , m_dbus(new QDBusConnection(QDBusConnection::systemBus()))
    , m_dbusInterface(new QDBusInterface(m_serviceName, m_path, m_interface, *m_dbus.get()))
{}

std::unique_ptr<TreeModel> ADTModelBuilderStrategyDbusInfo::buildModel()
{
    return std::unique_ptr<TreeModel>();
}

QStringList ADTModelBuilderStrategyDbusInfo::getObjectsPathByInterface(QString interface)
{
    QDBusReply<QList<QDBusObjectPath>> reply = m_dbusInterface->call(m_get_method_name, interface);

    QList<QDBusObjectPath> pathList = reply.value();

    QStringList paths;

    std::for_each(pathList.begin(), pathList.end(), [&paths](QDBusObjectPath &path) { paths.append(path.path()); });

    return paths;
}

QJsonDocument ADTModelBuilderStrategyDbusInfo::getInterfaceInfo(QString interface)
{
    QDBusInterface iface(m_serviceName, interface, m_findInterface, *m_dbus.get());

    QDBusReply<QStringList> reply = iface.call("info");

    QStringList infoList = reply.value();

    if (infoList.empty())
    {
        return QJsonDocument();
    }

    QString resultString;

    for (QString line : infoList)
    {
        resultString.append(line);
    }

    QJsonDocument resultDocument = QJsonDocument::fromJson(resultString.toLatin1());

    return resultDocument;
}
