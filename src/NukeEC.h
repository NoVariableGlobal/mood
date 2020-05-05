#pragma once
#include <string>

#include "Factory.h"
#include "ImmediatePowerUpEC.h"

class SoundComponent;

DECLARE_FACTORY(NukeEC);

class NukeEC final : public ImmediatePowerUpEC {
    SoundComponent* _soundComponent = nullptr;
    std::string _sound;

  public:
    void onPick();
    void setSound(const std::string& sound);
};
