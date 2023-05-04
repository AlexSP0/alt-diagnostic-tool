#include "adtexecutor.h"

#include <QApplication>
#include <QDBusReply>
#include <QThread>
#include <QTimer>

ADTExecutor::ADTExecutor(std::vector<StatusCommonWidget *> *vectorWidgets,
                         QString serviceName,
                         QString path,
                         QString intefaceName)
    : d(std::make_unique<ADTExecutorPrivate>(vectorWidgets))
{
    d->dbusServiceName   = serviceName;
    d->dbusPath          = path;
    d->dbusInterfaceName = intefaceName;
}

int ADTExecutor::getAmountOfWidgets()
{
    return d->widgets->size();
}

void ADTExecutor::cancelTasks()
{
    d->stopFlag = true;
}

void ADTExecutor::resetStopFlag()
{
    d->stopFlag = false;
}

void ADTExecutor::runTasks()
{
    emit allTaskBegin();

    int tasksCount = d->widgets->size();

    if (tasksCount == 0)
    {
        this->moveToThread(QApplication::instance()->thread());

        emit allTasksFinished();

        QThread::currentThread()->quit();

        return;
    }

    for (StatusCommonWidget *widget : *d->widgets)
    {
        if (d->stopFlag)
        {
            break;
        }

        ADTExecutable *currentTask = widget->getExecutable();

        emit beginTask(widget);

        executeTask(currentTask);

        emit finishTask(widget);
    }

    this->moveToThread(QApplication::instance()->thread());

    emit allTasksFinished();

    QThread::currentThread()->quit();
}

void ADTExecutor::executeTask(ADTExecutable *task)
{
    connectExecutableSignals(task);

    QDBusReply<int> reply = d->dbusInterface->call("new_ls", "\"root\"");

    task->m_exit_code = reply.value();

    waitForAnswer(1000);

    //QThread::sleep(1);

    disconnectExecutableSignals(task);
}

void ADTExecutor::connectExecutableSignals(ADTExecutable *task)
{
    d->dbusInterface->connection().connect(d->dbusServiceName,
                                           d->dbusPath,
                                           d->dbusInterfaceName,
                                           d->dbusStdOutSignalName,
                                           task,
                                           SLOT(getStdout(QString)));
    d->dbusInterface->connection().connect(d->dbusServiceName,
                                           d->dbusPath,
                                           d->dbusInterfaceName,
                                           d->dbusStdErrSignalName,
                                           task,
                                           SLOT(getStderr(QString)));
}

void ADTExecutor::disconnectExecutableSignals(ADTExecutable *task)
{
    d->dbusInterface->connection().disconnect(d->dbusServiceName,
                                              d->dbusPath,
                                              d->dbusInterfaceName,
                                              d->dbusStdOutSignalName,
                                              task,
                                              SLOT(getStdout(QString)));

    d->dbusInterface->connection().disconnect(d->dbusServiceName,
                                              d->dbusPath,
                                              d->dbusInterfaceName,
                                              d->dbusStdErrSignalName,
                                              task,
                                              SLOT(getStderr(QString)));
}

void ADTExecutor::waitForAnswer(int mSeconds)
{
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(mSeconds);
    loop.exec();
}
