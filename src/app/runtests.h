#ifndef RUNTESTS_H
#define RUNTESTS_H

#include "treemodel.h"

#include <QDialog>

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

public slots:
    void runCheckedTests();

signals:
    void exitPressed();

private slots:
    void on_exitPushButton_clicked();

    void on_backPushButton_clicked();

    void on_testPushButton_clicked();

private:
    Ui::RunTestsDialog *ui;

    TreeModel *treeModel;

private:
    RunTestsDialog(const RunTestsDialog &) = delete;
    RunTestsDialog(RunTestsDialog &&)      = delete;
    RunTestsDialog &operator=(const RunTestsDialog &) = delete;
    RunTestsDialog &operator=(RunTestsDialog &&) = delete;
};

#endif // RUNTESTS_H
