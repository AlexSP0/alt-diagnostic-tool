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

void MainToolsWidget::setModel(QAbstractItemModel *model)
{
    ui->toolsListView->setModel(model);
}

QItemSelectionModel *MainToolsWidget::getSelectionModel()
{
    return ui->toolsListView->selectionModel();
}

void MainToolsWidget::clearDescription()
{
    ui->descriptionTextEdit->clear();
}

void MainToolsWidget::setDescription(QString description)
{
    ui->descriptionTextEdit->setText(description);
}
