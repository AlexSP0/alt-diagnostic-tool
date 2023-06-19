#ifndef MAINTOOLSWIDGET_H
#define MAINTOOLSWIDGET_H

#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QWidget>

#include "interfaces/toolswidgetinterface.h"

namespace Ui
{
class MainToolsWidget;
}

class MainToolsWidget : public QWidget, public ToolsWidgetInterface
{
    Q_OBJECT
public:
    MainToolsWidget(QWidget *parent = nullptr);
    ~MainToolsWidget();

public:
    void setController(MainWindowControllerInterface *controller) override;

    void setModel(QAbstractItemModel *model) override;

    void enableButtons() override;
    void disableButtons() override;

    void enableExitButton() override;
    void disableExitButton() override;

    void setDescription(QString description) override;

private slots:
    void on_runAllPushButton_clicked();

    void on_browseCheckPushButton_clicked();

    void on_exitPushButton_clicked();

    void onSelectionChanged(const QItemSelection &newSelection, const QItemSelection &previousSelection);

private:
    Ui::MainToolsWidget *ui;

    MainWindowControllerInterface *m_controller;

private:
    MainToolsWidget(const MainToolsWidget &) = delete;
    MainToolsWidget(MainToolsWidget &&)      = delete;
    MainToolsWidget &operator=(const MainToolsWidget &) = delete;
    MainToolsWidget &operator=(MainToolsWidget &&) = delete;
};

#endif // MAINTOOLSWIDGET_H
