#pragma once
#include "EnemyBehaviourEC.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(MeleeEnemyBehaviourEC);
class MeleeEnemyBehaviourEC final : public EnemyBehaviourEC {
  public:
    void checkEvent() override;
    void rotateToPlayer() override;
};
