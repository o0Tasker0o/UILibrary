#include "Button.h"
#include <Windows.h>

Button::Button(int xPosition, int yPosition, unsigned int width, unsigned int height) :
        Control(xPosition, yPosition, width, height)
{
}


Button::~Button()
{
}

void Button::Update(unsigned int xPos, unsigned int yPos)
{
    Control::Update(xPos, yPos);
}