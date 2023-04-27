#ifndef ADTEXECUTOR_H
#define ADTEXECUTOR_H

#include "adtexecutorprivate.h"
#include "statuscommonwidget.h"

#include <QObject>

class ADTExecutor
{
public:
    ADTExecutor(std::vector<StatusCommonWidget> &widgets, QString &serviceName, QString &path, QString &intefaceName);

    int getAmountOfWidgets();

    void cancelTasks();

    void resetStopFlag();

public slots:

    void runTasks();

private:
    void executeTask();

private:
    std::unique_ptr<ADTExecutorPrivate> d;

signals:
    void beginTask();
    void finishTask();

    void allTaskBegin();
    void allTasksFinished();
};

#endif // ADTEXECUTOR_H
