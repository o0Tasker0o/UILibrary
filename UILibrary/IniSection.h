#include <map>
#include <string>

struct IniSection
{
    std::string sectionName;

    std::map<std::string, std::string>propertyMap;
};