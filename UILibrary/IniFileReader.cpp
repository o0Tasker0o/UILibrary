#include "IniFileReader.h"
#include <Windows.h>

using namespace std;

vector<IniSection> IniFileReader::LoadFile(string filename)
{
    FILE *pIniFile(NULL);
    fopen_s(&pIniFile, filename.c_str(), "rb");

    vector<IniSection> iniSections;

    if (NULL == pIniFile)
    {
        return iniSections;
    }

    const unsigned int cMaxLineLength = 1024;

    char pFileBuffer[cMaxLineLength];

    while (NULL != fgets(pFileBuffer, cMaxLineLength, pIniFile))
    {
        string currentLine = TrimWhitespace(pFileBuffer);

        if ('[' == currentLine[0])
        {
            IniSection newSection;

            int endBracketPosition = currentLine.find_last_of(']');

            newSection.sectionName = TrimWhitespace(currentLine.substr(1, endBracketPosition - 1));

            iniSections.push_back(newSection);
        }
        else if (currentLine.size() > 0 && iniSections.size() > 0)
        {
            iniSections.back().propertyMap.insert(ParseKeyValuePair(currentLine));
        }
    }

    fclose(pIniFile);

    return iniSections;
}

string IniFileReader::TrimWhitespace(string inputString)
{
    char const * const cWhiteSpace = " \r\n\t\f\v";

    int startOfLine = inputString.find_first_not_of(cWhiteSpace);
    int endOfLine = inputString.find_last_not_of(cWhiteSpace);

    if (startOfLine < 0 && endOfLine < 0)
    {
        return "";
    }

    return inputString.substr(startOfLine, (endOfLine + 1) - startOfLine);
}

pair<string, string> IniFileReader::ParseKeyValuePair(string keyValuePairString)
{
    int equalsPosition = keyValuePairString.find('=');

    if (equalsPosition < 0)
    {
        pair<string, string> newProperty;
        newProperty.first = keyValuePairString;
        newProperty.second = "";

        return newProperty;
    }

    string name = keyValuePairString.substr(0, equalsPosition);
    string value = keyValuePairString.substr(equalsPosition + 1);

    pair<string, string>newProperty;
    newProperty.first = name;
    newProperty.second = value;

    return newProperty;
}