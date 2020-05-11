#pragma once
#include <string>

#include "Factory.h"
#include "ImmediatePowerUpEC.h"

class SoundComponent;

DECLARE_FACTORY(NukeEC);

class NukeEC final : public ImmediatePowerUpEC {
    SoundComponent* _soundComponent = nullptr;

  public:
    void onPick();
};
