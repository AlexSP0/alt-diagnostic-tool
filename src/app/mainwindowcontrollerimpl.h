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

#ifndef MAINWINDOWCONTROLLERIMPL_H
#define MAINWINDOWCONTROLLERIMPL_H

#include "../core/treemodel.h"
#include "adtexecutor.h"
#include "interfaces/appcontrollerinterface.h"
#include "interfaces/mainwindowcontrollerinterface.h"
#include "interfaces/mainwindowinterface.h"
#include "interfaces/testswidgetinterface.h"
#include "interfaces/toolswidgetinterface.h"
#include "parser/commandlineoptions.h"

#include <QApplication>

class MainWindowControllerImplPrivate;

class MainWindowControllerImpl : public AppControllerInterface, public MainWindowControllerInterface
{
    Q_OBJECT
public:
    MainWindowControllerImpl(TreeModel *model, CommandLineOptions *options, QApplication *app);

    ~MainWindowControllerImpl();

    void runAllToolsWidget() override;

    void chooseToolsWidget() override;

    void exitToolsWidget() override;

    void changeSelectedTool(TreeItem *item) override;

    TreeItem *changeSelectedToolByIndex(QModelIndex index) override;

    void runTestsWidget(std::vector<ADTExecutable *> tasks) override;

    void backTestsWigdet();

    void exitTestsWidget();

    void detailsCurrentTest(StatusCommonWidget *widget);

    int listObjects();
    int listTestsOfObject(QString object);
    int runAllTestsOfObject(QString object);
    int runSpecifiedTestOfObject(QString object, QString test);
    int runApp() override;

public slots:
    virtual void on_serviceUnregistered() override;
    virtual void on_serviceRegistered() override;
    virtual void on_serviceOwnerChanged() override;

private:
    void clearAllReports();

    void clearToolReports(TreeItem *item);

    TreeItem *getToolById(QString id);

private:
    MainWindowControllerImplPrivate *d;

private slots:
    void onAllTasksBegin() override;
    void onAllTasksFinished() override;

    void onBeginTask(ADTExecutable *task) override;
    void onFinishTask(ADTExecutable *task) override;

    void onCloseAndExitButtonPressed();
    void on_closeButtonPressed();

private:
    MainWindowControllerImpl(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl(MainWindowControllerImpl &&)      = delete;

    MainWindowControllerImpl &operator=(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl &operator=(MainWindowControllerImpl &&) = delete;
};

#endif // MAINWINDOWCONTROLLERIMPL_H
