#include "ButtonView.h"
#include <Windows.h>
#include <gl/GL.h>

ButtonView::ButtonView(Button *pButton) : ControlView(pButton)
{
}

ButtonView::~ButtonView()
{
}

void ButtonView::Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState)
{
    mpControl->Update(xPos, yPos, leftButtonState);
}

void ButtonView::Render(void)
{
    glBegin(GL_TRIANGLE_STRIP);

    glColor4fv(mpBaseColour);

    if (mpControl->mIsClicked)
    {
        glColor4fv(mpClickedColour);
    }
    else if (mpControl->mIsFocused)
    {
        glColor4fv(mpFocusedColour);
    }

    glVertex2i(mpControl->mXPosition, mpControl->mYPosition);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition);
    glVertex2i(mpControl->mXPosition, mpControl->mYPosition + mpControl->mHeight);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition + mpControl->mHeight);

    glEnd();

    glBegin(GL_LINE_STRIP);

    glColor4fv(mpControl->mIsClicked ? mpShadowColour : mpHighlightColour);

    glVertex2i(mpControl->mXPosition + 1, mpControl->mYPosition + mpControl->mHeight);
    glVertex2i(mpControl->mXPosition + 1, mpControl->mYPosition);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition + 1);

    glEnd();

    glBegin(GL_LINE_STRIP);

    glColor4fv(mpControl->mIsClicked ? mpHighlightColour : mpShadowColour);

    glVertex2i(mpControl->mXPosition, mpControl->mYPosition + mpControl->mHeight);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition + mpControl->mHeight);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition);

    glEnd();
}