#pragma once
#include "Factory.h"
#include "InputComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(WeaponControllerIC)

class GunC;
class SoundComponent;
class AutomaticEC;
class WeaponControllerIC final : public InputComponent {
    GunC* currentGun_ = nullptr;
    GunC* secondaryGun_ = nullptr;
    SoundComponent* soundManager_ = nullptr;
    AutomaticEC* automaticEc_ = nullptr;

  public:
    void init();
    // Updates the entity's transform's
    // position upon pressing WASD keys
    void handleInput(const SDL_Event& event) override;

    GunC* getCurrentGun();
    GunC* getSecondaryGun();
    void pickUpGun(const std::string& gunName);

    void setSoundManager();
};
