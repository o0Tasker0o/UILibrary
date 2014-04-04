#include <Windows.h>
#include "ButtonView.h"
#include "LabelView.h"

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
    Button *mpButton;
    ButtonView *mpButtonView;
    Label *mpLabel;
    LabelView *mpLabelView;
};

#endif