#ifndef TREEPROXYMODEL_H
#define TREEPROXYMODEL_H

#include <QSortFilterProxyModel>

class TreeProxyModel : public QSortFilterProxyModel
{
public:
    TreeProxyModel();
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // TREEPROXYMODEL_H
