#include "maintestswidget.h"
#include "ui_maintestswidget.h"

const int LAYOUT_STRETCH_INDEX  = 100;
const int LAYOUT_STRETCH_FACTOR = 400;
const int LAYOUT_INDEX          = 10;

MainTestsWidget::MainTestsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainTestsWidget)
    , m_summaryLayout(new QVBoxLayout())
    , m_detailsLayout(new QVBoxLayout())
    , m_detailsText(new QPlainTextEdit)
    , m_backToSummaryWidgetButton(new QPushButton())
    , m_treeModel(nullptr)
    , m_currentItemCategory(nullptr)
    , m_statusWidgetsToDraw({})
    , m_statusWidgetsForRun({})
{
    ui->setupUi(this);

    ui->summaryScrollAreaWidgetContents->setLayout(m_summaryLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(m_detailsLayout);

    m_backToSummaryWidgetButton->setText("Back");
    //connect(backToSummaryWidgetButton, &QPushButton::clicked, this, &RunTestsDialog::toggleWidgetsInStackedWidget);

    QHBoxLayout *detailsHButtonLayout = new QHBoxLayout();
    detailsHButtonLayout->addStretch();
    detailsHButtonLayout->addWidget(m_backToSummaryWidgetButton);

    m_detailsLayout->addWidget(m_detailsText);
    m_detailsLayout->insertLayout(LAYOUT_INDEX, detailsHButtonLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(m_detailsLayout);

    //connect(executor.get(), &ADTExecutor::beginTask, this, &RunTestsDialog::on_beginTask);
    //connect(executor.get(), &ADTExecutor::finishTask, this, &RunTestsDialog::on_finishTask);
}

MainTestsWidget::~MainTestsWidget()
{
    delete ui;
}

void MainTestsWidget::setTreeModel(TreeModel *model)
{
    m_treeModel = model;
}

void MainTestsWidget::setCategory(TreeItem *item)
{
    m_currentItemCategory = item;
}

void MainTestsWidget::toggleWidgetsInStackedWidget()
{
    ui->stackedWidget->currentIndex() == 0 ? ui->stackedWidget->setCurrentIndex(1)
                                           : ui->stackedWidget->setCurrentIndex(0);
}

void MainTestsWidget::clearUi()
{
    delete ui->summaryScrollAreaWidgetContents;

    ui->summaryScrollAreaWidgetContents = new QWidget();

    ui->summaryScrollArea->setWidget(ui->summaryScrollAreaWidgetContents);

    m_summaryLayout = new QVBoxLayout();
    m_summaryLayout->setAlignment(Qt::AlignTop);

    ui->summaryScrollAreaWidgetContents->setLayout(m_summaryLayout);

    ui->stackedWidget->setCurrentIndex(0);
}

void MainTestsWidget::updateWidgetStorage()
{
    m_statusWidgetsToDraw.clear();

    if (m_currentItemCategory->childCount() == 0)
    {
        return;
    }

    for (int i = m_currentItemCategory->childCount() - 1; i >= 0; i--)
    {
        StatusCommonWidget *currentWidget = new StatusCommonWidget(m_currentItemCategory->child(i));

        //        connect(currentWidget,
        //                &StatusCommonWidget::detailsButtonClicked,
        //                this,
        //                &RunTestsDialog::on_Details_Button_clicked);

        //        connect(currentWidget, &StatusCommonWidget::runButtonCLicked, this, &RunTestsDialog::on_runPushBitton_clicked);

        m_statusWidgetsToDraw.push_back(currentWidget);
    }

    //DO it really need here&
    m_statusWidgetsForRun.clear();

    //TODO remove this loop
    for (StatusCommonWidget *currentWidgetPtr : m_statusWidgetsToDraw)
    {
        m_statusWidgetsForRun.push_back(currentWidgetPtr);
    }
}

void MainTestsWidget::updateCommonStatusWidgets()
{
    int i = 0;
    for (auto &commonStatusWidget : m_statusWidgetsToDraw)
    {
        m_summaryLayout->insertWidget(i, commonStatusWidget, Qt::AlignTop);
        i++;
    }

    m_summaryLayout->insertStretch(LAYOUT_STRETCH_INDEX, LAYOUT_STRETCH_FACTOR);
}
