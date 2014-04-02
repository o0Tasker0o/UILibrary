#include "ControlFactory.h"
#include "Button.h"

std::vector<Control *> ControlFactory::LoadControls(std::vector<IniSection> iniConfiguration)
{
    std::vector<Control *> loadedControls;

    std::vector<IniSection>::iterator iniSectionIterator = iniConfiguration.begin();

    while (iniSectionIterator != iniConfiguration.end())
    {
        if ("Button" == iniSectionIterator->sectionName)
        {
            std::string xPositionString = iniSectionIterator->propertyMap["xPosition"];
            std::string yPositionString = iniSectionIterator->propertyMap["yPosition"];
            std::string widthString = iniSectionIterator->propertyMap["width"];
            std::string heightString = iniSectionIterator->propertyMap["height"];

            Button *pButton = new Button(atoi(xPositionString.c_str()),
                                         atoi(yPositionString.c_str()),
                                         atoi(widthString.c_str()),
                                         atoi(heightString.c_str()));

            loadedControls.push_back(pButton);
        }

        ++iniSectionIterator;
    }

    return loadedControls;
}