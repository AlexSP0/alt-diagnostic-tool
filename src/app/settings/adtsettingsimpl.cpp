/***********************************************************************************************************************
**
** Copyright (C) 2024 BaseALT Ltd. <org@basealt.ru>
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

#include "adtsettingsimpl.h"

#include <memory>
#include <QMainWindow>
#include <QSettings>

const char *const REPORT_PATH_KEY     = "defaultPath";
const char *const DEFAULT_REPORT_PATH = "~/";

const char *const REPORT_FILENAME_TEMPLATE_KEY     = "defaultReportTemplate";
const char *const DEFAULT_REPORT_FILENAME_TEMPLATE = "report_%d_%m_%y.zip";

class ADTSettingsPrivate
{
public:
    ADTSettingsPrivate()
        : m_settings(){};

    ~ADTSettingsPrivate() = default;

public:
    QSettings m_settings;

private:
    ADTSettingsPrivate(const ADTSettingsPrivate &) = delete;
    ADTSettingsPrivate(ADTSettingsPrivate &&)      = delete;
    ADTSettingsPrivate &operator=(const ADTSettingsPrivate &) = delete;
    ADTSettingsPrivate &operator=(ADTSettingsPrivate &&) = delete;
};

ADTSettingsImpl::ADTSettingsImpl()
    : d(std::make_unique<ADTSettingsPrivate>())
{}

ADTSettingsImpl::~ADTSettingsImpl() {}

void ADTSettingsImpl::restoreWindowSettings(QWidget *window)
{
    if (!window)
    {
        return;
    }

    const QByteArray geometry = d->m_settings.value(window->windowTitle()).toByteArray();
    window->restoreGeometry(geometry);

    QMainWindow *mainWindow = dynamic_cast<QMainWindow *>(window);
    if (mainWindow)
    {
        const QByteArray state = d->m_settings.value(QString(mainWindow->windowTitle() + "state")).toByteArray();
        mainWindow->restoreState(state);
    }
}

void ADTSettingsImpl::saveWindowsSettings(QWidget *window)
{
    if (!window)
    {
        return;
    }

    const QByteArray geometry = window->saveGeometry();
    d->m_settings.setValue(window->windowTitle(), geometry);

    QMainWindow *mainWindow = dynamic_cast<QMainWindow *>(window);
    if (mainWindow)
    {
        const QByteArray state = mainWindow->saveState();
        d->m_settings.setValue(QString(mainWindow->windowTitle() + "state"), state);
    }
}

void ADTSettingsImpl::saveReportPath(QString path)
{
    if (path.isEmpty())
    {
        return;
    }

    d->m_settings.setValue(REPORT_PATH_KEY, QVariant(path));
}

QString ADTSettingsImpl::getReportPath()
{
    return d->m_settings.value(REPORT_PATH_KEY, QVariant(QString(DEFAULT_REPORT_PATH))).toString();
}

void ADTSettingsImpl::saveReportFilenameTemplate(QString templ)
{
    if (templ.isEmpty())
    {
        return;
    }

    d->m_settings.setValue(REPORT_FILENAME_TEMPLATE_KEY, QVariant(templ));
}

QString ADTSettingsImpl::getReportFilenameTemplate()
{
    return d->m_settings.value(REPORT_FILENAME_TEMPLATE_KEY, QVariant(QString(DEFAULT_REPORT_FILENAME_TEMPLATE)))
        .toString();
}
