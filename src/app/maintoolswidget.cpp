#include "maintoolswidget.h"
#include "ui_maintoolswidget.h"

MainToolsWidget::MainToolsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainToolsWidget)
{
    ui->setupUi(this);
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
}

void MainToolsWidget::setDescription(QString description)
{
    ui->descriptionTextEdit->setText(description);
}
