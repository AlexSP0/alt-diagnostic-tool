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
