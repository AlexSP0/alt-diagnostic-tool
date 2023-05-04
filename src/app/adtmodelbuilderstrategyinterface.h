#ifndef ADTMODELBUILDERSTRATEGYINTERFACE_H
#define ADTMODELBUILDERSTRATEGYINTERFACE_H

#include "../core/treemodel.h"
#include <memory>

class ADTModelBuilderStrategyInterface
{
public:
    virtual std::unique_ptr<TreeModel> buildModel() = 0;
    virtual ~ADTModelBuilderStrategyInterface()     = default;
};

#endif // ADTMODELBUILDERSTRATEGYINTERFACE_H
