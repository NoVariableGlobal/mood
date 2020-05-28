#pragma once
#include "EnemyBehaviourEC.h"
#include "Factory.h"
#include <string>

DECLARE_FACTORY(RangedEnemyBehaviourEC)

class GunC;
class SoundComponent;
class RangedEnemyBehaviourEC final : public EnemyBehaviourEC {
    // type of weapon equipped
    std::string weaponEquipped_;

    // pointer to weapon equipped
    GunC* gun_ = nullptr;
    SoundComponent* soundComponent_ = nullptr;

  public:
    void checkEvent() override;
    void rotateToPlayer() override;

    // getters and setters
    std::string getWeaponEquipped();

    void setWeaponEquipped(std::string weaponEquipped);

    // shoot bullets in different ways depending on weaponEquipped
    void shoot();
};
