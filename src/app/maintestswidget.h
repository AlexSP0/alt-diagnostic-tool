#ifndef MAINTESTSWIDGET_H
#define MAINTESTSWIDGET_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../core/treemodel.h"
#include "interfaces/testswidgetinterface.h"

#include "adtexecutor.h"
#include "statuscommonwidget.h"

namespace Ui
{
class MainTestsWidget;
}

class MainTestsWidget : public QWidget, public TestWidgetInterface
{
    Q_OBJECT
public:
    MainTestsWidget(QWidget *parent = nullptr);
    ~MainTestsWidget();

    void setToolItem(TreeItem *item) override;

    void enableButtons() override;
    void disableButtons() override;

    void showDetails(QString detailsText) override;

    void showAllTest() override;

    void changeStatusWidgetIcon(StatusCommonWidget *widget, QIcon &icon) override;

private:
    Ui::MainTestsWidget *ui;

    QVBoxLayout *m_summaryLayout;
    QVBoxLayout *m_detailsLayout;
    QPlainTextEdit *m_detailsText;
    QPushButton *m_backToSummaryWidgetButton;

    TreeItem *m_currentToolItem;

private:
    MainTestsWidget(const MainTestsWidget &) = delete;
    MainTestsWidget(MainTestsWidget &&)      = delete;
    MainTestsWidget &operator=(const MainTestsWidget &) = delete;
    MainTestsWidget &operator=(MainTestsWidget &&) = delete;
};

#endif // MAINTESTSWIDGET_H
