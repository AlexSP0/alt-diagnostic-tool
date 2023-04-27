#include "runtests.h"
#include "./ui_runtestsdialog.h"

const int LAYOUT_STRETCH_INDEX  = 0;
const int LAYOUT_STRETCH_FACTOR = 10;

RunTestsDialog::RunTestsDialog(TreeModel *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunTestsDialog)
    , summaryLayout(new QVBoxLayout())
    , detailsLayout(new QVBoxLayout())
    , treeModel(model)
    , currentItemCategory(nullptr)
    , statusWidgets()
{
    ui->setupUi(this);

    ui->summaryScrollAreaWidgetContents->setLayout(summaryLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(detailsLayout);
}

RunTestsDialog::~RunTestsDialog()
{
    delete ui;
}

void RunTestsDialog::setCategory(TreeItem *category)
{
    currentItemCategory = category;

    clearUi();

    updateWidgetStorage();

    updateCommonStatusWidgets();
}

void RunTestsDialog::runCheckedTests() {}

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

void RunTestsDialog::clearUi()
{
    delete ui->summaryScrollAreaWidgetContents;

    ui->summaryScrollAreaWidgetContents = new QWidget();

    ui->summaryScrollArea->setWidget(ui->summaryScrollAreaWidgetContents);

    summaryLayout = new QVBoxLayout();
    summaryLayout->setAlignment(Qt::AlignTop);
    summaryLayout->insertStretch(LAYOUT_STRETCH_INDEX, LAYOUT_STRETCH_FACTOR);

    ui->summaryScrollAreaWidgetContents->setLayout(summaryLayout);

    ui->stackedWidget->setCurrentIndex(0);
}

void RunTestsDialog::updateCommonStatusWidgets()
{
    for (auto &commonStatusWidget : statusWidgets)
    {
        summaryLayout->insertWidget(0, commonStatusWidget, Qt::AlignTop);
    }
}

void RunTestsDialog::updateWidgetStorage()
{
    statusWidgets.clear();

    if (currentItemCategory->childCount() == 0)
    {
        return;
    }

    for (int i = 0; i < currentItemCategory->childCount(); i++)
    {
        StatusCommonWidget *currentWidget = new StatusCommonWidget(currentItemCategory->child(i));
        statusWidgets.push_back(currentWidget);
    }
}

void RunTestsDialog::toggleWidgetsInStackedWidget()
{
    ui->stackedWidget->currentIndex() == 0 ? ui->stackedWidget->setCurrentIndex(1)
                                           : ui->stackedWidget->setCurrentIndex(0);
}
