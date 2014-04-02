#include "../UILibrary/ControlFactory.h"
#include "../UILibrary/IniSection.h"
#include "../UILibrary/Button.h"
using namespace System;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class ControlFactoryUnitTests
    {
      public: 
        [TestMethod]
        void ControlFactoryReturnsEmptyVectorWhenNoIniSectionsAreLoaded()
        {
            std::vector<IniSection> controlConfiguration;

            Assert::AreEqual(0, (int)ControlFactory::LoadControls(controlConfiguration).size());
        }

        [TestMethod]
        void ControlFactoryReturnsControlSpecifiedInIniSection()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "1");
            buttonSection.AddProperty("yPosition", "2");
            buttonSection.AddProperty("width", "3");
            buttonSection.AddProperty("height", "4");

            std::vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            std::vector<Control *> pLoadedControls = ControlFactory::LoadControls(controlConfiguration);

            Assert::AreEqual(1, (int) pLoadedControls.size());

            Assert::AreEqual(1U, pLoadedControls[0]->mXPosition);
            Assert::AreEqual(2U, pLoadedControls[0]->mYPosition);
            Assert::AreEqual(3U, pLoadedControls[0]->mWidth);
            Assert::AreEqual(4U, pLoadedControls[0]->mHeight);
        }

        [TestMethod]
        void ControlFactoryGeneratesDefaultsForMissingPropertyValues()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "1");

            std::vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            std::vector<Control *> pLoadedControls = ControlFactory::LoadControls(controlConfiguration);

            Assert::AreEqual(1, (int)pLoadedControls.size());

            Assert::AreEqual(1U, pLoadedControls[0]->mXPosition);
            Assert::AreEqual(0U, pLoadedControls[0]->mYPosition);
            Assert::AreEqual(0U, pLoadedControls[0]->mWidth);
            Assert::AreEqual(0U, pLoadedControls[0]->mHeight);
        }

        [TestMethod]
        void ControlFactoryHandlesInvalidPropertyValues()
        {
            IniSection buttonSection;
            buttonSection.sectionName = "Button";
            buttonSection.AddProperty("xPosition", "THIS IS NOT A NUMBER");

            std::vector<IniSection> controlConfiguration;

            controlConfiguration.push_back(buttonSection);

            std::vector<Control *> pLoadedControls = ControlFactory::LoadControls(controlConfiguration);

            Assert::AreEqual(1, (int)pLoadedControls.size());

            Assert::AreEqual(0U, pLoadedControls[0]->mXPosition);
            Assert::AreEqual(0U, pLoadedControls[0]->mYPosition);
            Assert::AreEqual(0U, pLoadedControls[0]->mWidth);
            Assert::AreEqual(0U, pLoadedControls[0]->mHeight);
        }
    };
}
