#include "adtexecutor.h"

ADTExecutor::ADTExecutor(std::vector<StatusCommonWidget> &widgets,
                         QString &serviceName,
                         QString &path,
                         QString &intefaceName)
    : d(std::unique_ptr<ADTExecutorPrivate>())
{}

int ADTExecutor::getAmountOfWidgets()
{
    return -1;
}

void ADTExecutor::cancelTasks() {}

void ADTExecutor::resetStopFlag() {}

void ADTExecutor::runTasks() {}

void ADTExecutor::executeTask() {}
