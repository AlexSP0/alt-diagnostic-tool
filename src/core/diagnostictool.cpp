/***********************************************************************************************************************
**
** Copyright (C) 2022 BaseALT Ltd. <org@basealt.ru>
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

#include "diagnostictool.h"
#include "adtexecutable.h"

#include <QJsonDocument>
#include <QThread>

#include <QtWidgets/QApplication>

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>

DiagnosticTool::DiagnosticTool(QJsonDocument document)
    : d(nullptr)
    , stopFlag(false)
{
    d.reset(new DiagnosticToolPrivate(document));
}

void DiagnosticTool::runChecks()
{
    emit begin();

    int checkSize = d->checks->size();

    if (checkSize == 0)
        return;

    int percentByOneCheck = 100 / checkSize;

    int progress = 0;

    for (int i = 0; i < checkSize; i++)
    {
        if (stopFlag)
        {
            break;
        }

        emit messageChanged(d->checks->at(i).get()->m_name);

        executeCommand(d->checks->at(i).get());
        QThread::sleep(1);

        emit onProgressUpdate(progress + (i + 1) * percentByOneCheck);
    }

    emit onProgressUpdate(100);

    this->moveToThread(QApplication::instance()->thread());

    emit finish();

    QThread::currentThread()->quit();
}

void DiagnosticTool::runResolvers()
{
    emit begin();

    int resolversSize = d->resolvers->size();

    if (resolversSize == 0)
        return;

    int percentByOneResolver = 100 / resolversSize;

    int progress = 0;

    for (int i = 0; i < resolversSize; i++)
    {
        if (stopFlag)
        {
            break;
        }

        emit messageChanged(d->resolvers->at(i).get()->m_name);

        QThread::sleep(1); //job simulation

        emit onProgressUpdate(progress + (i + 1) * percentByOneResolver);
    }

    emit onProgressUpdate(100);

    this->moveToThread(QApplication::instance()->thread());

    emit finish();

    QThread::currentThread()->quit();
}

void DiagnosticTool::executeCommand(ADTExecutable *task)
{
    QDBusConnection dbus = QDBusConnection::systemBus();

    QDBusInterface iface("ru.basealt",
                         "/ru/basealt/alterator/executor",
                         "ru.basealt.alterator.executor",
                         dbus);

    bool i1 = iface.connection().connect(QLatin1String("ru.basealt"),
                                         QLatin1String("/ru/basealt/alterator/executor"),
                                         QLatin1String("ru.basealt.alterator.executor"),
                                         QLatin1String("executor_stdout"),
                                         task,
                                         SLOT(getStdout(QString)));
    bool i2 = iface.connection().connect("ru.basealt",
                                         "/ru/basealt/alterator/executor",
                                         "ru.basealt.alterator.executor",
                                         "executor_stderr",
                                         task,
                                         SLOT(getStderr(QString)));

    QDBusReply<int> reply = iface.call("test1", "\"dev\"");
    //    QList<QVariant> arg;
    //    arg << "\"dev\"";
    //    QDBusPendingReply<QString> reply = iface.asyncCall("test1", arg);
    //    reply.waitForFinished();

    qWarning() << "Args: " << task->m_args << " Exit code: " << reply.value();

    //    bool i3 = iface.connection().disconnect("ru.basealt",
    //                                            "/ru/basealt/alterator/executor",
    //                                            "ru.basealt.alterator.executor",
    //                                            "executor_stdout",
    //                                            task,
    //                                            SLOT(getStdout(QString)));
    //    bool i4 = iface.connection().disconnect("ru.basealt",
    //                                            "/ru/basealt/alterator/executor",
    //                                            "ru.basealt.alterator.executor",
    //                                            "executor_stderr",
    //                                            task,
    //                                            SLOT(getStderr(QString)));
}

void DiagnosticTool::cancelTask()
{
    stopFlag = true;
}

unsigned int DiagnosticTool::getAmountOfChecks()
{
    return d->checks->size();
}

unsigned int DiagnosticTool::getAmountOfResolvers()
{
    return d->resolvers->size();
}
