#pragma once
#include "Factory.h"
#include "SpawnerEC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerEnemiesEC);
class TransformComponent;

class SpawnerEnemiesEC : public SpawnerEC {
  private:
    TransformComponent* transform = nullptr;
    int enemies;

  public:
    virtual void checkEvent() override;

    void setTransform(TransformComponent* trans);
    void setEnemies(int _enemies);
};
