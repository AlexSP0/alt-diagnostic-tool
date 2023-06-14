#ifndef MAINWINDOWCONTROLLERIMPL_H
#define MAINWINDOWCONTROLLERIMPL_H

#include "interfaces/mainwindowcontrollerinterface.h"

class MainWindowControllerImpl : public MainWindowControllerInterface
{
public:
    MainWindowControllerImpl();

    ~MainWindowControllerImpl();

    void runAllToolsWidget();

    void chooseToolsWidget();

    void exitToolsWidget();

    void changeSelectedTool(TreeItem *item);

    void runAllTestsWidget();

    void backTestsWigdet();

    void exitTestsWidget();

    void runCurrentTest(ADTExecutable *test);

    void detailsCurrentTest(ADTExecutable *test);

    void backToListOfTest();
};

#endif // MAINWINDOWCONTROLLERIMPL_H
