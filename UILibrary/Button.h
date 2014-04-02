#ifndef BUTTON_H
#define BUTTON_H

#include "Control.h"

class Button : public Control
{
public:
    Button(int xPosition, int yPosition, unsigned int width, unsigned int height);
    ~Button();

    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState);
};

#endif