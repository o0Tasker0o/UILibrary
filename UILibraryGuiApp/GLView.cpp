#include "GLView.h"
#include "IniFileReader.h"
#include "ControlFactory.h"
#include <gl/GL.h>
#include <gl/glu.h>

GLView::GLView(void) : mHDC(NULL)
{
}

GLView::~GLView(void)
{
    std::vector<std::pair<Control *, ControlView *>>::iterator controlIterator = mControls.begin();

    while (controlIterator != mControls.end())
    {
        delete controlIterator->second;
        delete controlIterator->first;

        controlIterator++;
    }
}

int GLView::Initialise(HWND hwnd, unsigned int width, unsigned int height)
{
    mHDC = GetDC(hwnd);

    std::vector<IniSection> controlIni = IniFileReader::LoadFile("demo controls.ini");
    mControls = ControlFactory::LoadControls(controlIni, hwnd);

    mControls[0].first->SetMouseClickedCallback(this, GLView::QuitInvoker);

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

    std::vector<std::pair<Control *, ControlView *>>::iterator controlIterator = mControls.begin();

    while (controlIterator != mControls.end())
    {
        controlIterator->second->Render();
        controlIterator++;
    }

    SwapBuffers(mHDC);
}

void GLView::Update(int mouseX, int mouseY, bool leftButtonDown)
{
    MouseButtonState leftButtonState = leftButtonDown ? MouseButtonState::MOUSEDOWN : MouseButtonState::MOUSEUP;

    std::vector<std::pair<Control *, ControlView *>>::iterator controlIterator = mControls.begin();

    while (controlIterator != mControls.end())
    {
        controlIterator->second->Update(mouseX, mouseY, leftButtonState);
        controlIterator++;
    }
}