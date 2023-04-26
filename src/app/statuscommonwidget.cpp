#include "statuscommonwidget.h"
#include "ui_statuscommonwidget.h"

StatusCommonWidget::StatusCommonWidget(TreeItem *item, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatusCommonWidget)
    , treeItem(item)
{}
