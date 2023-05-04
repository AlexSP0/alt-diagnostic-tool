#ifndef ADTMODELBUILDERSTRATEGYFROMJSON_H
#define ADTMODELBUILDERSTRATEGYFROMJSON_H

#include "../core/treemodel.h"
#include "../core/treemodelbuilderinterface.h"
#include "adtmodelbuilderstrategyinterface.h"

#include <memory>
#include <QString>

class ADTModelBuilderStrategyFromJson : public ADTModelBuilderStrategyInterface
{
public:
    ADTModelBuilderStrategyFromJson(QString filename);

    std::unique_ptr<TreeModel> buildModel();

private:
    QString m_checksSection    = "checks";
    QString m_resolversSection = "resolvers";

    QString m_fileName;

    std::unique_ptr<TreeModelBuilderInterface> m_builder;
};

#endif // ADTMODELBUILDERSTRATEGYFROMJSON_H
