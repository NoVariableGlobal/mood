#pragma once
#include "Factory.h"
#include "ImmediatePowerUpEC.h"

DECLARE_FACTORY(NukeEC)

class SoundComponent;
class NukeEC final : public ImmediatePowerUpEC {
    SoundComponent* soundComponent_ = nullptr;

  public:
    void onPick() override;
};
