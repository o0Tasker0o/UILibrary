#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include "Control.h"

class ControlView
{
public:
    virtual void Render(void) = 0;
    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState) = 0;

protected:
    ControlView(Control *pControl)
    {
        mpControl = pControl;
    }

    ~ControlView() {}

    Control *mpControl;
};

#endif