#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include "parser/commandlineoptions.h"

#include <QApplication>

class CommandLineParserPrivate;

class CommandLineParser
{
public:
    enum CommandLineParseResult
    {
        CommandLineOk,
        CommandLineError,
        CommandLineVersionRequested,
        CommandLineHelpRequested,
        CommandLineListOfObjectsRequested,
        CommandLineListOfTestsRequested,
        CommandLineRunAllTestsRequested,
        CommandLineRunSpecifiedTestRequested
    };

public:
    CommandLineParser(QApplication &application);
    ~CommandLineParser();

    CommandLineParseResult parseCommandLine(CommandLineOptions *options, QString *errorMessage);

    void showHelp();
    void showVersion();

private:
    CommandLineParser(const CommandLineParser &) = delete;
    CommandLineParser(CommandLineParser &&)      = delete;
    CommandLineParser &operator=(const CommandLineParser &) = delete;
    CommandLineParser &operator=(CommandLineParser &&) = delete;

private:
    CommandLineParserPrivate *d;
};

#endif
