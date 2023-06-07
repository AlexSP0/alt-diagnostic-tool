#ifndef TREEMODELBULDERFROMEXECUTABLE_H
#define TREEMODELBULDERFROMEXECUTABLE_H

#include "treemodelbuilderinterface.h"

class TreeModelBulderFromExecutable : public TreeModelBuilderInterface
{
public:
    TreeModelBulderFromExecutable()  = default;
    ~TreeModelBulderFromExecutable() = default;

public:
    std::unique_ptr<TreeModel> buildModel(std::vector<ADTExecutable>);
};

#endif // TREEMODELBULDERFROMEXECUTABLE_H
