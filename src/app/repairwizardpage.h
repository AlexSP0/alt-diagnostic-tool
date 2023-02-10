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

#ifndef REPAIRWIZARDPAGE_H
#define REPAIRWIZARDPAGE_H

#include "../core/adtexecutablerunner.h"

#include "abstractexecutablepage.h"
#include "executablestatuswidget.h"

#include <QLabel>
#include <QPlainTextEdit>
#include <QThread>
#include <QVBoxLayout>
#include <QWizardPage>

namespace Ui
{
class RepairWizardPage;
}

class RepairWizardPage : public AbstractExecutablePage
{
    Q_OBJECT

public:
    RepairWizardPage(ADTExecutableRunner *run, QWidget *parent = nullptr);

    virtual bool isComplete() const override;

private slots:

    void cancelButtonPressed(int currentPage);

private:
    RepairWizardPage(const RepairWizardPage &) = delete;
    RepairWizardPage(RepairWizardPage &&)      = delete;
    RepairWizardPage &operator=(const RepairWizardPage &) = delete;
    RepairWizardPage &operator=(RepairWizardPage &&) = delete;
};

#endif // REPAIRWIZARDPAGE_H
