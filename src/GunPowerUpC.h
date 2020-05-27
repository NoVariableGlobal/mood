#pragma once

#include "Factory.h"
#include "PowerUpC.h"
#include <string>

DECLARE_FACTORY(GunPowerUpC)

class GunPowerUpC final : public PowerUpC {
    std::string gunId_;

  public:
    void destroy();
    void onPickUp();
    void setGunId(const std::string& gunId);
};
