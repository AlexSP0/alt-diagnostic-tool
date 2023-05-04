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

    void connectExecutableSignals(ADTExecutable *task);
    void disconnectExecutableSignals(ADTExecutable *task);

    void waitForAnswer(int mSeconds);

signals:
    void beginTask(StatusCommonWidget *currentWidget);
    void finishTask(StatusCommonWidget *currentWidget);

    void allTaskBegin();
    void allTasksFinished();
};

#endif // ADTEXECUTOR_H
