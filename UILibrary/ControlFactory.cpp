#include "ControlFactory.h"
#include "Button.h"
#include "Label.h"
#include "ButtonView.h"
#include "LabelView.h"

using namespace std;

UiControls ControlFactory::LoadControls(vector<IniSection> iniConfiguration, HWND hwnd)
{
    UiControls loadedControls;

    vector<IniSection>::iterator iniSectionIterator = iniConfiguration.begin();

    while (iniSectionIterator != iniConfiguration.end())
    {
        string xPositionString = iniSectionIterator->propertyMap["xPosition"];
        string yPositionString = iniSectionIterator->propertyMap["yPosition"];
        string widthString = iniSectionIterator->propertyMap["width"];
        string heightString = iniSectionIterator->propertyMap["height"];

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

        ControlPair controllerViewPair;
        controllerViewPair.first = pNewControl;
        controllerViewPair.second = pNewControlView;
        loadedControls.push_back(controllerViewPair);

        ++iniSectionIterator;
    }

    return loadedControls;
}