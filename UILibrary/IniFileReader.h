#ifndef INIFILEREADER_H
#define INIFILEREADER_H

#include "IniSection.h"
#include <vector>

class IniFileReader
{
  public:
    static std::vector<IniSection> LoadFile(std::string filename);

  private:
    IniFileReader() {};
    ~IniFileReader() {};

    static std::string TrimWhitespace(std::string inputString);
    static std::pair<std::string, std::string> ParseKeyValuePair(std::string keyValuePairString);
};

#endif
