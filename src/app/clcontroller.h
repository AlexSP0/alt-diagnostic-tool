#ifndef CLCONTROLLER_H
#define CLCONTROLLER_H

#include "interfaces/appcontrollerinterface.h"
#include "parser/commandlineoptions.h"
#include <QString>

class CLControllerPrivate;

class CLController : public AppControllerInterface
{
public:
    CLController(CommandLineOptions *options);
    ~CLController();

    int listObjects() override;

    int listTestsOfObject(QString object) override;

    int runAllTestsOfObject(QString object) override;

    int runSpecifiedTestOfObject(QString object, QString test) override;

    int runApp() override;

private:
    CLControllerPrivate *d;

private:
    CLController(const CLController &) = delete;
    CLController(CLController &&)      = delete;
    CLController &operator=(const CLController &) = delete;
    CLController &operator=(CLController &&) = delete;
};

#endif // CLCONTROLLER_H
