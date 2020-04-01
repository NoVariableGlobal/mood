#pragma once
#include "Factory.h"
#include "ImmediatePowerUpEC.h"

DECLARE_FACTORY(NukeEC);

class NukeEC final : public ImmediatePowerUpEC {
  public:
    void onPick();
};
