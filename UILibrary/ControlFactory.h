#ifndef CONTROLFACTORY_H
#define CONTROLFACTORY_H

#include <vector>
#include "Control.h"
#include "IniSection.h"

class ControlFactory
{
  public:
    static std::vector<Control *> LoadControls(std::vector<IniSection> iniConfiguration);
  private:
    ControlFactory() {}
    ~ControlFactory() {}
};

#endif