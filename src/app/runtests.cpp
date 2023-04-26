#include "runtests.h"
#include "./ui_runtestsdialog.h"

RunTestsDialog::RunTestsDialog(TreeModel *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunTestsDialog)
    , summaryLayout(nullptr)
    , detailsLayout(nullptr)
    , treeModel(model)
    , currentItemCategory(nullptr)
    , statusWidgets()
{
    ui->setupUi(this);

    summaryLayout = new QVBoxLayout();
    detailsLayout = new QVBoxLayout();
}

RunTestsDialog::~RunTestsDialog()
{
    delete ui;
}

void RunTestsDialog::setCategory(TreeItem *category)
{
    currentItemCategory = category;

    updateCommonStatusWidgets();

    updateStackedWidget();
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

void RunTestsDialog::updateStackedWidget()
{

}

void RunTestsDialog::updateCommonStatusWidgets()
{
    statusWidgets.clear();

    if (currentItemCategory->childCount() == 0)
    {
        return;
    }

    for (int i = 0; i < currentItemCategory->childCount(); i++)
    {
        statusWidgets.emplace_back(
            std::make_unique<StatusCommonWidget>(currentItemCategory->child(i)));
    }
}
