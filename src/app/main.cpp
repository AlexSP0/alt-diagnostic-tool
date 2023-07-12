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

#include "adtapp.h"

#include <QApplication>
#include <QDebug>
#include <QTranslator>

#include "version.h"

QString getVersion()
{
    return QString("%1.%2.%3").arg(0).arg(ADT_VERSION_MINOR).arg(ADT_VERSION_PATCH);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // NOTE: set app variables which will be used to
    // construct settings path
    app.setOrganizationName(QCoreApplication::translate("main", "BaseALT Ltd."));
    app.setOrganizationDomain("basealt.ru");
    app.setApplicationName("ALT Diagnostic Tool");
    app.setApplicationVersion(getVersion());

    QLocale locale;

    QTranslator translator;
    QString language = locale.system().name().split("_").at(0);
    translator.load("app_" + language, ".");
    app.installTranslator(&translator);

    ADTApp adtApp(&app, locale.system().name());

    return adtApp.runApp();
}
