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
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QThread>
#include <QTimer>
#include <qdbusmessage.h>

class ADTExecutorPrivate
{
public:
    ADTExecutorPrivate()
        : executables()
        , stopFlag(false)
        , waitFlag(false)
        , isRunning(false)
    {}

    ~ADTExecutorPrivate() {}

    std::vector<ADTExecutable *> executables;

    volatile bool stopFlag;
    volatile bool waitFlag;
    volatile bool isRunning;

private:
    ADTExecutorPrivate(const ADTExecutorPrivate &) = delete;
    ADTExecutorPrivate(ADTExecutorPrivate &&)      = delete;
    ADTExecutorPrivate &operator=(const ADTExecutorPrivate &) = delete;
    ADTExecutorPrivate &operator=(ADTExecutorPrivate &&) = delete;
};

ADTExecutor::ADTExecutor()
    : d(new ADTExecutorPrivate)
{}

ADTExecutor::~ADTExecutor()
{
    delete d;
}

int ADTExecutor::getAmountOfExecutables()
{
    return d->executables.size();
}

void ADTExecutor::cancelTasks()
{
    d->stopFlag = true;
}

void ADTExecutor::resetStopFlag()
{
    d->stopFlag = false;
}

void ADTExecutor::wait()
{
    d->waitFlag = true;
}

void ADTExecutor::resetWaitFlag()
{
    d->waitFlag = false;
}

bool ADTExecutor::isRunning()
{
    return d->isRunning;
}

void ADTExecutor::setTasks(std::vector<ADTExecutable *> &tasks)
{
    d->executables.clear();

    d->executables.assign(tasks.begin(), tasks.end());
}

void ADTExecutor::runTasks()
{
    emit allTaskBegin();

    int tasksCount = d->executables.size();

    if (tasksCount == 0)
    {
        this->moveToThread(QApplication::instance()->thread());

        emit allTasksFinished();

        QThread::currentThread()->quit();

        return;
    }

    d->isRunning = true;

    for (ADTExecutable *executable : d->executables)
    {
        if (d->stopFlag)
        {
            break;
        }

        if (d->waitFlag)
        {
            while (true)
            {
                if (d->waitFlag)
                {
                    QThread::currentThread()->yieldCurrentThread();
                }
                else
                {
                    break;
                }
            }
        }

        emit beginTask(executable);

        executeTask(executable);

        emit finishTask(executable);
    }
    d->isRunning = false;

    this->moveToThread(QApplication::instance()->thread());

    emit allTasksFinished();

    QThread::currentThread()->quit();
}

void ADTExecutor::executeTask(ADTExecutable *task)
{
    QDBusConnection dbus(QDBusConnection::systemBus());

    QDBusInterface dbusIface(task->m_dbusServiceName, task->m_dbusPath, task->m_dbusInterfaceName, dbus);

    task->clearReports();

    QDBusMessage reply = dbusIface.call(task->m_dbusRunMethodName, task->m_id);

    if (reply.type() == QDBusMessage::ErrorMessage)
    {
        task->m_exit_code = -1;
        task->m_stringStderr.append(reply.errorMessage());

        return;
    }

    QList<QVariant> replyValues = reply.arguments();

    QStringList report = replyValues.takeFirst().toStringList();

    int exitCode = replyValues.takeFirst().toInt();

    task->m_exit_code = exitCode;

    for (QString &line : report)
    {
        task->m_stringStdout.append(line);
    }
}
