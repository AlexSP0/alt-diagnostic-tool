#include "adtdesktopfileparser.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <QDebug>

ADTDesktopFileParser::ADTDesktopFileParser(QString filename)
    : m_sections()
{
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini(filename.toStdString(), pt);

        for (auto &section : pt)
        {
            qWarning() << "[" << section.first.c_str() << "]\n";

            for (auto &key : section.second)
            {
                qWarning() << key.first.c_str() << "=" << key.second.get_value("").c_str() << "\n";

                Section &currentSections = m_sections[QString(section.first.c_str())];

                currentSections.insert(getKeyNameWithoutLocale(QString(key.first.c_str())),
                                       IniFileKey{getKeyNameWithoutLocale(QString(key.first.c_str())),
                                                  getKeyLocale(QString(key.first.c_str())),
                                                  QVariant(key.second.get_value("").c_str())});
            }
        }
    }
    catch (std::exception &e)
    {
        qDebug() << "ERROR: can't parse desktop file!"
                 << "\n";
    }
}

QList<QString> ADTDesktopFileParser::getGroupsList()
{
    return m_sections.keys();
}

QList<QString> ADTDesktopFileParser::getKeysListOfGroup(QString group)
{
    return m_sections[group].keys();
}

QString ADTDesktopFileParser::getKeyLocale(QString keyName)
{
    auto indexOfOpeningBracket = keyName.lastIndexOf("[");
    auto indexOfClosingBracket = keyName.lastIndexOf("]");

    if (indexOfOpeningBracket >= indexOfClosingBracket || indexOfOpeningBracket == -1 || indexOfClosingBracket == -1)
    {
        return QString();
    }
    return keyName.mid(indexOfOpeningBracket + 1, indexOfClosingBracket - indexOfOpeningBracket - 1);
}

QString ADTDesktopFileParser::getKeyNameWithoutLocale(QString keyName)
{
    auto indexOfOpeningBracket = keyName.lastIndexOf("[");
    auto indexOfClosingBracket = keyName.lastIndexOf("]");

    if (indexOfOpeningBracket >= indexOfClosingBracket || indexOfOpeningBracket == -1 || indexOfClosingBracket == -1)
    {
        return keyName;
    }

    return keyName.mid(0, keyName.size() - indexOfOpeningBracket);
}
