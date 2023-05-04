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

#include "adtexecutorprivate.h"

#include <QDBusConnection>
#include <QDBusInterface>

ADTExecutorPrivate::ADTExecutorPrivate(std::vector<StatusCommonWidget *> *vectorWidgets)
    : widgets(vectorWidgets)
    , dbusServiceName("ru.basealt.alterator")
    , dbusPath("/ru/basealt/alterator/adt")
    , dbusInterfaceName("ru.basealt.alterator.adt")
    , dbusStdOutSignalName("executor_stdout")
    , dbusStdErrSignalName("executor_stderr")
    , stopFlag(false)
    , dbus(std::make_unique<QDBusConnection>(QDBusConnection::systemBus()))
    , dbusInterface(std::make_unique<QDBusInterface>(dbusServiceName, dbusPath, dbusInterfaceName, *dbus.get()))
{}
