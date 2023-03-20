#ifndef ADTWIZARDBUILDERSTRATEGY_H
#define ADTWIZARDBUILDERSTRATEGY_H

#include <QJsonDocument>

class IADTWizardBuilderStrategy
{
public:
    IADTWizardBuilderStrategy()          = default;
    virtual ~IADTWizardBuilderStrategy() = default;

    virtual QJsonDocument buildChecks(QString &, QString &, QString &, QString &, QString &)    = 0;
    virtual QJsonDocument buildResolvers(QString &, QString &, QString &, QString &, QString &) = 0;
};

#endif // ADTWIZARDBUILDERSTRATEGY_H
