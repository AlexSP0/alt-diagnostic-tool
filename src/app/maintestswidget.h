#ifndef MAINTESTSWIDGET_H
#define MAINTESTSWIDGET_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../core/treemodel.h"

#include "statuscommonwidget.h"

namespace Ui
{
class MainTestsWidget;
}

class MainTestsWidget : public QWidget
{
    Q_OBJECT
public:
    MainTestsWidget(QWidget *parent = nullptr);
    ~MainTestsWidget();

    void setTreeModel(TreeModel *model);
    void setCategory(TreeItem *item);

private:
    Ui::MainTestsWidget *ui;

    QVBoxLayout *m_summaryLayout;
    QVBoxLayout *m_detailsLayout;
    QPlainTextEdit *m_detailsText;
    QPushButton *m_backToSummaryWidgetButton;

    TreeModel *m_treeModel;

    TreeItem *m_currentItemCategory;

    std::vector<StatusCommonWidget *> m_statusWidgetsToDraw;
    std::vector<StatusCommonWidget *> m_statusWidgetsForRun;

private:
    void toggleWidgetsInStackedWidget();

    void clearUi();

    void updateWidgetStorage();

    void updateCommonStatusWidgets();

private:
    MainTestsWidget(const MainTestsWidget &) = delete;
    MainTestsWidget(MainTestsWidget &&)      = delete;
    MainTestsWidget &operator=(const MainTestsWidget &) = delete;
    MainTestsWidget &operator=(MainTestsWidget &&) = delete;
};

#endif // MAINTESTSWIDGET_H
