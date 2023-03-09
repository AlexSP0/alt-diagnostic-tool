#ifndef IREPORTSCOLLECTOR_H
#define IREPORTSCOLLECTOR_H

#include <QString>

#include "adtexecutablerunner.h"

class IReportsCollector
{
public:
    IReportsCollector();
    virtual ~IReportsCollector() = default;

    virtual QString getAllReports(ADTExecutableRunner *tasks) = 0;

    virtual QString getStdoutReports(ADTExecutableRunner *tasks) = 0;

    virtual QString getStderrReports(ADTExecutableRunner *tasks) = 0;

    void setDelimiter(QString delimiter);

    void setStartLine(QString str);

    void setEndLine(QString str);

protected:
    QString m_delimiter;
    QString m_startLine;
    QString m_endLine;
};

#endif
