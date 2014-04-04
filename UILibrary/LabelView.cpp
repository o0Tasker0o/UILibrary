#include "LabelView.h"

LabelView::LabelView(Label *pLabel, HWND hwnd) : ControlView(pLabel),
        mFont(NULL)
{
    mTextList = glGenLists(cLabelLength);

    SetFont(GetDC(hwnd), "Microsoft Sans Serif", 16);
}

void LabelView::SetFont(HDC hdc, std::string fontName, int size)
{
    DWORD italic = FALSE;
    DWORD underline = FALSE;
    DWORD strikeout = FALSE;

    mFont = CreateFont(size,
                       0,
                       0,
                       0,
                       FW_NORMAL,
                       italic,
                       underline,
                       strikeout,
                       ANSI_CHARSET,
                       OUT_TT_PRECIS,
                       CLIP_DEFAULT_PRECIS,
                       ANTIALIASED_QUALITY,
                       FF_DONTCARE | DEFAULT_PITCH,
                       fontName.c_str());

    SelectObject(hdc, mFont);

    wglUseFontBitmaps(hdc, 0, cLabelLength, mTextList);

    mHdc = hdc;
}

LabelView::~LabelView()
{
}

void LabelView::Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState)
{

}

void LabelView::Render(void)
{
    Label *pLabel = (Label *) mpControl;
    std::string labelText = pLabel->mText;
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glRasterPos2f((float) pLabel->mXPosition, (float) pLabel->mYPosition);

    glListBase(mTextList);

    glCallLists(labelText.length(), GL_UNSIGNED_BYTE, labelText.c_str());
}