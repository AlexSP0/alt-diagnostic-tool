#ifndef APPCONTROLLERINTERFACE_H
#define APPCONTROLLERINTERFACE_H

#include <QString>

class AppControllerInterface
{
public:
    virtual ~AppControllerInterface();

    virtual int listObjects() = 0;

    virtual int listTestsOfObject(QString object) = 0;

    virtual int runAllTestsOfObject(QString object) = 0;

    virtual int runSpecifiedTestOfObject(QString object, QString test) = 0;

    virtual int runApp() = 0;
};

#endif // APPCONTROLLERINTERFACE_H
