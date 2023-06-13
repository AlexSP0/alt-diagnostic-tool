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

    QDBusConnection dbus(QDBusConnection::systemBus());

    QDBusInterface dbusIface(task->m_dbusServiceName, task->m_dbusPath, task->m_dbusInteface, dbus);

    QDBusReply<QStringList> reply = dbusIface.call(task->m_method, task->m_args);

    if (reply.error().type() == QDBusError::NoError)
    {
        task->m_exit_code = 0;

        for (QString &line : reply.value())
        {
            task->m_stringStdout.append(line);
        }
    }
    else
    {
        task->m_exit_code = -1;
        task->m_stringStderr.append(reply.error().message());
    }

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
