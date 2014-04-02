#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H

#include "ControlView.h"
#include "Button.h"

class ButtonView : public ControlView
{
public:
    ButtonView(Button *pButton);
    ~ButtonView();

    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState);
    virtual void Render(void);
};

#endif