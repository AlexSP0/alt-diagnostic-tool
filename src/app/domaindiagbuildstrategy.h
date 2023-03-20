#ifndef DOMAINDIAGBUILDSTRATEGY_H
#define DOMAINDIAGBUILDSTRATEGY_H

#include "iadtwizardbuilderstrategy.h"

#include <QJsonDocument>
#include <QString>

class DomainDiagBuildStrategy : public IADTWizardBuilderStrategy
{
public:
    DomainDiagBuildStrategy();
    ~DomainDiagBuildStrategy();

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

private:
    QJsonDocument loadDocument(QString &file, QString &jsonArrayName);

    QStringList getListOfChecks(QString &serviceName, QString &path, QString &interfaceName);
};

#endif // DOMAINDIAGBUILDSTRATEGY_H
