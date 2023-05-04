#ifndef ADTMODELBUILDER_H
#define ADTMODELBUILDER_H

#include "adtmodelbuilderstrategyinterface.h"

#include <memory>

class ADTModelBuilder
{
public:
    ADTModelBuilder(ADTModelBuilderStrategyInterface *builderStrategy);

    std::unique_ptr<TreeModel> buildModel();

private:
    std::unique_ptr<ADTModelBuilderStrategyInterface> m_builder;
};

#endif // ADTMODELBUILDER_H
