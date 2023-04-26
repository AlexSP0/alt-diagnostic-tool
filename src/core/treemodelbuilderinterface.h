#ifndef TREEMODELBUILDERINTERFACE_H
#define TREEMODELBUILDERINTERFACE_H

#include "treemodel.h"

#include <memory>

class TreeModelBuilderInterface
{
public:
    TreeModelBuilderInterface() = default;

    virtual ~TreeModelBuilderInterface() = default;

    virtual std::unique_ptr<TreeModel> buildModel(QJsonDocument *document) = 0;
};

#endif // TREEMODELBUILDERINTERFACE_H
