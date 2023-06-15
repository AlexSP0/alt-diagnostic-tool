#ifndef TESTSWIDGETINTERFACE_H
#define TESTSWIDGETINTERFACE_H

#include "../core/treemodel.h"
#include "mainwindowcontrollerinterface.h"

#include <statuscommonwidget.h>
#include <QIcon>

class TestWidgetInterface
{
public:
    enum TaskStatus
    {
        ready,
        running,
        finishedOk,
        finishedFailed
    };

public:
    virtual ~TestWidgetInterface();

    virtual void setToolItem(TreeItem *item) = 0;

    virtual void enableButtons()  = 0;
    virtual void disableButtons() = 0;

    virtual void showDetails(QString detailsText) = 0;
    virtual void showAllTest()                    = 0;

    virtual void setWidgetStatus(ADTExecutable *task, TestWidgetInterface::TaskStatus status) = 0;

    virtual void setController(MainWindowControllerInterface *controller) = 0;
};

#endif
