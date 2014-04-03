#include "Button.h"
#include "CallbackTester.h"

using namespace System;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class ButtonUnitTests
    {
    public: 
        [TestMethod]
        void ConstructorTest()
        {
            unsigned int xPosition = 1;
            unsigned int yPosition = 2;
            unsigned int width = 3;
            unsigned int height = 4;

            Button *pButton = new Button(xPosition, yPosition, width, height);

            Assert::AreEqual(xPosition, pButton->mXPosition);
            Assert::AreEqual(yPosition, pButton->mYPosition);
            Assert::AreEqual(width, pButton->mWidth);
            Assert::AreEqual(height, pButton->mHeight);

            delete pButton;
        }

        [TestMethod]
        void MouseEnterIsNotCalledIfCallbackNotSet()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();

            Assert::AreEqual(false, pCallbackTester->mMouseEntered);

            pButton->Update(0, 0, MouseButtonState::MOUSEUP);

            Assert::AreEqual(false, pCallbackTester->mMouseEntered);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseLeaveIsNotCalledIfCallbackNotSet()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();

            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            pButton->Update(10, 0, MouseButtonState::MOUSEUP);

            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseClickIsNotCalledIfCallbackNotSet()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();

            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->Update(0, 0, MouseButtonState::MOUSEDOWN);
            pButton->Update(0, 0, MouseButtonState::MOUSEUP);

            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseEnterAndLeaveCallbacksAreCalledWhenMouseEntersAndLeavesButton()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

            pButton->SetMouseEnterCallback(pCallbackTester, &CallbackTester::MouseEnterCallbackCaller);
            pButton->SetMouseLeaveCallback(pCallbackTester, &CallbackTester::MouseLeaveCallbackCaller);

            //Move the mouse into the top left corner of the button
            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(true, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse beyond the right of the button
            pButton->Update(10, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(true, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseLeft = false;

            //Move the mouse back into the top left corner of the button
            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(true, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse below the button
            pButton->Update(0, 6, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(true, pCallbackTester->mMouseLeft);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseEnterAndLeaveCallbacksAreNotCalledUnlessTheMouseEntersOrLeavesTheButton()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

            pButton->SetMouseEnterCallback(pCallbackTester, &CallbackTester::MouseEnterCallbackCaller);
            pButton->SetMouseLeaveCallback(pCallbackTester, &CallbackTester::MouseLeaveCallbackCaller);

            //Move the mouse into the top left corner of the button
            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(true, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse to another position inside the button
            pButton->Update(1, 1, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseEntered = false;

            //Move the mouse to the right of the button
            pButton->Update(10, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(true, pCallbackTester->mMouseLeft);
            pCallbackTester->mMouseLeft = false;

            //Move the mouse below the button
            pButton->Update(0, 6, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseEntered);
            Assert::AreEqual(false, pCallbackTester->mMouseLeft);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseClickCallbackIsCalledWhenMouseIsReleasedInsideControlBounds()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->SetMouseClickedCallback(pCallbackTester, &CallbackTester::MouseClickedCallbackCaller);
            
            pButton->Update(0, 0, MouseButtonState::MOUSEDOWN);
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(true, pCallbackTester->mMouseClicked);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseClickCallbackIsNotCalledWhenMouseIsReleasedOutsideControlBounds()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->SetMouseClickedCallback(pCallbackTester, &CallbackTester::MouseClickedCallbackCaller);

            pButton->Update(10, 0, MouseButtonState::MOUSEDOWN);
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->Update(10, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void MouseClickCallbackIsNotCalledWhenMouseIsStateDoesNotChange()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->SetMouseClickedCallback(pCallbackTester, &CallbackTester::MouseClickedCallbackCaller);

            pButton->Update(0, 0, MouseButtonState::MOUSEDOWN);
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->Update(0, 0, MouseButtonState::MOUSEDOWN);
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(true, pCallbackTester->mMouseClicked);

            pCallbackTester->mMouseClicked = false;

            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            delete pCallbackTester;
            delete pButton;
        }

        [TestMethod]
        void ButtonIsFocusedAndClickedOnMouseInteractions()
        {
            Button *pButton = new Button(0, 0, 10U, 5U);
            Assert::IsFalse(pButton->mIsFocused);
            Assert::IsFalse(pButton->mIsClicked);

            pButton->Update(0, 0, MouseButtonState::MOUSEUP);
            Assert::IsTrue(pButton->mIsFocused);
            Assert::IsFalse(pButton->mIsClicked);

            pButton->Update(10, 0, MouseButtonState::MOUSEUP);
            Assert::IsFalse(pButton->mIsFocused);
            Assert::IsFalse(pButton->mIsClicked);

            pButton->Update(0, 0, MouseButtonState::MOUSEDOWN);
            Assert::IsTrue(pButton->mIsFocused);
            Assert::IsTrue(pButton->mIsClicked);

            pButton->Update(10, 0, MouseButtonState::MOUSEDOWN);
            Assert::IsFalse(pButton->mIsFocused);
            Assert::IsFalse(pButton->mIsClicked);

            delete pButton;
        }
    };
}
