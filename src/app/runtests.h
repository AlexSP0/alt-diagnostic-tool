#ifndef RUNTESTS_H
#define RUNTESTS_H

#include "../core/treemodel.h"

#include "adtexecutor.h"
#include "statuscommonwidget.h"

#include <QDialog>
#include <QPlainTextEdit>
#include <QThread>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui
{
class RunTestsDialog;
}
QT_END_NAMESPACE
class RunTestsDialog : public QDialog
{
public:
    Q_OBJECT

public:
    RunTestsDialog(TreeModel *model, QWidget *parent = nullptr);
    ~RunTestsDialog();

    void setCategory(TreeItem *category);

public slots:
    void runCheckedTests();

signals:
    void exitPressed();

private slots:
    void on_exitPushButton_clicked();

    void on_backPushButton_clicked();

    void on_testPushButton_clicked();

    void on_Details_Button_clicked(StatusCommonWidget *widget);

    void toggleWidgetsInStackedWidget();

private:
    Ui::RunTestsDialog *ui;

    QVBoxLayout *summaryLayout;
    QVBoxLayout *detailsLayout;
    QPlainTextEdit *detailsText;
    QPushButton *backToSummaryWidgetButton;

    TreeModel *treeModel;

    TreeItem *currentItemCategory;

    std::vector<StatusCommonWidget *> statusWidgets;

    std::unique_ptr<ADTExecutor> executor;

    QThread *workerThread;

private:
    void clearUi();

    void updateStackedWidget();

    void updateCommonStatusWidgets();

    void updateWidgetStorage();

private:
    RunTestsDialog(const RunTestsDialog &) = delete;
    RunTestsDialog(RunTestsDialog &&)      = delete;
    RunTestsDialog &operator=(const RunTestsDialog &) = delete;
    RunTestsDialog &operator=(RunTestsDialog &&) = delete;
};

#endif // RUNTESTS_H
