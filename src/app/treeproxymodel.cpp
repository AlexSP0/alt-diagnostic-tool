#include "treeproxymodel.h"

TreeProxyModel::TreeProxyModel() {}

bool TreeProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex source_index = sourceModel()->index(source_row, this->filterKeyColumn(), source_parent);
    if (source_index.isValid())
    {
        auto data = source_index.data(Qt::CheckStateRole);
        if (data.isValid())
        {
            return data.value<Qt::CheckState>() == Qt::Checked;
        }
    }

    return false;
}
