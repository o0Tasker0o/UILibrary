#ifndef CONTROLFACTORY_H
#define CONTROLFACTORY_H

#include <vector>
#include "Control.h"
#include "IniSection.h"
#include "ControlView.h"

class ControlFactory
{
  public:
    static std::vector<std::pair<Control *, ControlView *>> LoadControls(std::vector<IniSection> iniConfiguration);
  private:
    ControlFactory() {}
    ~ControlFactory() {}
};

#endif