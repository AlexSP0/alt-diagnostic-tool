#include "runtests.h"
#include "./ui_runtestsdialog.h"

const int LAYOUT_STRETCH_INDEX  = 100;
const int LAYOUT_STRETCH_FACTOR = 400;
const int LAYOUT_INDEX          = 10;

RunTestsDialog::RunTestsDialog(TreeModel *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunTestsDialog)
    , summaryLayout(new QVBoxLayout())
    , detailsLayout(new QVBoxLayout())
    , detailsText(new QPlainTextEdit())
    , backToSummaryWidgetButton(new QPushButton())
    , treeModel(model)
    , currentItemCategory(nullptr)
    , statusWidgets()
    , executor(new ADTExecutor(&statusWidgets, "", "", ""))
    , workerThread(nullptr)
{
    ui->setupUi(this);

    ui->summaryScrollAreaWidgetContents->setLayout(summaryLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(detailsLayout);

    backToSummaryWidgetButton->setText("Back");
    connect(backToSummaryWidgetButton, &QPushButton::clicked, this, &RunTestsDialog::toggleWidgetsInStackedWidget);

    QHBoxLayout *detailsHButtonLayout = new QHBoxLayout();
    detailsHButtonLayout->addStretch();
    detailsHButtonLayout->addWidget(backToSummaryWidgetButton);

    detailsLayout->addWidget(detailsText);
    detailsLayout->insertLayout(LAYOUT_INDEX, detailsHButtonLayout);
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

void RunTestsDialog::runCheckedTests()
{
    //clearUi();

    executor->resetStopFlag();

    workerThread = new QThread();

    connect(workerThread, &QThread::started, executor.get(), &ADTExecutor::runTasks);
    connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    executor->moveToThread(workerThread);

    workerThread->start();
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

void RunTestsDialog::on_Details_Button_clicked(StatusCommonWidget *widget)
{
    if (widget == nullptr)
    {
        return;
    }

    detailsText->clear();

    detailsText->appendPlainText(widget->getExecutable()->m_stdout);
    detailsText->appendPlainText(widget->getExecutable()->m_stderr);

    toggleWidgetsInStackedWidget();
}

void RunTestsDialog::clearUi()
{
    delete ui->summaryScrollAreaWidgetContents;

    ui->summaryScrollAreaWidgetContents = new QWidget();

    ui->summaryScrollArea->setWidget(ui->summaryScrollAreaWidgetContents);

    summaryLayout = new QVBoxLayout();
    summaryLayout->setAlignment(Qt::AlignTop);

    ui->summaryScrollAreaWidgetContents->setLayout(summaryLayout);

    ui->stackedWidget->setCurrentIndex(0);
}

void RunTestsDialog::updateCommonStatusWidgets()
{
    for (auto &commonStatusWidget : statusWidgets)
    {
        summaryLayout->insertWidget(0, commonStatusWidget, Qt::AlignTop);
    }

    summaryLayout->insertStretch(LAYOUT_STRETCH_INDEX, LAYOUT_STRETCH_FACTOR);
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

        connect(currentWidget,
                &StatusCommonWidget::detailsButtonclicked,
                this,
                &RunTestsDialog::on_Details_Button_clicked);

        statusWidgets.push_back(currentWidget);
    }
}

void RunTestsDialog::toggleWidgetsInStackedWidget()
{
    ui->stackedWidget->currentIndex() == 0 ? ui->stackedWidget->setCurrentIndex(1)
                                           : ui->stackedWidget->setCurrentIndex(0);
}
