#include "adtdesktopfileparser.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <QDebug>

const QString ADTDesktopFileParser::NAME_SECTION_NAME          = "name";
const QString ADTDesktopFileParser::ICON_SECTION_NAME          = "icon";
const QString ADTDesktopFileParser::DESCRIPTION_SECTION_NAME   = "description";
const QString ADTDesktopFileParser::ARGS_SECTION_NAME          = "args";
const QString ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME = "Desktop Entry";

ADTDesktopFileParser::ADTDesktopFileParser(QString data)
    : m_sections()
    , m_testLists()
    , m_dbusServiceName()
    , m_dbusPath()
    , m_dbusInterfaceName()
    , m_dbusMethodName()
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

QString ADTDesktopFileParser::getDefaulValue(QList<IniFileKey> iniFileKey)
{
    for (IniFileKey &currentIniFileKey : iniFileKey)
    {
        if (currentIniFileKey.keyLocale.isEmpty())
        {
            return currentIniFileKey.value.toString();
        }
    }

    return QString();
}

ADTDesktopFileParser::ADTDesktopFileParser(QString data,
                                           QStringList testLists,
                                           QString dbusServiceName,
                                           QString dbusPath,
                                           QString dbusInterfaceName,
                                           QString dbusMethodName)
    : ADTDesktopFileParser{data}
{
    m_testLists         = testLists;
    m_dbusServiceName   = dbusServiceName;
    m_dbusPath          = dbusPath;
    m_dbusInterfaceName = dbusInterfaceName;
    m_dbusMethodName    = dbusMethodName;
}

std::unique_ptr<ADTExecutable> ADTDesktopFileParser::buildCategoryExecutable()
{
    std::unique_ptr<ADTExecutable> newADTExecutable = std::make_unique<ADTExecutable>();

    QList<QString> groups = getGroupsList();

    if (groups.isEmpty())
    {
        return nullptr;
    }

    newADTExecutable->m_id = getToolName();

    if (newADTExecutable->m_id.isEmpty())
    {
        return nullptr;
    }

    newADTExecutable->m_toolId = newADTExecutable->m_id;

    QList<QString> listOfKeys = getKeysListOfGroup(ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME);

    if (listOfKeys.empty())
    {
        qWarning() << "ERROR! Can't get list of keys for object: " << newADTExecutable->m_id;

        return nullptr;
    }

    setIcon(ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME, newADTExecutable.get());

    if (!setNames(ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME, newADTExecutable.get()))
    {
        qWarning() << "ERROR! Can't get name for object: " << newADTExecutable->m_id;
        return nullptr;
    }

    if (!setDescriptions(ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME, newADTExecutable.get()))
    {
        qWarning() << "ERROR! Can't get description for object: " << newADTExecutable->m_id;
    }

    setArgs(ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME, newADTExecutable.get());

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

    result->m_id        = test.trimmed();
    result->m_type      = ADTExecutable::ExecutableType::executableType;
    result->m_name      = test.trimmed();
    result->m_toolId    = categoryExecutable->m_id;
    result->m_icon      = categoryExecutable->m_icon;
    result->m_exit_code = categoryExecutable->m_exit_code;

    result->m_dbusServiceName   = m_dbusServiceName;
    result->m_dbusInterfaceName = m_dbusInterfaceName;
    result->m_dbusPath          = m_dbusPath;
    result->m_dbusRunMethodName = m_dbusMethodName;
    result->m_args              = result->m_id;

    auto testSection = m_sections.find(test);

    if (testSection == m_sections.end())
    {
        //No section for test found
        return nullptr;
    }

    if (!setNames(test, result.get()))
    {
        qWarning() << "ERROR! Can't find key " << ADTDesktopFileParser::NAME_SECTION_NAME << " for test : " << test
                   << " in tool: " << categoryExecutable->m_id;

        return nullptr;
    }
    if (!setDescriptions(test, result.get()))
    {
        qWarning() << "ERROR! Can't find key " << ADTDesktopFileParser::DESCRIPTION_SECTION_NAME
                   << " for test : " << test << " in tool: " << categoryExecutable->m_id;
    }

    if (!setArgs(test, result.get()))
    {}

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

        if (test.get())
        {
            results.push_back(std::move(test));
        }
    }

    return results;
}

