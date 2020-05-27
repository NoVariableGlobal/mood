#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(AutomaticEC)

class SoundComponent;
class WeaponControllerIC;

// class to detect when to fire an automatic weapon depending on its cadence
class AutomaticEC : public EventComponent {
    bool shoot_ = false;
    SoundComponent* soundComponent_ = nullptr;
    WeaponControllerIC* weaponController_ = nullptr;

  public:
    AutomaticEC();
    ~AutomaticEC();
    void checkEvent() override;
    void setShoot(bool _shoot);

    void setWeaponControllerAndSound();
};