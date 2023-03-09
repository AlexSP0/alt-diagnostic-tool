#ifndef BASEREPORTCOLLECTOR_H
#define BASEREPORTCOLLECTOR_H

#include "ireportscollector.h"

class BaseReportCollector : public IReportsCollector
{
public:
    BaseReportCollector();

    virtual QString getAllReports(ADTExecutableRunner *tasks) override;

    virtual QString getStdoutReports(ADTExecutableRunner *tasks) override;

    virtual QString getStderrReports(ADTExecutableRunner *tasks) override;
};

#endif // BASEREPORTCOLLECTOR_H
