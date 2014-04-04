#include "ControlFactory.h"
#include "IniSection.h"
#include "Button.h"
#include "LabelView.h"
#include "CallbackTester.h"

using namespace System;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace std;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class ControlFactoryUnitTests
    {
      public: 
        [TestMethod]
        void ControlFactoryReturnsEmptyVectorWhenNoIniSectionsAreLoaded()
        {
            vector<IniSection> controlConfiguration;

            Assert::AreEqual(0, (int)ControlFactory::LoadControls(controlConfiguration, nullptr).size());
        }

        [TestMethod]
        void ControlFactoryReturnsButtonSpecifiedInIniSection()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "1");
            buttonSection.AddProperty("yPosition", "2");
            buttonSection.AddProperty("width", "3");
            buttonSection.AddProperty("height", "4");

            vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            UiControls pLoadedControls = ControlFactory::LoadControls(controlConfiguration, nullptr);

            Assert::AreEqual(1, (int) pLoadedControls.size());

            Assert::AreEqual(1U, pLoadedControls[0].first->mXPosition);
            Assert::AreEqual(2U, pLoadedControls[0].first->mYPosition);
            Assert::AreEqual(3U, pLoadedControls[0].first->mWidth);
            Assert::AreEqual(4U, pLoadedControls[0].first->mHeight);
        }

        [TestMethod]
        void ControlFactoryReturnsLabelSpecifiedInIniSection()
        {
            string testString = "test string";

            IniSection buttonSection;
            buttonSection.sectionName = "Label";
            buttonSection.AddProperty("xPosition", "1");
            buttonSection.AddProperty("yPosition", "2");
            buttonSection.AddProperty("width", "3");
            buttonSection.AddProperty("text", testString);

            vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            UiControls pLoadedControls = ControlFactory::LoadControls(controlConfiguration, nullptr);

            Assert::AreEqual(1, (int)pLoadedControls.size());

            Assert::AreEqual(1U, pLoadedControls[0].first->mXPosition);
            Assert::AreEqual(2U, pLoadedControls[0].first->mYPosition);
            Assert::AreEqual(3U, pLoadedControls[0].first->mWidth);
            Assert::IsTrue(testString == ((Label *) pLoadedControls[0].first)->mText);
        }

        [TestMethod]
        void ControlFactoryReturnsControlWithLinkedView()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "0");
            buttonSection.AddProperty("yPosition", "0");
            buttonSection.AddProperty("width", "1");
            buttonSection.AddProperty("height", "1");

            vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            UiControls pLoadedControls = ControlFactory::LoadControls(controlConfiguration, nullptr);

            Assert::AreEqual(1, (int)pLoadedControls.size());

            CallbackTester *pCallbackTester = new CallbackTester();
            Assert::AreEqual(false, pCallbackTester->mMouseClicked);

            pLoadedControls[0].first->SetMouseClickedCallback(pCallbackTester, &CallbackTester::MouseClickedCallbackCaller);

            pLoadedControls[0].second->Update(0, 0, MouseButtonState::MOUSEDOWN);
            pLoadedControls[0].second->Update(0, 0, MouseButtonState::MOUSEUP);

            Assert::AreEqual(true, pCallbackTester->mMouseClicked);

            delete pCallbackTester;
        }

        [TestMethod]
        void ControlFactoryGeneratesDefaultsForMissingPropertyValues()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "1");

            vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            UiControls pLoadedControls = ControlFactory::LoadControls(controlConfiguration, nullptr);

            Assert::AreEqual(1, (int)pLoadedControls.size());

            Assert::AreEqual(1U, pLoadedControls[0].first->mXPosition);
            Assert::AreEqual(0U, pLoadedControls[0].first->mYPosition);
            Assert::AreEqual(0U, pLoadedControls[0].first->mWidth);
            Assert::AreEqual(0U, pLoadedControls[0].first->mHeight);
        }

        [TestMethod]
        void ControlFactoryHandlesInvalidPropertyValues()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "THIS IS NOT A NUMBER");

            vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            UiControls pLoadedControls = ControlFactory::LoadControls(controlConfiguration, nullptr);

            Assert::AreEqual(1, (int)pLoadedControls.size());

            Assert::AreEqual(0U, pLoadedControls[0].first->mXPosition);
            Assert::AreEqual(0U, pLoadedControls[0].first->mYPosition);
            Assert::AreEqual(0U, pLoadedControls[0].first->mWidth);
            Assert::AreEqual(0U, pLoadedControls[0].first->mHeight);
        }
    };
}
