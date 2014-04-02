#ifndef CALLBACKTESTER_H
#define CALLBACKTESTER_H

#include "../UILibrary/Control.h"

class CallbackTester
{
  public:
    CallbackTester();
    ~CallbackTester();

    static void MouseEnterCallbackCaller(void *object, Control *pCaller);
    static void MouseLeaveCallbackCaller(void *object, Control *pCaller);

    bool mMouseEntered;
    bool mMouseLeft;
};

#endif