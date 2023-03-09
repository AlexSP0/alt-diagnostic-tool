#include "basereportcollector.h"

BaseReportCollector::BaseReportCollector()
    : IReportsCollector()
{}

QString BaseReportCollector::getAllReports(ADTExecutableRunner *tasks)
{
    QString report;
    int numberOfTasks = tasks->getAmountOfTasks();

    report.append(m_startLine);
    for (int i = 0; i < numberOfTasks; i++)
    {
        ADTExecutable *currentTask = tasks->getTask(i);

        report.append(currentTask->m_name);
        report.append(currentTask->m_stdout);
        report.append(currentTask->m_stderr);
        report.append(m_delimiter);
    }

    report.append(m_endLine);

    return report;
}

QString BaseReportCollector::getStdoutReports(ADTExecutableRunner *tasks)
{
    QString report;
    int numberOfTasks = tasks->getAmountOfTasks();

    report.append(m_startLine);
    for (int i = 0; i < numberOfTasks; i++)
    {
        ADTExecutable *currentTask = tasks->getTask(i);

        report.append(currentTask->m_name);
        report.append(currentTask->m_stdout);
        report.append(m_delimiter);
    }

    report.append(m_endLine);

    return report;
}

QString BaseReportCollector::getStderrReports(ADTExecutableRunner *tasks)
{
    QString report;
    int numberOfTasks = tasks->getAmountOfTasks();

    report.append(m_startLine);
    for (int i = 0; i < numberOfTasks; i++)
    {
        ADTExecutable *currentTask = tasks->getTask(i);

        report.append(currentTask->m_name);
        report.append(currentTask->m_stderr);
        report.append(m_delimiter);
    }

    report.append(m_endLine);

    return report;
}
