#include "maintestswidget.h"
#include "ui_maintestswidget.h"

MainTestsWidget::MainTestsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainTestsWidget)
{
    ui->setupUi(this);
}

MainTestsWidget::~MainTestsWidget()
{
    delete ui;
}
