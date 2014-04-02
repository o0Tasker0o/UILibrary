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

    glVertex2i(mpControl->mXPosition, mpControl->mYPosition);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition);
    glVertex2i(mpControl->mXPosition, mpControl->mYPosition + mpControl->mHeight);
    glVertex2i(mpControl->mXPosition + mpControl->mWidth, mpControl->mYPosition + mpControl->mHeight);

    glEnd();
}