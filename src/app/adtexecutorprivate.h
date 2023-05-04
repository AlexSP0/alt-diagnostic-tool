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

#ifndef ADTEXECUTORPRIVATE_H
#define ADTEXECUTORPRIVATE_H

#include <statuscommonwidget.h>
#include <vector>
#include <QDBusConnection>
#include <qdbusinterface.h>

class ADTExecutorPrivate
{
public:
    ADTExecutorPrivate(std::vector<StatusCommonWidget *> *vectorWidgets);

    std::vector<StatusCommonWidget *> *widgets;

    QString dbusServiceName;
    QString dbusPath;
    QString dbusInterfaceName;
    QString dbusStdOutSignalName;
    QString dbusStdErrSignalName;

    volatile bool stopFlag;

    std::unique_ptr<QDBusConnection> dbus;
    std::unique_ptr<QDBusInterface> dbusInterface;

private:
    ADTExecutorPrivate(const ADTExecutorPrivate &) = delete;
    ADTExecutorPrivate(ADTExecutorPrivate &&)      = delete;
    ADTExecutorPrivate &operator=(const ADTExecutorPrivate &) = delete;
    ADTExecutorPrivate &operator=(ADTExecutorPrivate &&) = delete;
};

#endif // ADTEXECUTORPRIVATE_H
