#include "basereportcollector.h"

BaseReportCollector::BaseReportCollector()
    : IReportsCollector()
{}

QString BaseReportCollector::getReport(ADTExecutableRunner *tasks, ReportType type)
{
    QString report;
    int numberOfTasks = tasks->getAmountOfTasks();

    report.append(m_startLine);
    report.append("\n");

    for (int i = 0; i < numberOfTasks; i++)
    {
        ADTExecutable *currentTask = tasks->getTask(i);

        report.append(currentTask->m_name);
        report.append("\n");

        if (type == IReportsCollector::ReportType::All
            || type == IReportsCollector::ReportType::Stdout)
        {
            report.append(currentTask->m_stdout);
            report.append("\n");
        }

        if (type == IReportsCollector::ReportType::All
            || type == IReportsCollector::ReportType::Stderr)
        {
            report.append(currentTask->m_stderr);
            report.append("\n");
        }

        report.append(m_delimiter);
    }

    report.append(m_endLine);

    return report;
}
