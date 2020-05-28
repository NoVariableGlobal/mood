#pragma once
#include "EnemyBehaviourEC.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(TankMeleeEnemyBehaviourEC)

class TankMeleeEnemyBehaviourEC final : public EnemyBehaviourEC {

  public:
    TankMeleeEnemyBehaviourEC();
    ~TankMeleeEnemyBehaviourEC();

    void checkEvent() override;
    void rotateToPlayer() override;
};
