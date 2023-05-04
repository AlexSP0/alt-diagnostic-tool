/***********************************************************************************************************************
**
** Copyright (C) 2023 BaseALT Ltd. <org@basealt.ru>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#ifndef RUNTESTSDIALOG_H
#define RUNTESTSDIALOG_H

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

    void on_runPushBitton_clicked(StatusCommonWidget *currentWidget);

    void on_Details_Button_clicked(StatusCommonWidget *widget);

    void toggleWidgetsInStackedWidget();

    void on_beginTask(StatusCommonWidget *currentWidget);

    void on_finishTask(StatusCommonWidget *currentWidget);

private:
    Ui::RunTestsDialog *ui;

    QVBoxLayout *summaryLayout;
    QVBoxLayout *detailsLayout;
    QPlainTextEdit *detailsText;
    QPushButton *backToSummaryWidgetButton;

    TreeModel *treeModel;

    TreeItem *currentItemCategory;

    std::vector<StatusCommonWidget *> statusWidgetsToDraw;
    std::vector<StatusCommonWidget *> statusWidgetsForRun;

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
