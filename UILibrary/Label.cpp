#include "Label.h"


Label::Label(int xPosition, int yPosition, unsigned int width, std::string text) :
        Control(xPosition, yPosition, width, 0),
        mText(text)
{
}


Label::~Label()
{
}

void Label::Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState)
{
}