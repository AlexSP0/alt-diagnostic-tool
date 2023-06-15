#ifndef MAINWINDOWCONTROLLERIMPL_H
#define MAINWINDOWCONTROLLERIMPL_H

#include "../core/treemodel.h"
#include "interfaces/mainwindowcontrollerinterface.h"
#include "interfaces/mainwindowinterface.h"
#include "interfaces/testswidgetinterface.h"
#include "interfaces/toolswidgetinterface.h"

class MainWindowControllerImpl : public MainWindowControllerInterface
{
public:
    MainWindowControllerImpl(TreeModel *model,
                             MainWindowInterface *mainWindow,
                             ToolsWidgetInterface *toolsWidget,
                             TestWidgetInterface *testWidget);

    ~MainWindowControllerImpl();

    void runAllToolsWidget();

    void chooseToolsWidget();

    void exitToolsWidget();

    void changeSelectedTool(TreeItem *item);

    void runAllTestsWidget();

    void backTestsWigdet();

    void exitTestsWidget();

    void runCurrentTest(ADTExecutable *test);

    void detailsCurrentTest(ADTExecutable *test);

private:
    TreeModel *m_model;

    MainWindowInterface *m_mainWindow;

    ToolsWidgetInterface *m_toolsWidget;

    TestWidgetInterface *m_testWidget;

    TreeItem *m_currentToolItem;

private:
    MainWindowControllerImpl(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl(MainWindowControllerImpl &&)      = delete;

    MainWindowControllerImpl &operator=(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl &operator=(MainWindowControllerImpl &&) = delete;
};

#endif // MAINWINDOWCONTROLLERIMPL_H
