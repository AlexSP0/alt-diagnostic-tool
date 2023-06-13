#ifndef MAINTOOLSWIDGET_H
#define MAINTOOLSWIDGET_H

#include <QWidget>

namespace Ui
{
class MainToolsWidget;
}

class MainToolsWidget : public QWidget
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
};

#endif // MAINTOOLSWIDGET_H
