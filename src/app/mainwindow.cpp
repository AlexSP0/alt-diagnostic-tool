#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , treeViewModel(std::make_unique<TreeModel>())
    , treeProxyModel(std::make_unique<TreeProxyModel>())
    , runTestWindow(std::make_unique<RunTestsDialog>(treeViewModel.get()))
{
    ui->setupUi(this);
    treeProxyModel->setSourceModel(treeViewModel.get());
    ui->checkListView->setModel(treeProxyModel.get());

    connect(runTestWindow.get(), &RunTestsDialog::exitPressed, this, &MainWindow::on_exitPushButton_clicked);
    connect(this, &MainWindow::runAllCheckedTests, runTestWindow.get(), &RunTestsDialog::runCheckedTests);
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
