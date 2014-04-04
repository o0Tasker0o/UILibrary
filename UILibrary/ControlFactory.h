#ifndef CONTROLFACTORY_H
#define CONTROLFACTORY_H

#include <Windows.h>
#include <vector>
#include "Control.h"
#include "IniSection.h"
#include "ControlView.h"

typedef std::pair<Control *, ControlView *> ControlPair;
typedef std::vector<ControlPair> UiControls;

class ControlFactory
{
  public:
      static UiControls LoadControls(std::vector<IniSection> iniConfiguration, HWND hwnd);
  private:
    ControlFactory() {}
    ~ControlFactory() {}
};

#endif