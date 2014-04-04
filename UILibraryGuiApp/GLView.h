#include <Windows.h>
#include <vector>
#include "ControlFactory.h"
#include "Control.h"
#include "ControlView.h"

#ifndef GLVIEW_H
#define GLVIEW_H

class GLView
{
public:
    GLView(void);
    ~GLView(void);
    int Initialise(HWND hwnd, unsigned int width, unsigned int height);
    void Resize(unsigned int width, unsigned int height);
    void Render(void);
    void Update(int mouseX, int mouseY, bool leftButtonDown);

    static void QuitInvoker(void *object, Control *pCaller)
    {
        PostQuitMessage(0);
    }
private:
    HDC mHDC;

    UiControls mControls;
};

#endif