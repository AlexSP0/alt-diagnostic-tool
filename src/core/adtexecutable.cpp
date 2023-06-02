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
    : m_id(0)
    , m_name("")
    , m_category("")
    , m_icon("")
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
{}

void ADTExecutable::getStdout(QString out)
{
    m_stringStdout.append(out);
}

void ADTExecutable::getStderr(QString err)
{
    m_stringStderr.append(err);
}
