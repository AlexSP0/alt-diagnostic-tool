#include "domaindiagbuildstrategy.h"

#include <QDBusReply>
#include <QEventLoop>
#include <QJsonObject>
#include <QThread>
#include <QTimer>
#include <qfile.h>
#include <qjsonarray.h>

DomainDiagBuildStrategy::DomainDiagBuildStrategy()
    : m_listOfChecks({})
    , m_dbusConnection(nullptr)
    , m_dbusInterface(nullptr)
{}

DomainDiagBuildStrategy::~DomainDiagBuildStrategy() {}

QJsonDocument DomainDiagBuildStrategy::buildChecks(QString &file,
                                                   QString &checksSection,
                                                   QString &serviceName,
                                                   QString &path,
                                                   QString &interfaceName)
{
    QJsonDocument doc;

    buildListOfChecks(serviceName, path, interfaceName);

    if (m_listOfChecks.size() == 0)
    {
        return doc;
    }

    QJsonObject checks = doc.object();
    QJsonArray arrayOfChecks;

    int i = 0;
    for (QString &currentCommand : m_listOfChecks)
    {
        QJsonObject currentCheck;
        currentCheck["args"]     = "";
        currentCheck["category"] = "";
        currentCheck["command"]  = "domain_diag";
        currentCheck["id"]       = i;
        currentCheck["name"]     = currentCommand;
        currentCheck["args"]     = currentCommand;
        arrayOfChecks.append(currentCheck);
        i++;
    }
    checks[checksSection] = arrayOfChecks;

    doc.setObject(checks);

    return QJsonDocument(checks[checksSection].toArray());
}

QJsonDocument DomainDiagBuildStrategy::buildResolvers(QString &file,
                                                      QString &resolversSection,
                                                      QString &serviceName,
                                                      QString &path,
                                                      QString &interfaceName)
{
    return QJsonDocument();
}

void DomainDiagBuildStrategy::getStdout(QString out)
{
    m_listOfChecks.append(out);
}

void DomainDiagBuildStrategy::getStderr(QString err) {}

void DomainDiagBuildStrategy::buildListOfChecks(QString &serviceName,
                                                QString &path,
                                                QString &interfaceName)
{
    QString dbusMethodName("domain_diag");
    QString dbusSSignalName("executor_stdout");
    QString dbusESignalName("executor_stderr");
    QString listChecksParam("-l");

    m_dbusConnection = std::make_unique<QDBusConnection>(QDBusConnection::systemBus());

    if (!m_dbusConnection.get()->isConnected())
    {
        return;
    }

    m_dbusInterface = std::make_unique<QDBusInterface>(serviceName,
                                                       path,
                                                       interfaceName,
                                                       *m_dbusConnection.get());

    if (!m_dbusInterface.get()->isValid())
    {
        return;
    }

    m_dbusInterface->connection()
        .connect(serviceName, path, interfaceName, dbusSSignalName, this, SLOT(getStdout(QString)));

    m_dbusInterface->connection()
        .connect(serviceName, path, interfaceName, dbusESignalName, this, SLOT(getStderr(QString)));

    QDBusReply<int> reply = m_dbusInterface->call(dbusMethodName, listChecksParam);

    //Wait for all signals
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(100);
    loop.exec();

    //TO DO domain-debug return nonzero exit code, then calling with -l parameter
    if (reply.value() != 0)
    {
        //qWarning() << "Can't get list of checks from DBus!";
    }

    m_dbusInterface->connection().disconnect(serviceName,
                                             path,
                                             interfaceName,
                                             dbusSSignalName,
                                             this,
                                             SLOT(getStdout(QString)));

    m_dbusInterface->connection().disconnect(serviceName,
                                             path,
                                             interfaceName,
                                             dbusESignalName,
                                             this,
                                             SLOT(getStderr(QString)));
}
