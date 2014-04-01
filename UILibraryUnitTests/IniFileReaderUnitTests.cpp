#include "../UILibrary/IniFileReader.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class IniFileReaderUnitTests
    {
    public: 
        [TestMethod]
        void CanLoadFileFromNullFilename()
        {
            IniFileReader *pIniFileReader = new IniFileReader();

            pIniFileReader->LoadFile(nullptr);

            delete pIniFileReader;
        };
    };
}
