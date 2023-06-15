#include "mainwindowcontrollerimpl.h"

#include <QThread>

MainWindowControllerImpl::MainWindowControllerImpl(TreeModel *model,
                                                   MainWindowInterface *mainWindow,
                                                   ToolsWidgetInterface *toolsWidget,
                                                   TestWidgetInterface *testWidget)
    : m_model(model)
    , m_mainWindow(mainWindow)
    , m_toolsWidget(toolsWidget)
    , m_testWidget(testWidget)
    , m_currentToolItem(nullptr)
    , m_executor(new ADTExecutor())
    , m_workerThread(nullptr)
{
    m_toolsWidget->setController(this);
    m_toolsWidget->setModel(model);
    m_toolsWidget->disableButtons();

    m_testWidget->setController(this);

    m_mainWindow->setController(this);

    connect(m_executor.get(), &ADTExecutor::beginTask, this, &MainWindowControllerImpl::onBeginTask);
    connect(m_executor.get(), &ADTExecutor::finishTask, this, &MainWindowControllerImpl::onFinishTask);
    connect(m_executor.get(), &ADTExecutor::allTaskBegin, this, &MainWindowControllerImpl::onAllTasksBegin);
    connect(m_executor.get(), &ADTExecutor::allTasksFinished, this, &MainWindowControllerImpl::onAllTasksFinished);
}

MainWindowControllerImpl::~MainWindowControllerImpl() {}

void MainWindowControllerImpl::runAllToolsWidget() {}

void MainWindowControllerImpl::chooseToolsWidget()
{
    m_mainWindow->toggleStackWidget();
}

void MainWindowControllerImpl::exitToolsWidget()
{
    m_mainWindow->closeAll();
}

void MainWindowControllerImpl::changeSelectedTool(TreeItem *item)
{
    if (!item)
    {
        return;
    }

    m_currentToolItem = item;

    m_toolsWidget->setDescription(item->getExecutable()->m_description);

    m_toolsWidget->enableButtons();

    m_testWidget->setToolItem(item);
}

void MainWindowControllerImpl::runTestsWidget(std::vector<ADTExecutable *> tasks)
{
    m_executor->setTasks(tasks);

    m_executor->resetStopFlag();

    m_workerThread = new QThread();

    connect(m_workerThread, &QThread::started, m_executor.get(), &ADTExecutor::runTasks);
    connect(m_workerThread, &QThread::finished, m_workerThread, &QObject::deleteLater);

    m_executor->moveToThread(m_workerThread);

    m_workerThread->start();
}

void MainWindowControllerImpl::backTestsWigdet()
{
    m_mainWindow->toggleStackWidget();
}

void MainWindowControllerImpl::exitTestsWidget()
{
    m_mainWindow->closeAll();
}

void MainWindowControllerImpl::detailsCurrentTest(ADTExecutable *test)
{
    m_testWidget->showDetails(test->m_stringStdout + test->m_stringStderr);
}

void MainWindowControllerImpl::onAllTasksBegin()
{
    m_testWidget->disableButtons();
}

void MainWindowControllerImpl::onAllTasksFinished()
{
    m_testWidget->enableButtons();
}

void MainWindowControllerImpl::onBeginTask(ADTExecutable *task)
{
    m_testWidget->setWidgetStatus(task, TestWidgetInterface::TaskStatus::running);
}

void MainWindowControllerImpl::onFinishTask(ADTExecutable *task)
{
    if (task->m_exit_code == 0)
    {
        m_testWidget->setWidgetStatus(task, TestWidgetInterface::TaskStatus::finishedOk);
    }
    else
    {
        m_testWidget->setWidgetStatus(task, TestWidgetInterface::TaskStatus::finishedFailed);
    }
}
