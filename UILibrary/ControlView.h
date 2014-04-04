#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include "Control.h"

class ControlView
{
public:
    virtual void Render(void) = 0;
    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState) = 0;

    virtual ~ControlView() {}
protected:
    ControlView(Control *pControl)
    {
        mpControl = pControl;
    }

    Control *mpControl;

    const static float mpBaseColour[4];
    const static float mpFocusedColour[4];
    const static float mpClickedColour[4];
    const static float mpShadowColour[4];
    const static float mpHighlightColour[4];
};

#endif