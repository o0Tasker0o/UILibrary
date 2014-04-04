#ifndef LABELVIEW_H
#define LABELVIEW_H

#include <Windows.h>
#include <gl\GL.h>

#include "ControlView.h"
#include "Label.h"


class LabelView : public ControlView
{
  public:
    LabelView(Label *pLabel, HWND hwnd);
    ~LabelView();

    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState);
    virtual void Render(void);

  private:
      void SetFont(HDC hdc, std::string fontName, int size); 

      HDC mHdc;
      HFONT mFont;

      GLuint mTextList;

      const static unsigned int cLabelLength = 128;
};

#endif