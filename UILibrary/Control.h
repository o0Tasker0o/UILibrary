#ifndef CONTROL_H
#define CONTROL_H

class Control
{
  public:
      Control(unsigned int xPosition, unsigned int yPosition, unsigned int width, unsigned int height);
    ~Control() {};

    virtual void Update(unsigned int xPos, unsigned int yPos);

    void SetMouseEnterCallback(void *pEnterObject, void(*mouseEnterFunc)(void *object, Control *pCaller));
    void SetMouseLeaveCallback(void *pLeaveObject, void(*mouseLeaveFunc)(void *object, Control *pCaller));

    unsigned int mXPosition;
    unsigned int mYPosition;

    unsigned int mWidth;
    unsigned int mHeight;
  protected:
    void *mpEnterObject;
    void(*mMouseEnterCallback)(void *object, Control *pCaller);

    void *mpLeaveObject;
    void(*mMouseLeaveCallback)(void *object, Control *pCaller);
    
  private:
    bool mMouseIsInsideControl;
};

#endif