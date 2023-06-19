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

#include "clcontroller.h"

#include <iostream>

class CLControllerPrivate
{
public:
    CLControllerPrivate(TreeModel *model, CommandLineOptions *options)
        : m_options(options)
        , m_model(model)
    {}
    ~CLControllerPrivate() {}

    CommandLineOptions *m_options;
    TreeModel *m_model;

private:
    CLControllerPrivate(const CLControllerPrivate &) = delete;
    CLControllerPrivate(CLControllerPrivate &&)      = delete;
    CLControllerPrivate &operator=(const CLControllerPrivate &) = delete;
    CLControllerPrivate &operator=(CLControllerPrivate &&) = delete;
};

CLController::CLController(TreeModel *model, CommandLineOptions *options)
    : d(new CLControllerPrivate(model, options))
{}

CLController::~CLController()
{
    delete d;
}

int CLController::listObjects()
{
    std::cout << "list all objects" << std::endl;
    return 0;
}

int CLController::listTestsOfObject(QString object)
{
    std::cout << "list test of " << object.toStdString() << "object" << std::endl;
    return 0;
}

int CLController::runAllTestsOfObject(QString object)
{
    std::cout << "run all tests of " << object.toStdString() << "object" << std::endl;
    return 0;
}

int CLController::runSpecifiedTestOfObject(QString object, QString test)
{
    std::cout << "run" << test.toStdString() << " test of " << object.toStdString() << "object" << std::endl;
    return 0;
}

int CLController::runApp()
{
    int result = -1;

    switch (d->m_options->action)
    {
    case CommandLineOptions::Action::listOfObjects:
        result = listObjects();
        break;
    case CommandLineOptions::Action::listOfTestFromSpecifiedObject:
        result = listTestsOfObject(d->m_options->objectName);
        break;
    case CommandLineOptions::Action::runAllTestFromSpecifiedObject:
        result = runAllTestsOfObject(d->m_options->objectName);
        break;
    case CommandLineOptions::Action::runSpecifiedTestFromSpecifiedObject:
        result = runSpecifiedTestOfObject(d->m_options->objectName, d->m_options->testName);
        break;
    default:
        break;
    }

    return result;
}
