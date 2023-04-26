#include "adtmodelbuilder.h"
#include "../core/adtjsonloader.h"
#include "../core/treemodelbuilderimpl.h"

#include <QJsonDocument>
#include <QMessageBox>

ADTModelBuilder::ADTModelBuilder()
    : m_builder(new TreeModelBuilderImpl())
{}

std::unique_ptr<TreeModel> ADTModelBuilder::buildModel()
{
    QJsonDocument checks = ADTJsonLoader::loadDocument(m_dataFile, m_checksSection);
    //QJsonDocument resolvers = ADTJsonLoader::loadDocument(m_dataFile, m_resolversSection);

    if (checks.isEmpty())
    {
        QMessageBox checksMsgBox;
        checksMsgBox.setText(
            QObject::tr("Checks file is missing or corrupted. Cannot continue working!"));
        checksMsgBox.setIcon(QMessageBox::Critical);
        checksMsgBox.exec();
        return nullptr;
    }

    /*if (resolvers.isEmpty())
    {
        QMessageBox resolversMsgBox;
        resolversMsgBox.setText(QObject::tr(
            "The data file does not contain data about the resolvers, only checks are possible."));
        resolversMsgBox.setIcon(QMessageBox::Warning);
        resolversMsgBox.exec();
    }*/

    auto model = m_builder->buildModel(&checks);
    return model;
}
