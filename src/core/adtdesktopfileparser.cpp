#include "adtdesktopfileparser.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <QDebug>

ADTDesktopFileParser::ADTDesktopFileParser(QString data)
    : m_sections()
    , m_testLists()
{
    std::istringstream iStream(data.toStdString());

    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini(iStream, pt);

        for (auto &section : pt)
        {
            for (auto &key : section.second)
            {
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
        qWarning() << "ERROR: can't parse desktop file: " << data << "\n";
    }
}

ADTDesktopFileParser::ADTDesktopFileParser(QString data, QStringList testLists)
    : ADTDesktopFileParser{data}
{
    m_testLists = testLists;
}

std::unique_ptr<ADTExecutable> ADTDesktopFileParser::buildCategoryExecutable()
{
    std::unique_ptr<ADTExecutable> newADTExecutable = std::make_unique<ADTExecutable>();

    QList<QString> groups = getGroupsList();

    if (groups.isEmpty() || groups.at(0).isEmpty())
    {
        return nullptr;
    }

    newADTExecutable->m_id = groups.at(0);

    QList<QString> listOfKeys = getKeysListOfGroup(newADTExecutable->m_id);

    if (listOfKeys.empty())
    {
        return nullptr;
    }

    if (!setDbusFields(newADTExecutable->m_id, newADTExecutable.get()))
    {
        return nullptr;
    }

    setIcon(newADTExecutable->m_id, newADTExecutable.get());

    setName(newADTExecutable->m_id, newADTExecutable.get());

    setCategory(newADTExecutable->m_id, newADTExecutable.get());

    setDescription(newADTExecutable->m_id, newADTExecutable.get());

    newADTExecutable->m_type = ADTExecutable::ExecutableType::categoryType;

    return newADTExecutable;
}

std::unique_ptr<ADTExecutable> ADTDesktopFileParser::buildTestExecutable(QString test, ADTExecutable *categoryExecutable)
{
    std::unique_ptr<ADTExecutable> result = std::make_unique<ADTExecutable>();

    if (!categoryExecutable)
    {
        return nullptr;
    }

    result->m_id              = test;
    result->m_type            = ADTExecutable::ExecutableType::executableType;
    result->m_name            = test;
    result->m_category        = categoryExecutable->m_category;
    result->m_icon            = categoryExecutable->m_icon;
    result->m_description     = categoryExecutable->m_description;
    result->m_dbusServiceName = categoryExecutable->m_dbusServiceName;
    result->m_dbusPath        = categoryExecutable->m_dbusPath;
    result->m_dbusInteface    = categoryExecutable->m_dbusInteface;
    result->m_method          = categoryExecutable->m_method;
    result->m_args            = test;
    result->m_exit_code       = categoryExecutable->m_exit_code;

    return result;
}

std::vector<std::unique_ptr<ADTExecutable>> ADTDesktopFileParser::buildExecutables()
{
    std::vector<std::unique_ptr<ADTExecutable>> results;

    std::unique_ptr<ADTExecutable> categoryExecutable = buildCategoryExecutable();

    if (!categoryExecutable.get())
    {
        return results;
    }

    ADTExecutable *currentCategory = categoryExecutable.get();

    results.push_back(std::move(categoryExecutable));

    for (QString currentTest : m_testLists)
    {
        std::unique_ptr<ADTExecutable> test = buildTestExecutable(currentTest, currentCategory);

        if (!test.get())
        {
            return results;
        }
        results.push_back(std::move(test));
    }

    return results;
}

QList<QString> ADTDesktopFileParser::getGroupsList() const
{
    return m_sections.keys();
}

QList<QString> ADTDesktopFileParser::getKeysListOfGroup(QString group) const
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

    return keyName.mid(0, indexOfOpeningBracket);
}

bool ADTDesktopFileParser::setDbusFields(QString &category, ADTExecutable *object)
{
    Section section = m_sections[category];

    auto dbusServiceNameIt = section.find("dbusServiceName");
    if (dbusServiceNameIt == section.end())
    {
        return false;
    }
    object->m_dbusServiceName = dbusServiceNameIt->value.toString();

    auto dbusPathNameIt = section.find("dbusPath");
    if (dbusPathNameIt == section.end())
    {
        return false;
    }
    object->m_dbusPath = dbusPathNameIt->value.toString();

    auto dbusInterfaceIt = section.find("dbusInteface");
    if (dbusInterfaceIt == section.end())
    {
        return false;
    }
    object->m_dbusInteface = dbusInterfaceIt->value.toString();

    auto dbusMethodIt = section.find("dbusMethod");
    if (dbusMethodIt == section.end())
    {
        return false;
    }
    object->m_method = dbusMethodIt->value.toString();

    auto dbusMethodArgsIt = section.find("args");
    if (dbusMethodArgsIt == section.end())
    {
        return false;
    }
    object->m_args = dbusMethodArgsIt->value.toString();

    return true;
}

bool ADTDesktopFileParser::setIcon(QString &category, ADTExecutable *object)
{
    Section section = m_sections[category];
    auto iconIt     = section.find("icon");

    if (iconIt == section.end())
    {
        object->m_icon = DEFAULT_ICON;
    }
    else
    {
        object->m_icon = iconIt->value.toString();
    }

    return true;
}

bool ADTDesktopFileParser::setName(QString &category, ADTExecutable *object)
{
    Section section = m_sections[category];
    auto nameIt     = section.find("name");

    if (nameIt == section.end())
    {
        object->m_name = "";
        return false;
    }

    QList<IniFileKey> listOfKeys = section.values("name");

    for (IniFileKey &currentIniFileKey : listOfKeys)
    {
        if (currentIniFileKey.keyLocale.isEmpty())
        {
            object->m_name = currentIniFileKey.value.toString();
        }
        object->m_nameLocaleStorage.insert(currentIniFileKey.keyLocale, currentIniFileKey.value.toString());
    }

    return true;
}

bool ADTDesktopFileParser::setCategory(QString &category, ADTExecutable *object)
{
    Section section = m_sections[category];
    auto nameIt     = section.find("category");

    if (nameIt == section.end())
    {
        object->m_category = "";
        return false;
    }

    QList<IniFileKey> listOfKeys = section.values("category");

    for (IniFileKey &currentIniFileKey : listOfKeys)
    {
        if (currentIniFileKey.keyLocale.isEmpty())
        {
            object->m_category = currentIniFileKey.value.toString();
        }
        object->m_categoryLocaleStorage.insert(currentIniFileKey.keyLocale, currentIniFileKey.value.toString());
    }

    return true;
}

bool ADTDesktopFileParser::setDescription(QString &category, ADTExecutable *object)
{
    Section section = m_sections[category];
    auto nameIt     = section.find("description");

    if (nameIt == section.end())
    {
        object->m_description = "";
        return false;
    }

    QList<IniFileKey> listOfKeys = section.values("description");

    for (IniFileKey &currentIniFileKey : listOfKeys)
    {
        if (currentIniFileKey.keyLocale.isEmpty())
        {
            object->m_description = currentIniFileKey.value.toString();
        }
        object->m_descriptionLocaleStorage.insert(currentIniFileKey.keyLocale, currentIniFileKey.value.toString());
    }

    return true;
}
