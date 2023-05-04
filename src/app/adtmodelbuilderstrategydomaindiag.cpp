#include "adtmodelbuilderstrategydomaindiag.h"

#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <qdbusconnection.h>

ADTModelBuilderStrategyDomainDiag::ADTModelBuilderStrategyDomainDiag(QString serviceName,
                                                                     QString path,
                                                                     QString interfaceName,
                                                                     TreeModelBuilderInterface *modelBuilder)
    : m_dbusServiceName(serviceName)
    , m_dbusPath(path)
    , m_dbusInterfaceName(interfaceName)
    , m_listOfChecks({})
    , m_treeModelBuilder(modelBuilder)
{}

std::unique_ptr<TreeModel> ADTModelBuilderStrategyDomainDiag::buildModel()
{
    buildListOfChecks();

    if (m_listOfChecks.size() == 0)
    {
        return nullptr;
    }

    QJsonObject checks;
    QJsonArray arrayOfChecks;

    int i = 0;
    for (QString &currentCommand : m_listOfChecks)
    {
        QJsonObject currentCheck;
        currentCommand.chop(1);
        currentCheck["category"] = "domain-diag";
        currentCheck["command"]  = "domain_diag";
        currentCheck["id"]       = i;
        currentCheck["name"]     = currentCommand;
        currentCheck["args"]     = currentCommand;
        arrayOfChecks.append(currentCheck);
        i++;
    }
    checks[checksSection] = arrayOfChecks;

    auto jsonDoc = QJsonDocument(checks[checksSection].toArray());

    return m_treeModelBuilder->buildModel(&jsonDoc);
}

void ADTModelBuilderStrategyDomainDiag::buildListOfChecks()
{
    QDBusConnection dbus = QDBusConnection::systemBus();

    if (!dbus.isConnected())
    {
        qWarning() << "ERROR. Can't connect to DBUS and get list of DomainDiag commands";

        return;
    }

    QDBusInterface dbusInterface(m_dbusServiceName, m_dbusPath, m_dbusInterfaceName, dbus);

    if (!dbusInterface.isValid())
    {
        qWarning() << "ERROR. Can't connect dbus interface and get list of DomainDiag commands";
        return;
    }

    dbusInterface.connection()
        .connect(m_dbusServiceName, m_dbusPath, m_dbusInterfaceName, dbusSSignalName, this, SLOT(getStdout(QString)));

    dbusInterface.connection()
        .connect(m_dbusServiceName, m_dbusPath, m_dbusInterfaceName, dbusESignalName, this, SLOT(getStderr(QString)));

    QDBusReply<int> reply = dbusInterface.call(dbusDomainDiagMethodName, domainDiagListChecksParam);

    //Wait for all signals
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(2000);
    loop.exec();

    dbusInterface.connection().disconnect(m_dbusServiceName,
                                          m_dbusPath,
                                          m_dbusInterfaceName,
                                          dbusSSignalName,
                                          this,
                                          SLOT(getStdout(QString)));

    dbusInterface.connection().disconnect(m_dbusServiceName,
                                          m_dbusPath,
                                          m_dbusInterfaceName,
                                          dbusESignalName,
                                          this,
                                          SLOT(getStderr(QString)));

    if (reply.isValid() && (reply.value() != 0))
    {
        qWarning() << "ERROR! Exit code of dbus reply is nonzero.";

        return;
    }
}

void ADTModelBuilderStrategyDomainDiag::getStdout(QString line)
{
    m_listOfChecks.append(line);
}

void ADTModelBuilderStrategyDomainDiag::getSdterr(QString line) {}
