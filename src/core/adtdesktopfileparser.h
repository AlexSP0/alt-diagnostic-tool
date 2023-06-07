#ifndef ADTDESKTOPFILEPARSER_H
#define ADTDESKTOPFILEPARSER_H

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

public:
    ADTDesktopFileParser(QString filename);

    QList<QString> getGroupsList();
    QList<QString> getKeysListOfGroup(QString group);
    QString getKeyLocale(QString keyName);

private:
    QString getKeyNameWithoutLocale(QString keyName);

private:
    Sections m_sections;
};

#endif // ADTDESKTOPFILEPARSER_H
