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

//#include "dbuschecker.h"

#include "adtapp.h"

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // NOTE: set app variables which will be used to
    // construct settings path
    app.setOrganizationName(QCoreApplication::translate("main", "BaseALT Ltd."));
    app.setOrganizationDomain("basealt.ru");
    app.setApplicationName("ALT Diagnostic tool");
    app.setApplicationVersion("0.1.0");

    QTranslator translator;
    translator.load("app_ru", ".");
    app.installTranslator(&translator);

    //    if (!DBusChecker::checkDBusServiceOnSystemBus(DBUS_SERVICE_NAME, PATH_TO_DBUS_OBJECT, DBUS_INTERFACE_NAME))
    //    {
    //        QMessageBox errorMsgBox;
    //        errorMsgBox.setText(QObject::tr("Cannot connect to service. Restart the service and run ADT again."));
    //        errorMsgBox.setIcon(QMessageBox::Critical);
    //        errorMsgBox.exec();

    //        exit(1);
    //    }

    ADTApp adtApp(&app);

    //return controller->runSpecifiedTestOfObject("diag2", "check_common_packages");

    return adtApp.runApp();
}
