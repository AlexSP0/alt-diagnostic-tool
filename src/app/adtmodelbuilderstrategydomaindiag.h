/***********************************************************************************************************************
**
** Copyright (C) 2023 BaseALT Ltd. <org@basealt.ru>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

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
