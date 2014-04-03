#ifndef LABEL_H
#define LABEL_H

#include "Control.h"
#include <string>

class Label : public Control
{
  public:
    Label(int xPosition, int yPosition, unsigned int width, std::string text);
    ~Label();

    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState);

    std::string mText;
};

#endif