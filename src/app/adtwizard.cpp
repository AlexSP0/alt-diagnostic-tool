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
#include "../core/basereportcollector.h"
#include "jsonloadbuilderstrategy.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>
#include <QPushButton>

#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

const int LAST_PAGE_INDEX = -1;

ADTWizard::ADTWizard(QJsonDocument &checksData,
                     QJsonDocument &resolversData,
                     QString &serviceName,
                     QString &path,
                     QString &interfaceName,
                     QWidget *parent)
    : QWizard(parent)
    , checks(new ADTExecutableRunner(checksData, serviceName, path, interfaceName))
    , resolvers(new ADTExecutableRunner(resolversData, serviceName, path, interfaceName))
    , reportsCollector(new BaseReportCollector())
    , introPage(new IntroWizardPage())
    , checkPage(new CheckWizardPage(checks.get()))
    , repairPage(new RepairWizardPage(resolvers.get()))
    , finishPage(new FinishWizardPage())
    , slotConnector(new SlotConnector())
    , serviceWatcher(new QDBusServiceWatcher(serviceName,
                                             QDBusConnection::systemBus(),
                                             QDBusServiceWatcher::WatchForOwnerChange))
    , previousPage(0)
{
    setPage(Intro_Page, introPage.data());
    setPage(Check_Page, checkPage.data());
    setPage(Repair_Page, repairPage.data());
    setPage(Finish_Page, finishPage.data());

    setStartId(Intro_Page);

    disconnect(button(QWizard::CancelButton), SIGNAL(clicked()), this, SLOT(reject()));
    connect(button(QWizard::CancelButton),
            &QPushButton::clicked,
            this,
            &ADTWizard::cancelButtonPressed);

    connect(this, &QWizard::currentIdChanged, this, &ADTWizard::currentIdChanged);

    connect(serviceWatcher.get(),
            &QDBusServiceWatcher::serviceUnregistered,
            this,
            &ADTWizard::dBusServiceUnregistered);

    connect(serviceWatcher.get(),
            &QDBusServiceWatcher::serviceRegistered,
            this,
            &ADTWizard::dBusServiceRegistered);

    setButtonText(QWizard::CustomButton1, "Save");

    connect(button(QWizard::CustomButton1),
            &QPushButton::clicked,
            this,
            &ADTWizard::onSaveButtonPressed);
}

int ADTWizard::nextId() const
{
    auto repairPg = static_cast<RepairWizardPage *>(page(ADTWizard::Repair_Page));
    auto checkPg  = static_cast<CheckWizardPage *>(page(ADTWizard::Check_Page));

    int currentPage = currentId();

    switch (currentPage)
    {
    case Intro_Page:
        return (checkPg->getAmountOfTasks() != 0 ? Check_Page : Finish_Page);

    case Check_Page:
        return (repairPg->getAmountOfTasks() != 0 && checkPg->isAnyErrorsInTasks() ? Repair_Page
                                                                                   : Finish_Page);

    case Repair_Page:
        return Finish_Page;

    case Finish_Page:
        return LAST_PAGE_INDEX;
    }

    return LAST_PAGE_INDEX;
}

bool ADTWizard::isServiceActive()
{
    return isServiceRegistered;
}

void ADTWizard::cancelButtonPressed()
{
    ICancelButtonHandler *handler = dynamic_cast<ICancelButtonHandler *>(currentPage());

    if (handler)
    {
        handler->cancelButtonPressed();
    }
}

void ADTWizard::currentIdChanged(int currentPageId)
{
    connectSlotInCurrentPage(currentPageId);
    disconnectSlotInPreviousPage();

    previousPage = currentPageId;

    switch (currentPageId)
    {
    case Check_Page:
        checkPage.data()->runTasks();
        break;

    case Repair_Page:
        repairPage.data()->runTasks();
        break;

    default:
        break;
    }
}

void ADTWizard::dBusServiceUnregistered()
{
    isServiceRegistered = false;

    switch (currentId())
    {
    case Check_Page:
        checkPage->currentDBusServiceUnregistered();
        break;
    case Repair_Page:
        repairPage->currentDBusServiceUnregistered();
        break;
    }
}

void ADTWizard::dBusServiceRegistered()
{
    isServiceRegistered = true;
}

void ADTWizard::onSaveButtonPressed()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    "reports.txt",
                                                    tr("Text file (*.txt)"));

    if (fileName.isEmpty())
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setText(QObject::tr("File name is empty! Cannot save the reports. "));
        errorMsgBox.setIcon(QMessageBox::Warning);
        errorMsgBox.exec();

        return;
    }

    QFile outputFile(fileName);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox errorMsgBox;
        errorMsgBox.setText(QObject::tr("Cannot open specified file! "));
        errorMsgBox.setIcon(QMessageBox::Warning);
        errorMsgBox.exec();

        return;
    }

    QTextStream textStream(&outputFile);
    textStream << reportsCollector->getReport(checks.get(), IReportsCollector::ReportType::All);

    textStream << reportsCollector->getReport(resolvers.get(), IReportsCollector::ReportType::All);

    outputFile.flush();
    outputFile.close();
}

void ADTWizard::connectSlotInCurrentPage(int currentPageId)
{
    setOption(QWizard::HaveCustomButton1, false);

    switch (currentPageId)
    {
    case ADTWizard::Check_Page:

        slotConnector->connectSignals(checks.get(),
                                      static_cast<AbstractExecutablePage *>(checkPage.get()));
        break;

    case ADTWizard::Repair_Page:
        slotConnector->connectSignals(resolvers.get(),
                                      static_cast<AbstractExecutablePage *>(repairPage.get()));
        break;

    case ADTWizard::Intro_Page:
        break;

    case ADTWizard::Finish_Page:
        setOption(QWizard::HaveCustomButton1, true);
        break;
    default:
        break;
    }
}

void ADTWizard::disconnectSlotInPreviousPage()
{
    switch (previousPage)
    {
    case ADTWizard::Check_Page:

        slotConnector->disconnectSignals(checks.get(),
                                         static_cast<AbstractExecutablePage *>(checkPage.get()));
        break;

    case ADTWizard::Repair_Page:
        slotConnector->disconnectSignals(resolvers.get(),
                                         static_cast<AbstractExecutablePage *>(repairPage.get()));
        break;

    case ADTWizard::Intro_Page:
    case ADTWizard::FinishButton:
    default:
        break;
    }
}
