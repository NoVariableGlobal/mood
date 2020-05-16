#pragma once
#include "EventComponent.h"
#include "Factory.h"
class SoundComponent;
class WeaponControllerIC;

DECLARE_FACTORY(AutomaticEC);
// class to detect when to fire an automatic weapon depending on its cadence
class AutomaticEC : public EventComponent {
  private:
    bool shoot = false;
    SoundComponent* _soundComponent = nullptr;
    WeaponControllerIC* weaponController = nullptr;

  public:
    AutomaticEC();
    ~AutomaticEC();
    virtual void checkEvent() override;
    void setShoot(bool _shoot);

    void setWeaponControllerAndSound();
};