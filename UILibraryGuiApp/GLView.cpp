#include "GLView.h"
#include <gl/GL.h>
#include <gl/glu.h>

GLView::GLView(void) : mHDC(NULL)
{
}

GLView::~GLView(void)
{
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

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45.0,
        (double)width / (double)height,
        0.1,
        80.0);

    glMatrixMode(GL_MODELVIEW);
}

void GLView::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    SwapBuffers(mHDC);
}