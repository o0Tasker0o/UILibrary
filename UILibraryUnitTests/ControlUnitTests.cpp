#include "../UILibrary/Control.h"
#include "CallbackTester.h"

using namespace System;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class ControlUnitTests
    {
    private:
        void ButtonClickFunctionCaller(void *object, Control *pCaller)
        {

        }
    public: 
        [TestMethod]
        void ConstructorTest()
        {
            unsigned int xPosition = 1;
            unsigned int yPosition = 2;
            unsigned int width = 3;
            unsigned int height = 4;

			Control *pControl = new Control(xPosition, yPosition, width, height);

			Assert::AreEqual(xPosition, pControl->mXPosition);
			Assert::AreEqual(yPosition, pControl->mYPosition);
			Assert::AreEqual(width, pControl->mWidth);
			Assert::AreEqual(height, pControl->mHeight);

			delete pControl;
        }

        [TestMethod]
        void MouseEnterIsNotCalledIfCallbackNotSet()
        {
			Control *pControl = new Control(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();

            Assert::AreEqual(false, pCallbackTester->mMouseEntered);

			pControl->Update(0, 0);

            Assert::AreEqual(false, pCallbackTester->mMouseEntered);

            delete pCallbackTester;
			delete pControl;
        }

        [TestMethod]
        void MouseEnterAndLeaveCallbacksAreCalledWhenMouseEntersAndLeavesButton()
        {
			Control *pControl = new Control(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

			pControl->SetMouseEnterCallback(pCallbackTester, &CallbackTester::MouseEnterCallbackCaller);
			pControl->SetMouseLeaveCallback(pCallbackTester, &CallbackTester::MouseLeaveCallbackCaller);

            //Move the mouse into the top left corner of the button
			pControl->Update(0, 0);
            Assert::AreEqual(true, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse beyond the right of the button
			pControl->Update(10, 0);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(true, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseLeft = false;

            //Move the mouse back into the top left corner of the button
			pControl->Update(0, 0);
            Assert::AreEqual(true, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse below the button
			pControl->Update(0, 6);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(true, pCallbackTester->mMouseLeft);

            delete pCallbackTester;
			delete pControl;
        }

        [TestMethod]
        void MouseEnterAndLeaveCallbacksAreNotCalledUnlessTheMouseEntersOrLeavesTheButton()
        {
			Control *pControl = new Control(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

			pControl->SetMouseEnterCallback(pCallbackTester, &CallbackTester::MouseEnterCallbackCaller);
			pControl->SetMouseLeaveCallback(pCallbackTester, &CallbackTester::MouseLeaveCallbackCaller);

            //Move the mouse into the top left corner of the button
			pControl->Update(0, 0);
            Assert::AreEqual(true, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse to another position inside the button
			pControl->Update(1, 1);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse to the right of the button
			pControl->Update(10, 0);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(true, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseLeft = false;

            //Move the mouse below the button
			pControl->Update(0, 6);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

            delete pCallbackTester;
			delete pControl;
        }
    };
}
