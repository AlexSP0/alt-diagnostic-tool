#ifndef ADTMODELBUILDERSTRATEGYDOMAINDIAG_H
#define ADTMODELBUILDERSTRATEGYDOMAINDIAG_H

#include "../core/treemodelbuilderinterface.h"
#include "adtmodelbuilderstrategyinterface.h"

#include <QString>

class ADTModelBuilderStrategyDomainDiag : public QObject, public ADTModelBuilderStrategyInterface
{
public:
    Q_OBJECT
public:
    ADTModelBuilderStrategyDomainDiag(QString serviceName,
                                      QString path,
                                      QString interfaceName,
                                      TreeModelBuilderInterface *modelBuilder);

public:
    std::unique_ptr<TreeModel> buildModel();

private:
    void buildListOfChecks();

private slots:
    void getStdout(QString line);
    void getSdterr(QString line);

private:
    QString m_dbusServiceName;
    QString m_dbusPath;
    QString m_dbusInterfaceName;

    QString dbusDomainDiagMethodName  = "domain_diag";
    QString dbusSSignalName           = "executor_stdout";
    QString dbusESignalName           = "executor_stderr";
    QString domainDiagListChecksParam = "-l";
    QString checksSection             = "checks";

    QStringList m_listOfChecks;

    std::unique_ptr<TreeModelBuilderInterface> m_treeModelBuilder;
};

#endif // ADTMODELBUILDERSTRATEGYDOMAINDIAG_H
