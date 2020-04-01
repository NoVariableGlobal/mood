#pragma once
#include "Factory.h"
#include "ImmediatePowerUpEC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(MedkitEC);

class MedkitEC final : public ImmediatePowerUpEC {
  public:
    void onPick();
};
