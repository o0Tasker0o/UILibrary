#include "Label.h"

using namespace System;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class LabelUnitTests
    {
      public: 
        [TestMethod]
        void ConstructorTest()
        {
           unsigned int xPosition = 1;
           unsigned int yPosition = 2;
           unsigned int width = 3;
           std::string inputText = "label";
           Label *pLabel = new Label(xPosition, yPosition, width, inputText);

           Assert::AreEqual(xPosition, pLabel->mXPosition);
           Assert::AreEqual(yPosition, pLabel->mYPosition);
           Assert::AreEqual(width, pLabel->mWidth);
           Assert::AreEqual(0U, pLabel->mHeight);
           Assert::IsTrue(inputText == pLabel->mText);

           delete pLabel;
        }
    };
}
