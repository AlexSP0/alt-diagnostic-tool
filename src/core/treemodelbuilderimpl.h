#ifndef TREEMODELBUILDERIMPL_H
#define TREEMODELBUILDERIMPL_H

#include "treemodelbuilderinterface.h"

#include <QJsonDocument>

class TreeModelBuilderImpl : public TreeModelBuilderInterface
{
public:
    TreeModelBuilderImpl()          = default;
    virtual ~TreeModelBuilderImpl() = default;

    // TreeModelBuilderInterface interface
public:
    std::unique_ptr<TreeModel> buildModel(QJsonDocument *document) override;
};

#endif // TREEMODELBUILDERIMPL_H
