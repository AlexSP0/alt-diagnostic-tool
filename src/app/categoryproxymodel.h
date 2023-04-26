#ifndef CATEGORYPROXYMODEL_H
#define CATEGORYPROXYMODEL_H

#include <QSortFilterProxyModel>

class CategoryProxyModel : public QSortFilterProxyModel
{
public:
    CategoryProxyModel(const QString &category = "");
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    void setSelectedCategory(const QString &category);
    QString getSelectedCategory() const;

private:
    QString selectedCategory;
};

#endif // CATEGORYPROXYMODEL_H
