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

    void setController(MainWindowControllerInterface *controller) override;

    void setToolItem(TreeItem *item) override;

    void enableButtons() override;
    void disableButtons() override;

    void showDetails(QString detailsText) override;

    void showAllTest() override;

    void changeStatusWidgetIcon(StatusCommonWidget *widget, QIcon &icon) override;

private slots:
    void on_runAllTestPushButton_clicked();

    void on_backPushButton_clicked();

    void on_exitPushButton_clicked();

    void on_runButtonCurrentStatusWidget_clicked(StatusCommonWidget *widget);
    void on_detailsButtonCurrentStatusWidget_clicked(StatusCommonWidget *widget);
    void on_backToSummaryPushButton_clicked();

private:
    void updateStatusWidgets();

    void updateListOfStatusCommonWidgets();

    void clearUi();

private:
    Ui::MainTestsWidget *ui;

    MainWindowControllerInterface *m_controller;

    QVBoxLayout *m_summaryLayout;
    QVBoxLayout *m_detailsLayout;
    QPlainTextEdit *m_detailsText;
    QPushButton *m_backToSummaryWidgetButton;

    TreeItem *m_currentToolItem;

    QMap<StatusCommonWidget *, int> m_statusWidgets;

private:
    MainTestsWidget(const MainTestsWidget &) = delete;
    MainTestsWidget(MainTestsWidget &&)      = delete;
    MainTestsWidget &operator=(const MainTestsWidget &) = delete;
    MainTestsWidget &operator=(MainTestsWidget &&) = delete;
};

#endif // MAINTESTSWIDGET_H
