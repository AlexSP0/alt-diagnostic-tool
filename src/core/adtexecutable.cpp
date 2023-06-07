/***********************************************************************************************************************
**
** Copyright (C) 2022 BaseALT Ltd. <org@basealt.ru>
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

#include "adtexecutable.h"

#include <QJsonArray>

ADTExecutable::ADTExecutable()
    : m_id("")
    , m_name("")
    , m_category("")
    , m_icon("")
    , m_description("")
    , m_dbusServiceName("")
    , m_dbusPath("")
    , m_dbusInteface("")
    , m_method("")
    , m_args("")
    , m_exit_code(-1)
    , m_stringStdout("")
    , m_stringStderr("")
    , m_bytesStdout({})
    , m_bytesStderr({})
    , m_nameLocaleStorage()
    , m_categoryLocaleStorage()
    , m_descriptionLocaleStorage()
{}

void ADTExecutable::setLocate(QString locale)
{
    auto nameIt = m_nameLocaleStorage.find(locale);
    if (nameIt != m_nameLocaleStorage.end())
    {
        m_name = *nameIt;
    }

    auto categoryIt = m_categoryLocaleStorage.find(locale);
    if (categoryIt != m_categoryLocaleStorage.end())
    {
        m_category = *categoryIt;
    }

    auto descriptionIt = m_descriptionLocaleStorage.find(locale);
    if (descriptionIt != m_descriptionLocaleStorage.end())
    {
        m_description = *descriptionIt;
    }
}

void ADTExecutable::getStdout(QString out)
{
    m_stringStdout.append(out);
}

void ADTExecutable::getStderr(QString err)
{
    m_stringStderr.append(err);
}
