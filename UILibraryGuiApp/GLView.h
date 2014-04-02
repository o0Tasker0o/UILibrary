#include <Windows.h>

#ifndef GLVIEW_H
#define GLVIEW_H

class GLView
{
public:
    GLView(void);
    ~GLView(void);
    int Initialise(HDC hdc, unsigned int width, unsigned int height);
    void Resize(unsigned int width, unsigned int height);
    void Render(void);
private:
    HDC mHDC;
};

#endif