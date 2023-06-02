/***********************************************************************************************************************
**
** Copyright (C) 2023 BaseALT Ltd. <org@basealt.ru>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#include "adtmodelbuilderstrategyfromjson.h"

#include "../core/adtjsonloader.h"
#include "../core/treemodelbuilderimpl.h"

#include <QMessageBox>

ADTModelBuilderStrategyFromJson::ADTModelBuilderStrategyFromJson(QString filename)
    : m_fileName(filename)
    , m_builder(new TreeModelBuilderImpl())
{}

std::unique_ptr<TreeModel> ADTModelBuilderStrategyFromJson::buildModel()
{
    QJsonDocument checks = ADTJsonLoader::loadDocument(m_fileName, m_checksSection);
    //QJsonDocument resolvers = ADTJsonLoader::loadDocument(m_dataFile, m_resolversSection);

    if (checks.isEmpty())
    {
        QMessageBox checksMsgBox;
        checksMsgBox.setText(QObject::tr("Checks file is missing or corrupted. Cannot continue working!"));
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
