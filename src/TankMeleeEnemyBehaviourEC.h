#pragma once
#include "EnemyBehaviourEC.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(TankMeleeEnemyBehaviourEC);
class TankMeleeEnemyBehaviourEC : public EnemyBehaviourEC {

  public:
    TankMeleeEnemyBehaviourEC();
    ~TankMeleeEnemyBehaviourEC();

    virtual void checkEvent();
    virtual void rotateToPlayer();
};
