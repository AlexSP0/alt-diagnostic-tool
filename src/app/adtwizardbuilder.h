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

#ifndef ADTWIZARDBUILDER_H
#define ADTWIZARDBUILDER_H

#include "adtwizard.h"

#include <iadtwizardbuilderstrategy.h>

class ADTWizardBuilder
{
public:
    ADTWizardBuilder();
    ~ADTWizardBuilder();

    ADTWizardBuilder &withFile(const QString &filename);
    ADTWizardBuilder &withChecksSection(const QString &checksSectionName);
    ADTWizardBuilder &withResolversSections(const QString &resolversSectionName);
    ADTWizardBuilder &withService(const QString &serviceName);
    ADTWizardBuilder &withPath(const QString &path);
    ADTWizardBuilder &withInterface(const QString &interfaceName);

    std::unique_ptr<ADTWizard> build(std::unique_ptr<IADTWizardBuilderStrategy> strategy);

private:
    QString m_dataFile         = "data.json";
    QString m_checksSection    = "checks";
    QString m_resolversSection = "resolvers";
    QString m_serviceName      = "ru.basealt.alterator";
    QString m_path             = "/ru/basealt/alterator/executor";
    QString m_interfaceName    = "ru.basealt.alterator.executor";
};

#endif // ADTWIZARDBUILDER_H
