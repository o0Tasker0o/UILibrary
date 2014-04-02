#include "ControlFactory.h"
#include "Button.h"
#include "ButtonView.h"

std::vector<std::pair<Control *, ControlView *>> ControlFactory::LoadControls(std::vector<IniSection> iniConfiguration)
{
    std::vector<std::pair<Control *, ControlView *>> loadedControls;

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

            ButtonView *pButtonView = new ButtonView(pButton);

            std::pair<Button*, ButtonView*> controllerViewPair;
            controllerViewPair.first = pButton;
            controllerViewPair.second = pButtonView;
            loadedControls.push_back(controllerViewPair);
        }

        ++iniSectionIterator;
    }

    return loadedControls;
}