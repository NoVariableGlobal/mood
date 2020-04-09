#pragma once
#include "EnemyBehaviourEC.h"
#include "Factory.h"
#include <string>

DECLARE_FACTORY(RangedEnemyBehaviourEC);
class GunC;
class RangedEnemyBehaviourEC : public EnemyBehaviourEC {

  private:
    // type of weapon equipped
    std::string weaponEquipped;

    // pointer to weapon equipped
    GunC* gun = nullptr;

  public:
    RangedEnemyBehaviourEC();
    ~RangedEnemyBehaviourEC();
    virtual void checkEvent();

    // getters and setters
    std::string getWeaponEquipped();

    void setWeaponEquipped(std::string _weaponEquipped);

    // shoot bullets in different ways depending on weaponEquipped
    void shoot();
};
