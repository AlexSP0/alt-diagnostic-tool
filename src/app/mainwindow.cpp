#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(TreeModel *model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , treeViewModel(model)
    , treeProxyModel(std::make_unique<TreeProxyModel>())
    , runTestWindow(std::make_unique<RunTestsDialog>(treeViewModel))
{
    ui->setupUi(this);
    treeProxyModel->setSourceModel(treeViewModel);
    ui->checkListView->setModel(treeViewModel);

    connect(runTestWindow.get(),
            &RunTestsDialog::exitPressed,
            this,
            &MainWindow::on_exitPushButton_clicked);
    connect(this,
            &MainWindow::runAllCheckedTests,
            runTestWindow.get(),
            &RunTestsDialog::runCheckedTests);

    connect(ui->checkListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::onSelectionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitPushButton_clicked()
{
    this->close();
}

void MainWindow::on_runAllPushButton_clicked()
{
    runTestWindow->show();
    emit runAllCheckedTests();
}

void MainWindow::on_browseCheckPushButton_clicked()
{
    runTestWindow->show();
}

void MainWindow::onSelectionChanged(const QItemSelection &newSelection,
                                    const QItemSelection &previousSelection)
{
    if (newSelection.isEmpty())
    {
        return;
    }

    QModelIndex currentIndex = newSelection.indexes().at(0);
    TreeItem *currentItem    = static_cast<TreeItem *>(currentIndex.internalPointer());

    if (currentItem)
    {
        runTestWindow->setCategory(currentItem);
    }
}
