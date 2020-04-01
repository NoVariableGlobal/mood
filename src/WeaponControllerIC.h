#pragma once
#include "Factory.h"
#include "InputComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(WeaponControllerIC);

class GunC;
class WeaponControllerIC : public InputComponent {

  private:
    GunC* currentGun = nullptr;
    GunC* secondaryGun = nullptr;

  public:
    WeaponControllerIC();
    virtual ~WeaponControllerIC();

    void init();
    // Updates the entity's transform's
    // position upon pressing WASD keys
    virtual void handleInput(const SDL_Event& _event);

    GunC* getCurrentGun();
    GunC* getSecondaryGun();
    void pickUpGun(std::string _gunName);
};
