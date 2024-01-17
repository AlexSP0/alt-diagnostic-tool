#ifndef MAINWINDOWCONTROLLERINTERFACE_H
#define MAINWINDOWCONTROLLERINTERFACE_H

#include "../core/adtexecutable.h"
#include "../core/treeitem.h"

#include <mainwindow/statuscommonwidget.h>

class MainWindowControllerInterface
{
public:
    virtual ~MainWindowControllerInterface();

    virtual void runAllToolsWidget() = 0;

    virtual void chooseToolsWidget() = 0;

    virtual void exitToolsWidget() = 0;

    virtual void changeSelectedTool(TreeItem *item) = 0;

    virtual TreeItem *changeSelectedToolByIndex(QModelIndex index) = 0;

    virtual void runTestsWidget(std::vector<ADTExecutable *> tasks) = 0;

    virtual void backTestsWigdet() = 0;

    virtual void exitTestsWidget() = 0;

    virtual void detailsCurrentTest(StatusCommonWidget *widget) = 0;

    virtual int runApp() = 0;

    virtual void saveMainWindowSettings() = 0;

    virtual void restoreMainWindowSettings() = 0;
};

#endif
