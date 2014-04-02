#ifndef CONTROL_H
#define CONTROL_H

enum MouseButtonState
{
    MOUSEDOWN,
    MOUSEUP
};

class Control
{
  public:
    ~Control() {};

    virtual void Update(unsigned int xPos, unsigned int yPos, MouseButtonState leftButtonState);

    void SetMouseEnterCallback(void *pEnterObject, void(*mouseEnterFunc)(void *object, Control *pCaller));
    void SetMouseLeaveCallback(void *pLeaveObject, void(*mouseLeaveFunc)(void *object, Control *pCaller));
    void SetMouseClickedCallback(void *pclickedObject, void(*mouseClickedFunc)(void *object, Control *pCaller));

    unsigned int mXPosition;
    unsigned int mYPosition;

    unsigned int mWidth;
    unsigned int mHeight;
  protected:
    Control(unsigned int xPosition, unsigned int yPosition, unsigned int width, unsigned int height);

    void *mpEnterObject;
    void(*mMouseEnterCallback)(void *object, Control *pCaller);

    void *mpLeaveObject;
    void(*mMouseLeaveCallback)(void *object, Control *pCaller);

    void *mpClickedObject;
    void(*mMouseClickedCallback)(void *object, Control *pCaller);

  private:
    bool mMouseIsInsideControl;
    MouseButtonState mPreviousLeftButtonState;
};

#endif