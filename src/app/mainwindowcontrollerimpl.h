#ifndef MAINWINDOWCONTROLLERIMPL_H
#define MAINWINDOWCONTROLLERIMPL_H

#include "../core/treemodel.h"
#include "adtexecutor.h"
#include "interfaces/mainwindowcontrollerinterface.h"
#include "interfaces/mainwindowinterface.h"
#include "interfaces/testswidgetinterface.h"
#include "interfaces/toolswidgetinterface.h"

class MainWindowControllerImpl : public MainWindowControllerInterface
{
    Q_OBJECT
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

    void runTestsWidget(std::vector<ADTExecutable *> tasks);

    void backTestsWigdet();

    void exitTestsWidget();

    void detailsCurrentTest(ADTExecutable *test);

private:
    void clearAllReports();

    void clearToolReports(TreeItem *item);

private:
    TreeModel *m_model;

    MainWindowInterface *m_mainWindow;

    ToolsWidgetInterface *m_toolsWidget;

    TestWidgetInterface *m_testWidget;

    TreeItem *m_currentToolItem;

    std::unique_ptr<ADTExecutor> m_executor;

    QThread *m_workerThread;

    bool m_isWorkingThreadActive;

private slots:
    void onAllTasksBegin();
    void onAllTasksFinished();

    void onBeginTask(ADTExecutable *task);
    void onFinishTask(ADTExecutable *task);

private:
    MainWindowControllerImpl(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl(MainWindowControllerImpl &&)      = delete;

    MainWindowControllerImpl &operator=(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl &operator=(MainWindowControllerImpl &&) = delete;
};

#endif // MAINWINDOWCONTROLLERIMPL_H
