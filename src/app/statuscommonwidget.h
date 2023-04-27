#ifndef STATUSCOMMONWIDGET_H
#define STATUSCOMMONWIDGET_H

#include <../core/treeitem.h>
#include <QWidget>

namespace Ui
{
class StatusCommonWidget;
}

class StatusCommonWidget : public QWidget
{
    Q_OBJECT

public:
    StatusCommonWidget(TreeItem *item, QWidget *parent = nullptr);

    ADTExecutable *getExecutable();

private:
    Ui::StatusCommonWidget *ui;

    TreeItem *treeItem;

private:
    StatusCommonWidget(const StatusCommonWidget &) = delete;
    StatusCommonWidget(StatusCommonWidget &&)      = delete;
    StatusCommonWidget &operator=(const StatusCommonWidget &) = delete;
    StatusCommonWidget &operator=(StatusCommonWidget &&) = delete;
};

#endif // STATUSCOMMONWIDGET_H
