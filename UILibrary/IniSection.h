#ifndef INISECTION_H
#define INISECTION_H

#include <map>
#include <string>

struct IniSection
{
    std::string sectionName;

    std::map<std::string, std::string>propertyMap;

    void AddProperty(std::string key, std::string value)
    {
        std::pair<std::string, std::string> newProperty;
        newProperty.first = key;
        newProperty.second = value;

        propertyMap.insert(newProperty);
    }
};

#endif