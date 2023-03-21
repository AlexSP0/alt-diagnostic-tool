#ifndef DOMAINDIAGBUILDSTRATEGY_H
#define DOMAINDIAGBUILDSTRATEGY_H

#include "iadtwizardbuilderstrategy.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QJsonDocument>
#include <QString>

class DomainDiagBuildStrategy : public QObject, public IADTWizardBuilderStrategy
{
    Q_OBJECT
public:
    DomainDiagBuildStrategy();
    virtual ~DomainDiagBuildStrategy();

    QJsonDocument buildChecks(QString &file,
                              QString &checksSection,
                              QString &serviceName,
                              QString &path,
                              QString &interfaceName);
    QJsonDocument buildResolvers(QString &file,
                                 QString &resolversSection,
                                 QString &serviceName,
                                 QString &path,
                                 QString &interfaceName);
public slots:
    void getStdout(QString out);
    void getStderr(QString err);

    void buildListOfChecks(QString &serviceName, QString &path, QString &interfaceName);

private:
    QStringList m_listOfChecks;

    std::unique_ptr<QDBusConnection> m_dbusConnection;

    std::unique_ptr<QDBusInterface> m_dbusInterface;
};

#endif // DOMAINDIAGBUILDSTRATEGY_H
