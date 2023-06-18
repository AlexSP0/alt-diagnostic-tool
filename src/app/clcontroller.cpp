#include "clcontroller.h"

#include <iostream>

class CLControllerPrivate
{
public:
    CLControllerPrivate(TreeModel *model, CommandLineOptions *options)
        : m_options(options)
        , m_model(model)
    {}
    ~CLControllerPrivate() {}

    CommandLineOptions *m_options;
    TreeModel *m_model;

private:
    CLControllerPrivate(const CLControllerPrivate &) = delete;
    CLControllerPrivate(CLControllerPrivate &&)      = delete;
    CLControllerPrivate &operator=(const CLControllerPrivate &) = delete;
    CLControllerPrivate &operator=(CLControllerPrivate &&) = delete;
};

CLController::CLController(TreeModel *model, CommandLineOptions *options)
    : d(new CLControllerPrivate(model, options))
{}

CLController::~CLController()
{
    delete d;
}

int CLController::listObjects()
{
    std::cout << "list all objects" << std::endl;
    return 0;
}

int CLController::listTestsOfObject(QString object)
{
    std::cout << "list test of " << object.toStdString() << "object" << std::endl;
    return 0;
}

int CLController::runAllTestsOfObject(QString object)
{
    std::cout << "run all tests of " << object.toStdString() << "object" << std::endl;
    return 0;
}

int CLController::runSpecifiedTestOfObject(QString object, QString test)
{
    std::cout << "run" << test.toStdString() << " test of " << object.toStdString() << "object" << std::endl;
    return 0;
}

int CLController::runApp()
{
    int result = -1;

    switch (d->m_options->action)
    {
    case CommandLineOptions::Action::listOfObjects:
        result = listObjects();
        break;
    case CommandLineOptions::Action::listOfTestFromSpecifiedObject:
        result = listTestsOfObject(d->m_options->objectName);
        break;
    case CommandLineOptions::Action::runAllTestFromSpecifiedObject:
        result = runAllTestsOfObject(d->m_options->objectName);
        break;
    case CommandLineOptions::Action::runSpecifiedTestFromSpecifiedObject:
        result = runSpecifiedTestOfObject(d->m_options->objectName, d->m_options->testName);
        break;
    default:
        break;
    }

    return result;
}
