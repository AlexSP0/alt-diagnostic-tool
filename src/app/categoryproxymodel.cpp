#include "categoryproxymodel.h"
#include "../core/adtexecutable.h"

CategoryProxyModel::CategoryProxyModel(const QString &category)
    : selectedCategory(category)
{}

bool CategoryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex source_index = sourceModel()->index(source_row, this->filterKeyColumn(), source_parent);
    if (source_index.isValid())
    {
        auto data = source_index.data(Qt::UserRole + 1);
        if (data.isValid())
        {
            return data.value<ADTExecutable *>()->m_category == selectedCategory;
        }
    }

    return false;
}

void CategoryProxyModel::setSelectedCategory(const QString &category)
{
    selectedCategory = category;
}

QString CategoryProxyModel::getSelectedCategory() const
{
    return selectedCategory;
}
