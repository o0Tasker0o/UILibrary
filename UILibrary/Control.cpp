#include "Control.h"
#include <Windows.h>

Control::Control(unsigned int xPosition, unsigned int yPosition, unsigned int width, unsigned int height) :
            mMouseEnterCallback(NULL),
            mMouseIsInsideControl(false)
{
    mXPosition = xPosition;
    mYPosition = yPosition;

    mWidth = width;
    mHeight = height;
}

void Control::SetMouseEnterCallback(void *pEnterObject, void(*mouseEnterFunc)(void *object, Control *pCaller))
{
    mpEnterObject = pEnterObject;
    mMouseEnterCallback = mouseEnterFunc;
}

void Control::SetMouseLeaveCallback(void *pLeaveObject, void(*mouseLeaveFunc)(void *object, Control *pCaller))
{
    mpLeaveObject = pLeaveObject;
    mMouseLeaveCallback = mouseLeaveFunc;
}

void Control::Update(unsigned int xPos, unsigned int yPos)
{
    if (xPos >= mXPosition && xPos < mXPosition + mWidth &&
        yPos >= mYPosition && yPos < mYPosition + mHeight)
    {
        if (!mMouseIsInsideControl)
        {
            mMouseIsInsideControl = true;

            if (NULL != mMouseEnterCallback)
            {
                mMouseEnterCallback(mpEnterObject, this);
            }
        }
    }
    else
    {
        if (mMouseIsInsideControl)
        {
            mMouseIsInsideControl = false;

            if (NULL != mMouseLeaveCallback)
            {
                mMouseLeaveCallback(mpLeaveObject, this);
            }
        }
    }
}