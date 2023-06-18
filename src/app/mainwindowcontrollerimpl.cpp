#include "mainwindowcontrollerimpl.h"
#include "mainwindow.h"

#include <QThread>

MainWindowControllerImpl::MainWindowControllerImpl(TreeModel *model, CommandLineOptions *options, QApplication *app)
    : m_model(model)
    , m_mainWindow(nullptr)
    , m_toolsWidget(nullptr)
    , m_testWidget(nullptr)
    , m_currentToolItem(nullptr)
    , m_executor(new ADTExecutor())
    , m_workerThread(nullptr)
    , m_isWorkingThreadActive(false)
    , m_options(options)
    , m_application(app)
{
    m_mainWindow  = new MainWindow();
    m_toolsWidget = m_mainWindow->getToolsWidget();
    m_testWidget  = m_mainWindow->getTestWidget();

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

MainWindowControllerImpl::~MainWindowControllerImpl()
{
    delete m_mainWindow;
}

void MainWindowControllerImpl::runAllToolsWidget()
{
    m_mainWindow->toggleStackWidget();
    runTestsWidget(m_testWidget->getTasks());
}

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

int MainWindowControllerImpl::listObjects()
{
    return 0;
}

int MainWindowControllerImpl::listTestsOfObject(QString object)
{
    TreeItem *toolItem = getToolById(object);
    if (!toolItem)
    {
        qWarning() << "ERROR: can't find tool with id: " + object;
        //TO DO show messagebox with warning
        return 1;
    }

    changeSelectedTool(toolItem);
    m_mainWindow->toggleStackWidget();

    return 0;
}

int MainWindowControllerImpl::runAllTestsOfObject(QString object)
{
    TreeItem *toolItem = getToolById(object);
    if (!toolItem)
    {
        qWarning() << "ERROR: can't find tool with id: " + object;
        //TO DO show messagebox with warning
        return 1;
    }

    changeSelectedTool(toolItem);
    m_mainWindow->toggleStackWidget();

    runTestsWidget(m_testWidget->getTasks());
    return 0;
}

int MainWindowControllerImpl::runSpecifiedTestOfObject(QString object, QString test)
{
    TreeItem *toolItem = getToolById(object);
    if (!toolItem)
    {
        qWarning() << "ERROR: can't find tool with id: " + object;
        //TO DO show messagebox with warning
        return 1;
    }

    changeSelectedTool(toolItem);
    m_mainWindow->toggleStackWidget();

    std::vector<ADTExecutable *> tasks = m_testWidget->getTasks();

    ADTExecutable *runningTest = nullptr;

    for (ADTExecutable *currentTask : tasks)
    {
        if (currentTask->m_id == test)
        {
            runningTest = currentTask;
        }
    }

    if (!runningTest)
    {
        qWarning() << "ERROR: can't find test with id: " + test + " in tool: " + object;
        //TO DO show messagebox with warning
        return 1;
    }

    runTestsWidget(std::vector<ADTExecutable *>{runningTest});
    return 0;
}

int MainWindowControllerImpl::runApp()
{
    int result = -1;

    switch (m_options->action)
    {
    case CommandLineOptions::Action::listOfObjects:
        result = listObjects();
        break;
    case CommandLineOptions::Action::listOfTestFromSpecifiedObject:
        result = listTestsOfObject(m_options->objectName);
        break;
    case CommandLineOptions::Action::runAllTestFromSpecifiedObject:
        result = runAllTestsOfObject(m_options->objectName);
        break;
    case CommandLineOptions::Action::runSpecifiedTestFromSpecifiedObject:
        result = runSpecifiedTestOfObject(m_options->objectName, m_options->testName);
        break;
    default:
        break;
    }

    auto mainWindow = dynamic_cast<MainWindow *>(m_mainWindow);

    mainWindow->show();

    m_application->exec();

    return result;
}

void MainWindowControllerImpl::clearAllReports()
{
    QModelIndex rootIndex = m_model->parent(QModelIndex());

    TreeItem *rootItem = static_cast<TreeItem *>(rootIndex.internalPointer());

    if (!rootItem)
    {
        qWarning() << "ERROR: can't get root item to clear all reports!";

        return;
    }

    for (int i = rootItem->childCount() - 1; i >= 0; i--)
    {
        clearToolReports(rootItem->child(i));
    }
}

void MainWindowControllerImpl::clearToolReports(TreeItem *item)
{
    if (item->childCount() == 0)
    {
        return;
    }

    for (int i = item->childCount() - 1; i >= 0; i--)
    {
        TreeItem *currentChild = item->child(i);

        currentChild->getExecutable()->clearReports();
    }
}

void MainWindowControllerImpl::onAllTasksBegin()
{
    m_isWorkingThreadActive = true;
    m_testWidget->setEnabledRunButtonOfStatusWidgets(false);
    m_testWidget->disableButtons();
}

void MainWindowControllerImpl::onAllTasksFinished()
{
    m_isWorkingThreadActive = false;
    m_testWidget->setEnabledRunButtonOfStatusWidgets(true);
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

TreeItem *MainWindowControllerImpl::getToolById(QString id)
{
    TreeItem *rootItem = static_cast<TreeItem *>(m_model->parent(QModelIndex()).internalPointer());

    if (rootItem->childCount() < 1)
    {
        qWarning() << "ERROR: where is not tests in this tool!";
        return nullptr;
    }

    for (int i = 0; i < rootItem->childCount(); i++)
    {
        TreeItem *currentChild = rootItem->child(i);
        if (currentChild->getExecutable()->m_id == id)
        {
            return currentChild;
        }
    }

    return nullptr;
}
