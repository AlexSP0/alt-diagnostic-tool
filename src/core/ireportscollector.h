#ifndef IREPORTSCOLLECTOR_H
#define IREPORTSCOLLECTOR_H

#include <QString>

#include "adtexecutablerunner.h"

class IReportsCollector
{
public:
    enum ReportType
    {
        All,
        Stdout,
        Stderr
    };

public:
    IReportsCollector();
    virtual ~IReportsCollector() = default;

    virtual QString getReport(ADTExecutableRunner *tasks, ReportType type) = 0;

    void setDelimiter(QString delimiter);

    void setStartLine(QString str);

    void setEndLine(QString str);

protected:
    QString m_delimiter;
    QString m_startLine;
    QString m_endLine;
};

#endif
