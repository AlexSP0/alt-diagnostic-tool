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
}

ADTExecutable *StatusCommonWidget::getExecutable()
{
    return treeItem->getExecutable();
}
