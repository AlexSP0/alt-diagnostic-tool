#ifndef ADTEXECUTOR_H
#define ADTEXECUTOR_H

#include "adtexecutorprivate.h"
#include "statuscommonwidget.h"

#include <QObject>

class ADTExecutor : public QObject
{
    Q_OBJECT
public:
    ADTExecutor(std::vector<StatusCommonWidget *> *vectorWidgets,
                QString serviceName,
                QString path,
                QString intefaceName);

    int getAmountOfWidgets();

    void cancelTasks();

    void resetStopFlag();

public slots:
    void runTasks();

private:
    void executeTask(ADTExecutable *task);

private:
    std::unique_ptr<ADTExecutorPrivate> d;

signals:
    void beginTask(StatusCommonWidget *currentWidget);
    void finishTask(StatusCommonWidget *currentWidget);

    void allTaskBegin();
    void allTasksFinished();
};

#endif // ADTEXECUTOR_H
