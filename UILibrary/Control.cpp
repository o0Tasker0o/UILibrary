#include "Control.h"
#include <Windows.h>

Control::Control(unsigned int xPosition, unsigned int yPosition, unsigned int width, unsigned int height) :
            mMouseEnterCallback(NULL),
            mMouseLeaveCallback(NULL),
            mMouseClickedCallback(NULL),
            mPreviousLeftButtonState(MouseButtonState::MOUSEUP),
            mIsFocused(false)
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

void Control::SetMouseClickedCallback(void *pClickedObject, void(*mouseClickedFunc)(void *object, Control *pCaller))
{
    mpClickedObject = pClickedObject;
    mMouseClickedCallback = mouseClickedFunc;
}

void Control::Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState)
{
    if (xPos >= mXPosition && xPos < mXPosition + mWidth &&
        yPos >= mYPosition && yPos < mYPosition + mHeight)
    {
        if (mPreviousLeftButtonState == MouseButtonState::MOUSEDOWN && leftButtonState == MouseButtonState::MOUSEUP)
        {
            if (NULL != mMouseClickedCallback)
            {
                mMouseClickedCallback(mpClickedObject, this);
            }
        }

        if (!mIsFocused)
        {
            mIsFocused = true;

            if (NULL != mMouseEnterCallback)
            {
                mMouseEnterCallback(mpEnterObject, this);
            }
        }
    }
    else
    {
        if (mIsFocused)
        {
            mIsFocused = false;

            if (NULL != mMouseLeaveCallback)
            {
                mMouseLeaveCallback(mpLeaveObject, this);
            }
        }
    }

    mPreviousLeftButtonState = leftButtonState;
}