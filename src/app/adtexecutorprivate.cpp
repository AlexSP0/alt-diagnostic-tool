#include "adtexecutorprivate.h"

ADTExecutorPrivate::ADTExecutorPrivate(std::vector<StatusCommonWidget *> *vectorWidgets)
    : widgets(vectorWidgets)
    , serviceName()
    , path()
    , interfaceName()
    , stopFlag(false)
    , dbus(nullptr)
    , dbusInterface(nullptr)
{}
