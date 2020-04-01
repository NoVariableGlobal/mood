#pragma once

#include "Factory.h"
#include "PowerUpC.h"
#include <string>

DECLARE_FACTORY(GunPowerUpC);

class GunPowerUpC : public PowerUpC {
    std::string _gunId;

  public:
    virtual void destroy();

    void onPickUp();

    void setGunId(const std::string& gunId);
};
