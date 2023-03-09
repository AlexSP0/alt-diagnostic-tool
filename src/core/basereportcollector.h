#ifndef BASEREPORTCOLLECTOR_H
#define BASEREPORTCOLLECTOR_H

#include "ireportscollector.h"

class BaseReportCollector : public IReportsCollector
{
public:
    BaseReportCollector();

    virtual QString getReport(ADTExecutableRunner *tasks, ReportType type) override;
};

#endif // BASEREPORTCOLLECTOR_H
