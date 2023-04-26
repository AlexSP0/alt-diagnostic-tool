#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../core/treemodel.h"
#include "runtests.h"

#include <memory>
#include <treeproxymodel.h>
#include <QItemSelectionModel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
public:
    Q_OBJECT

public:
    MainWindow(TreeModel *model, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void runAllCheckedTests();

private slots:

    void on_exitPushButton_clicked();

    void on_runAllPushButton_clicked();

    void on_browseCheckPushButton_clicked();

    void onSelectionChanged(QItemSelection const &newSelection,
                            QItemSelection const &previousSelection);

private:
    Ui::MainWindow *ui;

    TreeModel *treeViewModel;
    std::unique_ptr<TreeProxyModel> treeProxyModel;
    std::unique_ptr<RunTestsDialog> runTestWindow;

private:
    MainWindow(const MainWindow &) = delete;
    MainWindow(MainWindow &&)      = delete;
    MainWindow &operator=(const MainWindow &) = delete;
    MainWindow &operator=(MainWindow &&) = delete;
};

#endif // MAINWINDOW_H
