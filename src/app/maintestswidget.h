#ifndef MAINTESTSWIDGET_H
#define MAINTESTSWIDGET_H

#include <QWidget>

namespace Ui
{
class MainTestsWidget;
}

class MainTestsWidget : public QWidget
{
    Q_OBJECT
public:
    MainTestsWidget(QWidget *parent = nullptr);
    ~MainTestsWidget();

private:
    Ui::MainTestsWidget *ui;

private:
    MainTestsWidget(const MainTestsWidget &) = delete;
    MainTestsWidget(MainTestsWidget &&)      = delete;
    MainTestsWidget &operator=(const MainTestsWidget &) = delete;
    MainTestsWidget &operator=(MainTestsWidget &&) = delete;
};

#endif // MAINTESTSWIDGET_H
