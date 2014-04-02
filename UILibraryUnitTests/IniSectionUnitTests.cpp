#include "../UILibrary/IniSection.h"

using namespace System;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class UnitTest
    {
    public: 
        [TestMethod]
        void IniSectionAddPropertyTest()
        {
            IniSection testSection;

            Assert::AreEqual(0U, testSection.propertyMap.size());

            std::string inputKey = "a";
            std::string inputValue = "b";

            testSection.AddProperty(inputKey, inputValue);

            Assert::AreEqual(1U, testSection.propertyMap.size());
            Assert::IsTrue(inputValue == testSection.propertyMap[inputKey]);
        }
    };
}
