#include "ControlFactory.h"
#include "Button.h"
#include "Label.h"
#include "ButtonView.h"
#include "LabelView.h"

std::vector<std::pair<Control *, ControlView *>> ControlFactory::LoadControls(std::vector<IniSection> iniConfiguration, HWND hwnd)
{
    std::vector<std::pair<Control *, ControlView *>> loadedControls;

    std::vector<IniSection>::iterator iniSectionIterator = iniConfiguration.begin();

    while (iniSectionIterator != iniConfiguration.end())
    {
        std::string xPositionString = iniSectionIterator->propertyMap["xPosition"];
        std::string yPositionString = iniSectionIterator->propertyMap["yPosition"];
        std::string widthString = iniSectionIterator->propertyMap["width"];
        std::string heightString = iniSectionIterator->propertyMap["height"];

        Control *pNewControl(NULL);
        ControlView *pNewControlView(NULL);

        if ("Button" == iniSectionIterator->sectionName)
        {
            pNewControl = new Button(atoi(xPositionString.c_str()),
                                     atoi(yPositionString.c_str()),
                                     atoi(widthString.c_str()),
                                     atoi(heightString.c_str()));

            pNewControlView = new ButtonView((Button *) pNewControl);
        }
        else if ("Label" == iniSectionIterator->sectionName)
        {
            pNewControl = new Label(atoi(xPositionString.c_str()),
                                    atoi(yPositionString.c_str()),
                                    atoi(widthString.c_str()),
                                    iniSectionIterator->propertyMap["text"]);

            pNewControlView = new LabelView((Label *) pNewControl, hwnd);
        }

        std::pair<Control*, ControlView*> controllerViewPair;
        controllerViewPair.first = pNewControl;
        controllerViewPair.second = pNewControlView;
        loadedControls.push_back(controllerViewPair);

        ++iniSectionIterator;
    }

    return loadedControls;
}