#include "maintoolswidget.h"
#include "ui_maintoolswidget.h"

#include <QDebug>

MainToolsWidget::MainToolsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainToolsWidget)
    , m_controller(nullptr)
{
    ui->setupUi(this);
}

void MainToolsWidget::setController(MainWindowControllerInterface *controller)
{
    m_controller = controller;
}

MainToolsWidget::~MainToolsWidget()
{
    delete ui;
}

void MainToolsWidget::enableButtons()
{
    ui->runAllPushButton->setEnabled(true);
    ui->browseCheckPushButton->setEnabled(true);
}

void MainToolsWidget::disableButtons()
{
    ui->runAllPushButton->setEnabled(false);
    ui->browseCheckPushButton->setEnabled(false);
}

void MainToolsWidget::enableExitButton()
{
    ui->exitPushButton->setEnabled(true);
}

void MainToolsWidget::disableExitButton()
{
    ui->exitPushButton->setEnabled(false);
}

void MainToolsWidget::setModel(QAbstractItemModel *model)
{
    ui->toolsListView->setModel(model);

    connect(ui->toolsListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainToolsWidget::onSelectionChanged);
}

void MainToolsWidget::setDescription(QString description)
{
    ui->descriptionTextEdit->setText(description);
}

void MainToolsWidget::on_runAllPushButton_clicked()
{
    m_controller->runAllToolsWidget();
}

void MainToolsWidget::on_browseCheckPushButton_clicked()
{
    m_controller->chooseToolsWidget();
}

void MainToolsWidget::on_exitPushButton_clicked()
{
    m_controller->exitToolsWidget();
}

void MainToolsWidget::onSelectionChanged(const QItemSelection &newSelection, const QItemSelection &previousSelection)
{
    if (newSelection.isEmpty())
    {
        return;
    }

    QModelIndex currentIndex = newSelection.indexes().at(0);
    TreeItem *currentItem    = static_cast<TreeItem *>(currentIndex.internalPointer());

    if (!currentItem)
    {
        qWarning() << "ERROR: Can't get item from selection model!";
    }

    m_controller->changeSelectedTool(currentItem);
}
