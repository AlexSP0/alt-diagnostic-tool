#include "adtmodelbuilder.h"
#include "../core/adtjsonloader.h"
#include "../core/treemodelbuilderimpl.h"

#include <QJsonDocument>
#include <QMessageBox>

ADTModelBuilder::ADTModelBuilder(ADTModelBuilderStrategyInterface *builderStrategy)
    : m_builder(builderStrategy)
{}

std::unique_ptr<TreeModel> ADTModelBuilder::buildModel()
{
    return m_builder->buildModel();
}
