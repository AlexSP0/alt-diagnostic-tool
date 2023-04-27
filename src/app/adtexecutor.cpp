#include "adtexecutor.h"

#include <QApplication>
#include <QThread>

ADTExecutor::ADTExecutor(std::vector<StatusCommonWidget *> *vectorWidgets,
                         QString serviceName,
                         QString path,
                         QString intefaceName)
    : d(std::make_unique<ADTExecutorPrivate>(vectorWidgets))
{
    d->serviceName   = serviceName;
    d->path          = path;
    d->interfaceName = intefaceName;
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
        ADTExecutable *currentTask = widget->getExecutable();

        emit beginTask();

        executeTask(currentTask);

        emit finishTask();
    }

    this->moveToThread(QApplication::instance()->thread());

    emit allTasksFinished();

    QThread::currentThread()->quit();

    return;
}

void ADTExecutor::executeTask(ADTExecutable *task)
{
    //No backend
    QThread::sleep(100);
}
