#include "domaindiagbuildstrategy.h"

#include <QDBusConnection>
#include <QDBusInterface>

DomainDiagBuildStrategy::DomainDiagBuildStrategy() {}

DomainDiagBuildStrategy::~DomainDiagBuildStrategy() {}

QJsonDocument DomainDiagBuildStrategy::buildChecks(QString &file,
                                                   QString &checksSection,
                                                   QString &serviceName,
                                                   QString &path,
                                                   QString &interfaceName)
{
    return QJsonDocument();
}

QJsonDocument DomainDiagBuildStrategy::buildResolvers(QString &file,
                                                      QString &resolversSection,
                                                      QString &serviceName,
                                                      QString &path,
                                                      QString &interfaceName)
{
    return QJsonDocument();
}

QStringList DomainDiagBuildStrategy::getListOfChecks(QString &serviceName,
                                                     QString &path,
                                                     QString &interfaceName)
{
    QDBusConnection dbus = QDBusConnection::systemBus();
    QDBusInterface dbusInterface(serviceName, path, interfaceName, dbus);

    QStringList list;
    return list;
}
