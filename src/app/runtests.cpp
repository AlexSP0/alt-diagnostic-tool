#include "runtests.h"
#include "./ui_runtestsdialog.h"

RunTestsDialog::RunTestsDialog(TreeModel *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunTestsDialog)
    , treeModel(model)
{
    ui->setupUi(this);
}

RunTestsDialog::~RunTestsDialog()
{
    delete ui;
}

void RunTestsDialog::runCheckedTests()
{
    //TO DO run all checked tests
}

void RunTestsDialog::on_exitPushButton_clicked()
{
    this->close();
    emit exitPressed();
}

void RunTestsDialog::on_backPushButton_clicked()
{
    this->close();
}

void RunTestsDialog::on_testPushButton_clicked() {}
