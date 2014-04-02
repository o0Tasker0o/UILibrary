#include "CallbackTester.h"

CallbackTester::CallbackTester()
{
    mMouseEntered = false;
    mMouseLeft = false;
    mMouseClicked = false;
}

CallbackTester::~CallbackTester()
{

}

void CallbackTester::MouseEnterCallbackCaller(void *object, Control *pCaller)
{
    ((CallbackTester *)object)->mMouseEntered = true;
}

void CallbackTester::MouseLeaveCallbackCaller(void *object, Control *pCaller)
{
    ((CallbackTester *)object)->mMouseLeft = true;
}

void CallbackTester::MouseClickedCallbackCaller(void *object, Control *pCaller)
{
    ((CallbackTester *)object)->mMouseClicked = true;
}