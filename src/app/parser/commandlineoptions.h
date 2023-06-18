#ifndef COMMANDLINEOPTIONS_H
#define COMMANDLINEOPTIONS_H

#include <qstring.h>

class CommandLineOptions
{
public:
    enum Action
    {
        listOfObjects,
        listOfTestFromSpecifiedObject,
        runAllTestFromSpecifiedObject,
        runSpecifiedTestFromSpecifiedObject
    };

    Action action{Action::listOfObjects};

    QString objectName{};

    QString testName{};

    bool useGraphic{true};
};

#endif
