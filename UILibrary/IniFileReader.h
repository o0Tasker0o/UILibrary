#ifndef INIFILEREADER_H
#define INIFILEREADER_H

class IniFileReader
{
public:
    IniFileReader();
    ~IniFileReader();
    void LoadFile(char const * const pFilename);
};

#endif
