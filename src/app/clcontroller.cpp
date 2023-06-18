#include "clcontroller.h"

class CLControllerPrivate
{
public:
    CLControllerPrivate(CommandLineOptions *options)
        : m_options(options)
    {}
    ~CLControllerPrivate() {}

    CommandLineOptions *m_options;

private:
    CLControllerPrivate(const CLControllerPrivate &) = delete;
    CLControllerPrivate(CLControllerPrivate &&)      = delete;
    CLControllerPrivate &operator=(const CLControllerPrivate &) = delete;
    CLControllerPrivate &operator=(CLControllerPrivate &&) = delete;
};

CLController::CLController(CommandLineOptions *options)
    : d(new CLControllerPrivate(options))
{}

CLController::~CLController()
{
    delete d;
}

int CLController::listObjects()
{
    return 0;
}

int CLController::listTestsOfObject(QString object)
{
    return 0;
}

int CLController::runAllTestsOfObject(QString object)
{
    return 0;
}

int CLController::runSpecifiedTestOfObject(QString object, QString test)
{
    return 0;
}

int CLController::runApp()
{
    return 0;
}
