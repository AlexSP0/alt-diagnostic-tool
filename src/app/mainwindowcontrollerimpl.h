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

class MainWindowControllerImpl : public MainWindowControllerInterface, public AppControllerInterface
{
    Q_OBJECT
public:
    MainWindowControllerImpl(TreeModel *model, CommandLineOptions *options, QApplication *app);

    ~MainWindowControllerImpl();

    void runAllToolsWidget();

    void chooseToolsWidget();

    void exitToolsWidget();

    void changeSelectedTool(TreeItem *item);

    void runTestsWidget(std::vector<ADTExecutable *> tasks);

    void backTestsWigdet();

    void exitTestsWidget();

    void detailsCurrentTest(ADTExecutable *test);

    int listObjects();
    int listTestsOfObject(QString object);
    int runAllTestsOfObject(QString object);
    int runSpecifiedTestOfObject(QString object, QString test);
    int runApp() override;

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

    CommandLineOptions *m_options;

    QApplication *m_application;

private slots:
    void onAllTasksBegin();
    void onAllTasksFinished();

    void onBeginTask(ADTExecutable *task);
    void onFinishTask(ADTExecutable *task);

private:
    TreeItem *getToolById(QString id);

private:
    MainWindowControllerImpl(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl(MainWindowControllerImpl &&)      = delete;

    MainWindowControllerImpl &operator=(const MainWindowControllerImpl &) = delete;
    MainWindowControllerImpl &operator=(MainWindowControllerImpl &&) = delete;
};

#endif // MAINWINDOWCONTROLLERIMPL_H
