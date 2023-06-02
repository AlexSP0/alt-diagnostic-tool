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

#ifndef ADTEXECUTABLE_H
#define ADTEXECUTABLE_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class ADTExecutable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id MEMBER m_id)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(QString category MEMBER m_category)
    Q_PROPERTY(QString icon MEMBER m_icon)
    Q_PROPERTY(QString dbusServiceName MEMBER m_dbusServiceName)
    Q_PROPERTY(QString dbusPath MEMBER m_dbusPath)
    Q_PROPERTY(QString dbusInterface MEMBER m_dbusInteface)
    Q_PROPERTY(QString dbusMethod MEMBER m_method)
    Q_PROPERTY(QString args MEMBER m_args)
    Q_PROPERTY(int m_exit_code MEMBER m_exit_code)

public:
    int m_id;
    QString m_name;
    QString m_category;
    QString m_icon;
    QString m_dbusServiceName;
    QString m_dbusPath;
    QString m_dbusInteface;
    QString m_method;
    QString m_args;
    int m_exit_code;

    QString m_stringStdout;
    QString m_stringStderr;

    QByteArray m_bytesStdout;
    QByteArray m_bytesStderr;

public:
    ADTExecutable();

public slots:
    void getStdout(QString out);
    void getStderr(QString err);
};

#endif //ADTEXECUTABLE_H
