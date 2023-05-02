#include "statuscommonwidget.h"
#include "ui_statuscommonwidget.h"

#include <QStyle>

StatusCommonWidget::StatusCommonWidget(TreeItem *item, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatusCommonWidget)
    , treeItem(item)
{
    ui->setupUi(this);

    QIcon icon = style()->standardIcon(QStyle::SP_ComputerIcon);

    ui->testIconLabel->setPixmap(icon.pixmap(QSize(16, 16)));

    ui->testNameLabel->setText(treeItem->getExecutable()->m_name);
}

ADTExecutable *StatusCommonWidget::getExecutable()
{
    return treeItem->getExecutable();
}

void StatusCommonWidget::setText(QString text)
{
    ui->testNameLabel->setText(text);
}

void StatusCommonWidget::setIcon(QIcon &icon)
{
    ui->testIconLabel->setPixmap(icon.pixmap(QSize(16, 16)));
}

void StatusCommonWidget::on_detailsPushButton_clicked()
{
    emit detailsButtonclicked(this);
}
