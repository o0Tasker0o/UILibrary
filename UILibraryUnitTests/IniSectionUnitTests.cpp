#include "IniSection.h"

using namespace System;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace std;

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

            string inputKey = "a";
            string inputValue = "b";

            testSection.AddProperty(inputKey, inputValue);

            Assert::AreEqual(1U, testSection.propertyMap.size());
            Assert::IsTrue(inputValue == testSection.propertyMap[inputKey]);
        }
    };
}
