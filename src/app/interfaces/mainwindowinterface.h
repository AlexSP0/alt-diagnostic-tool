#ifndef MAINWINDOWINTERFACE_H
#define MAINWINDOWINTERFACE_H

class MainWindowInterface
{
public:
    virtual ~MainWindowInterface();

    virtual void toggleStackWidget() = 0;
};

#endif
