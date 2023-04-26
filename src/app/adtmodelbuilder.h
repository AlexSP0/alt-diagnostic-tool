#ifndef ADTMODELBUILDER_H
#define ADTMODELBUILDER_H

#include "../core/treemodel.h"
#include "../core/treemodelbuilderinterface.h"

#include <memory>
#include <QString>

class ADTModelBuilder
{
public:
    ADTModelBuilder();

    std::unique_ptr<TreeModel> buildModel();

private:
    QString m_dataFile         = "data.json";
    QString m_checksSection    = "checks";
    QString m_resolversSection = "resolvers";

    std::unique_ptr<TreeModelBuilderInterface> m_builder;
};

#endif // ADTMODELBUILDER_H
