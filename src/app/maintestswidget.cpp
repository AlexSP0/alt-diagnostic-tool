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
    , m_summaryLayout(new QVBoxLayout())
    , m_detailsLayout(new QVBoxLayout())
    , m_detailsText(new QPlainTextEdit())
    , m_backToSummaryWidgetButton(new QPushButton())
    , m_currentToolItem(nullptr)
{
    ui->setupUi(this);

    ui->summaryScrollAreaWidgetContents->setLayout(m_summaryLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(m_detailsLayout);

    m_backToSummaryWidgetButton->setText(tr("Back"));

    QHBoxLayout *detailsHButtonLayout = new QHBoxLayout();
    detailsHButtonLayout->addStretch();
    detailsHButtonLayout->addWidget(m_backToSummaryWidgetButton);

    m_detailsLayout->addWidget(m_detailsText);
    m_detailsLayout->insertLayout(LAYOUT_INDEX, detailsHButtonLayout);
    ui->detailsScrollAreaWidgetContents->setLayout(m_detailsLayout);
}

MainTestsWidget::~MainTestsWidget()
{
    delete ui;
}

void MainTestsWidget::setToolItem(TreeItem *item)
{
    m_currentToolItem = item;
}

void MainTestsWidget::enableButtons()
{

}

void MainTestsWidget::disableButtons()
{

}

void MainTestsWidget::showDetails(QString detailsText)
{

}

void MainTestsWidget::showAllTest()
{

}

void MainTestsWidget::changeStatusWidgetIcon(StatusCommonWidget *widget, QIcon &icon)
{

}
