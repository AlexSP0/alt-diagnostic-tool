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

private:
    Ui::MainToolsWidget *ui;

private:
    MainToolsWidget(const MainToolsWidget &) = delete;
    MainToolsWidget(MainToolsWidget &&)      = delete;
    MainToolsWidget &operator=(const MainToolsWidget &) = delete;
    MainToolsWidget &operator=(MainToolsWidget &&) = delete;

    // ToolsWidgetInterface interface
public:
    void setModel(QAbstractItemModel *model) override;

    void enableButtons() override;
    void disableButtons() override;

    void enableExitButton() override;
    void disableExitButton() override;

    void setDescription(QString description) override;
};

#endif // MAINTOOLSWIDGET_H
