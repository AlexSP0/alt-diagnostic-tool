#include <QStyle>

#include "./ui_runtestsdialog.h"
#include "runtests.h"

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
    , statusWidgetsToDraw({})
    , statusWidgetsForRun({})
    , executor(new ADTExecutor(&statusWidgetsForRun, "", "", ""))
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

    connect(executor.get(), &ADTExecutor::beginTask, this, &RunTestsDialog::on_beginTask);
    connect(executor.get(), &ADTExecutor::finishTask, this, &RunTestsDialog::on_finishTask);
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

void RunTestsDialog::on_testPushButton_clicked()
{
    clearUi();

    updateWidgetStorage();

    updateCommonStatusWidgets();

    runCheckedTests();
}

void RunTestsDialog::on_runPushBitton_clicked(StatusCommonWidget *currentWidget)
{
    statusWidgetsForRun.clear();
    statusWidgetsForRun.push_back(currentWidget);

    runCheckedTests();
}

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
    int i = 0;
    for (auto &commonStatusWidget : statusWidgetsToDraw)
    {
        summaryLayout->insertWidget(i, commonStatusWidget, Qt::AlignTop);
        i++;
    }

    summaryLayout->insertStretch(LAYOUT_STRETCH_INDEX, LAYOUT_STRETCH_FACTOR);
}

void RunTestsDialog::updateWidgetStorage()
{
    statusWidgetsToDraw.clear();

    if (currentItemCategory->childCount() == 0)
    {
        return;
    }

    for (int i = currentItemCategory->childCount() - 1; i >= 0; i--)
    {
        StatusCommonWidget *currentWidget = new StatusCommonWidget(currentItemCategory->child(i));

        connect(currentWidget,
                &StatusCommonWidget::detailsButtonClicked,
                this,
                &RunTestsDialog::on_Details_Button_clicked);

        connect(currentWidget, &StatusCommonWidget::runButtonCLicked, this, &RunTestsDialog::on_runPushBitton_clicked);

        statusWidgetsToDraw.push_back(currentWidget);
    }

    statusWidgetsForRun.clear();

    for (StatusCommonWidget *currentWidgetPtr : statusWidgetsToDraw)
    {
        statusWidgetsForRun.push_back(currentWidgetPtr);
    }
}

void RunTestsDialog::toggleWidgetsInStackedWidget()
{
    ui->stackedWidget->currentIndex() == 0 ? ui->stackedWidget->setCurrentIndex(1)
                                           : ui->stackedWidget->setCurrentIndex(0);
}

void RunTestsDialog::on_beginTask(StatusCommonWidget *currentWidget)
{
    QIcon icon = style()->standardIcon(QStyle::SP_BrowserReload);
    currentWidget->setIcon(icon);
}

void RunTestsDialog::on_finishTask(StatusCommonWidget *currentWidget)
{
    QIcon icon = style()->standardIcon(QStyle::SP_DialogApplyButton);

    if (currentWidget->getExecutable()->m_exit_code != 0)
    {
        icon = style()->standardIcon(QStyle::SP_DialogCloseButton);
    }

    currentWidget->setIcon(icon);
}
