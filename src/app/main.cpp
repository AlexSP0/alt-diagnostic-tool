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

#include "adtwizard.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>

#include "../core/adtjsonloader.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // NOTE: set app variables which will be used to
    // construct settings path
    app.setOrganizationName(QCoreApplication::translate("main", "BaseALT Ltd."));
    app.setOrganizationDomain("basealt.ru");
    app.setApplicationName("ALT Diagnostic tool");
    app.setApplicationVersion("0.1.0");

    QJsonDocument checks    = ADTJsonLoader::loadDocument("data.json", "checks");
    QJsonDocument resolvers = ADTJsonLoader::loadDocument("data.json", "resolvers");

    if (checks.isEmpty())
    {
        QMessageBox checksMsgBox;
        checksMsgBox.setText(
            QObject::tr("Checks file is missing or corrupted. Cannot continue working!"));
        checksMsgBox.setIcon(QMessageBox::Critical);
        checksMsgBox.exec();
        exit(1);
    }

    if (resolvers.isEmpty())
    {
        QMessageBox resolversMsgBox;
        resolversMsgBox.setText(QObject::tr(
            "The data file does not contain data about the resolvers, only checks are possible."));
        resolversMsgBox.setIcon(QMessageBox::Warning);
        resolversMsgBox.exec();
    }

    ADTWizard wizard(checks, resolvers);

    wizard.show();

    return app.exec();
}
