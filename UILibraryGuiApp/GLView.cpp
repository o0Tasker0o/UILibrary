#include "GLView.h"
#include <gl/GL.h>
#include <gl/glu.h>

GLView::GLView(void) : mHDC(NULL)
{
    mpButton = new Button(10, 20, 40, 30);
    mpButton->SetMouseClickedCallback(this, GLView::QuitInvoker);

    mpButtonView = new ButtonView(mpButton);
}

GLView::~GLView(void)
{
    delete mpButton;
    delete mpButtonView;
}

int GLView::Initialise(HDC hdc, unsigned int width, unsigned int height)
{
    mHDC = hdc;

    Resize(width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return 0;
}

void GLView::Resize(unsigned int width, unsigned int height)
{
    if (0 == width)
    {
        width = 1;
    }

    if (0 == height)
    {
        height = 1;
    }

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0.0, width, height, 0.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void GLView::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    mpButtonView->Render();

    SwapBuffers(mHDC);
}

void GLView::Update(int mouseX, int mouseY, bool leftButtonDown)
{
    MouseButtonState leftButtonState = leftButtonDown ? MouseButtonState::MOUSEDOWN : MouseButtonState::MOUSEUP;
    mpButtonView->Update(mouseX, mouseY, leftButtonState);
}