QList<QString> ADTDesktopFileParser::getGroupsList() const
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
        return keyName.toLower();
    }

    return keyName.mid(0, indexOfOpeningBracket).toLower();
}

bool ADTDesktopFileParser::setIcon(const QString &test, ADTExecutable *object)
{
    Section section = m_sections[test];
    auto iconIt     = section.find(ADTDesktopFileParser::ICON_SECTION_NAME);

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

bool ADTDesktopFileParser::setNames(const QString &test, ADTExecutable *object)
{
    Section section = m_sections[test];
    auto nameIt     = section.find(ADTDesktopFileParser::NAME_SECTION_NAME);

    if (nameIt == section.end())
    {
        object->m_name = "";
        return false;
    }

    QList<IniFileKey> listOfKeys = section.values(ADTDesktopFileParser::NAME_SECTION_NAME);

    QString defaultName = getDefaulValue(listOfKeys);
    if (defaultName.isEmpty())
    {
        return false;
    }

    object->m_name = defaultName;

    for (IniFileKey &currentIniFileKey : listOfKeys)
    {
        object->m_nameLocaleStorage.insert(currentIniFileKey.keyLocale, currentIniFileKey.value.toString());
    }

    return true;
}

bool ADTDesktopFileParser::setDescriptions(const QString &test, ADTExecutable *object)
{
    Section section = m_sections[test];
    auto nameIt     = section.find(ADTDesktopFileParser::DESCRIPTION_SECTION_NAME);

    if (nameIt == section.end())
    {
        object->m_description = "";
        return false;
    }

    QList<IniFileKey> listOfKeys = section.values(ADTDesktopFileParser::DESCRIPTION_SECTION_NAME);

    QString defaultDescription = getDefaulValue(listOfKeys);
    if (defaultDescription.isEmpty())
    {
        return false;
    }

    object->m_description = defaultDescription;

    for (IniFileKey &currentIniFileKey : listOfKeys)
    {
        object->m_descriptionLocaleStorage.insert(currentIniFileKey.keyLocale, currentIniFileKey.value.toString());
    }

    return true;
}

bool ADTDesktopFileParser::setArgs(const QString &test, ADTExecutable *object)
{
    Section section = m_sections[test];
    auto nameIt     = section.find(ADTDesktopFileParser::ARGS_SECTION_NAME);

    if (nameIt == section.end())
    {
        object->m_args = "";
        return false;
    }

    QList<IniFileKey> listOfKeys = section.values(ADTDesktopFileParser::ARGS_SECTION_NAME);

    if (!listOfKeys.empty())
    {
        object->m_args = listOfKeys.at(0).value.toString();
        return true;
    }

    return false;
}

QString ADTDesktopFileParser::getToolName()
{
    auto desktopEntryIt = m_sections.find(ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME);

    if (desktopEntryIt == m_sections.end())
    {
        qWarning() << "ERROR! Can't find section: " << ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME
                   << " for the object located on the path " << m_dbusPath;

        return QString();
    }

    Section desktopEntrySection = *desktopEntryIt;

    QList<IniFileKey> toolNameList = desktopEntrySection.values(ADTDesktopFileParser::NAME_SECTION_NAME);

    if (toolNameList.isEmpty())
    {
        qWarning() << "ERROR! Can't find any keys in section: " << ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME
                   << " for the object located on the path " << m_dbusPath;

        return QString();
    }

    for (IniFileKey &currentKey : toolNameList)
    {
        if (currentKey.keyLocale.isEmpty())
        {
            return currentKey.value.toString();
        }
    }

    qWarning() << "ERROR! Can't find key: " << ADTDesktopFileParser::NAME_SECTION_NAME
               << " in section: " << ADTDesktopFileParser::DESKTOP_ENTRY_SECTION_NAME << " without locale "
               << "for the object located on the path " << m_dbusPath;
    return QString();
}
