#ifndef COMMANDLINEOPTIONS_H
#define COMMANDLINEOPTIONS_H

#include <qstring.h>

class CommandLineOptions
{
public:
    enum Action
    {
        none,
        listOfTestInObject,
        runAllTestInObject,
        runSpecifiedTestOfObject
    };
    Action action = Action::none;

    QString objectName{};
    QString testName{};
    bool useGraphic{true};
};

#endif
