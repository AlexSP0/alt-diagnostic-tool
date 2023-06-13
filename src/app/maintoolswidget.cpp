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
