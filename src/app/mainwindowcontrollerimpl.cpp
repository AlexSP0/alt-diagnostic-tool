#include "mainwindowcontrollerimpl.h"

MainWindowControllerImpl::MainWindowControllerImpl(TreeModel *model,
                                                   MainWindowInterface *mainWindow,
                                                   ToolsWidgetInterface *toolsWidget,
                                                   TestWidgetInterface *testWidget)
    : m_model(model)
    , m_mainWindow(mainWindow)
    , m_toolsWidget(toolsWidget)
    , m_testWidget(testWidget)
    , m_currentToolItem(nullptr)
{
    m_toolsWidget->setController(this);
    m_toolsWidget->setModel(model);
    m_toolsWidget->disableButtons();

    m_testWidget->setController(this);

    m_mainWindow->setController(this);
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

void MainWindowControllerImpl::runAllTestsWidget() {}

void MainWindowControllerImpl::backTestsWigdet()
{
    m_mainWindow->toggleStackWidget();
}

void MainWindowControllerImpl::exitTestsWidget()
{
    m_mainWindow->closeAll();
}

void MainWindowControllerImpl::runCurrentTest(ADTExecutable *test) {}

void MainWindowControllerImpl::detailsCurrentTest(ADTExecutable *test)
{
    m_testWidget->showDetails(test->m_stringStdout + test->m_stringStderr);
}
