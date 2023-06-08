#ifndef ADTDESKTOPFILEPARSER_H
#define ADTDESKTOPFILEPARSER_H

#include "adtexecutable.h"

#include <QString>
#include <QVariant>

struct IniFileKey
{
    QString keyName{};
    QString keyLocale{};
    QVariant value{};
};

class ADTDesktopFileParser
{
public:
    using Section  = QMultiMap<QString, IniFileKey>;
    using Sections = QMap<QString, Section>;

    const QString DEFAULT_ICON = "system-run";

public:
    ADTDesktopFileParser(QString data);

    std::unique_ptr<ADTExecutable> buildExecutable();

    QList<QString> getGroupsList() const;
    QList<QString> getKeysListOfGroup(QString group) const;

    QString getKeyLocale(QString keyName);

private:
    QString getKeyNameWithoutLocale(QString keyName);
    bool setDbusFields(QString &category, ADTExecutable *object);
    bool setIcon(QString &category, ADTExecutable *object);
    bool setName(QString &category, ADTExecutable *object);
    bool setCategory(QString &category, ADTExecutable *object);
    bool setDescription(QString &category, ADTExecutable *object);

private:
    Sections m_sections;
};

#endif // ADTDESKTOPFILEPARSER_H
