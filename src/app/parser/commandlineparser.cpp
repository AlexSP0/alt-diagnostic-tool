#include "parser/commandlineparser.h"

#include <memory>
#include <QApplication>
#include <QCommandLineParser>

class CommandLineParserPrivate
{
public:
    QApplication &application;
    std::unique_ptr<QCommandLineParser> parser;

    CommandLineParserPrivate(QApplication &currentApplication)
        : application(currentApplication)
        , parser(std::make_unique<QCommandLineParser>())
    {}

private:
    CommandLineParserPrivate(const CommandLineParserPrivate &) = delete;
    CommandLineParserPrivate(CommandLineParserPrivate &&)      = delete;
    CommandLineParserPrivate &operator=(const CommandLineParserPrivate &) = delete;
    CommandLineParserPrivate &operator=(CommandLineParserPrivate &&) = delete;
};

CommandLineParser::CommandLineParser(QApplication &application)
    : d(new CommandLineParserPrivate(application))
{}

CommandLineParser::~CommandLineParser()
{
    delete d;
}

CommandLineParser::CommandLineParseResult CommandLineParser::parseCommandLine(CommandLineOptions *options,
                                                                              QString *errorMessage)
{
    //TO DO add translations
    const QCommandLineOption helpOption = d->parser->addHelpOption();

    const QCommandLineOption versionOption = d->parser->addVersionOption();

    const QCommandLineOption listOfObjectsOption("l", QObject::tr("List of available objects"));

    const QCommandLineOption objectListOption("o", QObject::tr("Test list of specified object."), "object");

    const QCommandLineOption runAllTestsOfSpecifiedObjectOption("a",
                                                                QObject::tr("Run all tests of speccified object"),
                                                                "object");

    const QCommandLineOption runSpecifiedTestOption(
        "r", QObject::tr("Run specicfied test of specified object. Must specify test name with -t option"), "object");

    const QCommandLineOption specifiedTestOption("t", QObject::tr("Specify test for running"), "test");

    d->parser->setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    d->parser->addOption(objectListOption);
    d->parser->addOption(listOfObjectsOption);
    d->parser->addOption(runAllTestsOfSpecifiedObjectOption);
    d->parser->addOption(runSpecifiedTestOption);
    d->parser->addOption(specifiedTestOption);

    if (!d->parser->parse(d->application.arguments()))
    {
        *errorMessage = d->parser->errorText();
        return CommandLineError;
    }

    if (d->parser->isSet(versionOption))
    {
        return CommandLineVersionRequested;
    }

    if (d->parser->isSet(helpOption))
    {
        return CommandLineHelpRequested;
    }

    if (d->parser->isSet(listOfObjectsOption))
    {
        return CommandLineListOfObjectsRequested;
    }

    if (d->parser->isSet(objectListOption))
    {
        const QString objectName = d->parser->value(objectListOption);
        options->objectName      = objectName;

        if (options->objectName.isNull() || options->objectName.isEmpty())
        {
            *errorMessage = QObject::tr("Bad object name: ") + objectName;
            return CommandLineError;
        }
        return CommandLineListOfTestsRequested;
    }

    if (d->parser->isSet(runAllTestsOfSpecifiedObjectOption))
    {
        const QString objectName = d->parser->value(runAllTestsOfSpecifiedObjectOption);
        options->objectName      = objectName;

        if (options->objectName.isNull() || options->objectName.isEmpty())
        {
            *errorMessage = QObject::tr("Bad object name: ") + objectName;
            return CommandLineError;
        }

        return CommandLineRunAllTestsRequested;
    }

    if (d->parser->isSet(runSpecifiedTestOption))
    {
        const QString objectName = d->parser->value(runAllTestsOfSpecifiedObjectOption);
        options->objectName      = objectName;

        if (options->objectName.isNull() || options->objectName.isEmpty())
        {
            *errorMessage = QObject::tr("Bad object name: ") + objectName;
            return CommandLineError;
        }

        if (!d->parser->isSet(specifiedTestOption))
        {
            *errorMessage = QObject::tr("Missing test name for object: ") + objectName;
            return CommandLineError;
        }

        const QString testName = d->parser->value(specifiedTestOption);
        options->testName      = testName;
        if (options->testName.isNull() || options->testName.isEmpty())
        {
            *errorMessage = QObject::tr("Bad test name: ") + testName;
            return CommandLineError;
        }

        return CommandLineRunSpecifiedTestRequested;
    }

    return CommandLineOk;
}

void CommandLineParser::showHelp()
{
    d->parser->showHelp();
}

void CommandLineParser::showVersion()
{
    d->parser->showVersion();
}
