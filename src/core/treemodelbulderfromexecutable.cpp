#include "treemodelbulderfromexecutable.h"

std::unique_ptr<TreeModel> TreeModelBulderFromExecutable::buildModel(std::vector<std::unique_ptr<ADTExecutable>> elements)
{
    std::unique_ptr<TreeModel> model = std::make_unique<TreeModel>();

    QModelIndex rootIndex = model->parent(QModelIndex());

    TreeItem *rootItem = static_cast<TreeItem *>(rootIndex.internalPointer());

    QMap<QString, TreeItem *> categoriesMap;

    for (size_t i = 0; i < elements.size(); i++)
    {
        //auto task = std::make_unique<ADTExecutable>();

        //QJsonObject obj = tasksArray[i].toObject();

        //ADTJsonConverter::JSonToObject(*task.get(), &obj);

        auto it = categoriesMap.find(elements.at(i)->m_category);
        if (it == categoriesMap.end())
        {
            TreeItem *categoryItem = new TreeItem(QList<QVariant>{}, TreeItem::categoryItem, rootItem);

            rootItem->appendChild(categoryItem);

            categoriesMap[elements.at(i)->m_category] = categoryItem;

            auto categoryTask = std::make_unique<ADTExecutable>();

            categoryTask->m_description = elements.at(i)->m_description;

            categoryTask->m_name = elements.at(i)->m_category;

            categoryItem->setExecutable(std::move(categoryTask));

            TreeItem *checkItem = new TreeItem(QList<QVariant>{}, TreeItem::checkItem, categoryItem);

            checkItem->setExecutable(std::move(elements.at(i)));

            categoryItem->appendChild(checkItem);
        }
        else
        {
            TreeItem *categoryItem = categoriesMap[elements.at(i)->m_category];

            if (categoryItem)
            {
                TreeItem *checkItem = new TreeItem(QList<QVariant>{}, TreeItem::checkItem, categoryItem);

                categoryItem->appendChild(checkItem);

                checkItem->setExecutable(std::move(elements.at(i)));
            }
        }
    }

    return model;
}
