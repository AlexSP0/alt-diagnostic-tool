#include "maintestswidget.h"
#include "ui_maintestswidget.h"

#include <QStyle>
#include <QThread>

const int LAYOUT_STRETCH_INDEX  = 100;
const int LAYOUT_STRETCH_FACTOR = 400;
const int LAYOUT_INDEX          = 10;

MainTestsWidget::MainTestsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainTestsWidget)
    , m_controller(nullptr)
    , m_summaryLayout(new QVBoxLayout())
    , m_detailsLayout(new QVBoxLayout())
    , m_detailsText(new QPlainTextEdit())
    , m_backToSummaryWidgetButton(new QPushButton())
    , m_currentToolItem(nullptr)
    , m_statusWidgets()
{
    ui->setupUi(this);

    ui->summaryScrollAreaWidgetContents->setLayout(m_summaryLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(m_detailsLayout);

    m_backToSummaryWidgetButton->setText(tr("Back"));

    QHBoxLayout *detailsHButtonLayout = new QHBoxLayout();
    detailsHButtonLayout->addStretch();
    detailsHButtonLayout->addWidget(m_backToSummaryWidgetButton);
    connect(m_backToSummaryWidgetButton,
            &QPushButton::clicked,
            this,
            &MainTestsWidget::on_backToSummaryPushButton_clicked);

    m_detailsLayout->addWidget(m_detailsText);
    m_detailsLayout->insertLayout(LAYOUT_INDEX, detailsHButtonLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(m_detailsLayout);
}

MainTestsWidget::~MainTestsWidget()
{
    delete ui;
}

void MainTestsWidget::setController(MainWindowControllerInterface *controller)
{
    m_controller = controller;
}

void MainTestsWidget::setToolItem(TreeItem *item)
{
    m_currentToolItem = item;

    clearUi();

    updateStatusWidgets();

    updateListOfStatusCommonWidgets();
}

void MainTestsWidget::enableButtons()
{
    ui->backPushButton->setEnabled(true);
    ui->exitPushButton->setEnabled(true);
    ui->runAllTestPushButton->setEnabled(true);
}

void MainTestsWidget::disableButtons()
{
    ui->backPushButton->setEnabled(false);
    ui->exitPushButton->setEnabled(false);
    ui->runAllTestPushButton->setEnabled(false);
}

void MainTestsWidget::showDetails(QString detailsText)
{
    m_detailsText->appendPlainText(detailsText);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainTestsWidget::showAllTest()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainTestsWidget::changeStatusWidgetIcon(StatusCommonWidget *widget, QIcon &icon) {}

void MainTestsWidget::on_runAllTestPushButton_clicked()
{
    m_controller->runAllTestsWidget();
}

void MainTestsWidget::on_backPushButton_clicked()
{
    m_controller->backTestsWigdet();
}

void MainTestsWidget::on_exitPushButton_clicked()
{
    m_controller->exitTestsWidget();
}

void MainTestsWidget::on_runButtonCurrentStatusWidget_clicked(StatusCommonWidget *widget) {}

void MainTestsWidget::on_detailsButtonCurrentStatusWidget_clicked(StatusCommonWidget *widget)
{
    m_controller->detailsCurrentTest(widget->getExecutable());
}

void MainTestsWidget::on_backToSummaryPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainTestsWidget::updateStatusWidgets()
{
    if (!m_currentToolItem)
    {
        return;
    }

    m_statusWidgets.clear();

    if (m_currentToolItem->childCount() == 0)
    {
        return;
    }

    for (int i = m_currentToolItem->childCount() - 1; i >= 0; i--)
    {
        StatusCommonWidget *currentWidget = new StatusCommonWidget(m_currentToolItem->child(i));

        connect(currentWidget,
                &StatusCommonWidget::detailsButtonClicked,
                this,
                &MainTestsWidget::on_detailsButtonCurrentStatusWidget_clicked);

        connect(currentWidget,
                &StatusCommonWidget::runButtonCLicked,
                this,
                &MainTestsWidget::on_runButtonCurrentStatusWidget_clicked);

        m_statusWidgets[currentWidget] = 0;
    }
}

void MainTestsWidget::updateListOfStatusCommonWidgets()
{
    int i = 0;
    for (auto &commonStatusWidget : m_statusWidgets.keys())
    {
        m_summaryLayout->insertWidget(i, commonStatusWidget, Qt::AlignTop);
        i++;
    }

    m_summaryLayout->insertStretch(LAYOUT_STRETCH_INDEX, LAYOUT_STRETCH_FACTOR);
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
