#pragma once
#include "EventComponent.h"
#include "Factory.h"

#include <vector>

DECLARE_FACTORY(RoundManagerEC);

class SpawnerEnemiesEC;
class SpawnerEC;

class RoundManagerEC : public EventComponent {
  private:
    int enemiesInRound = 0;
    int enemiesDead = 0;
    int minAddEnemies = 0;
    int maxAddEnemies = 0;
    int timeBetweenRounds = 10;
    float timer = 0;
    bool roundEnd = false;

    std::vector<SpawnerEnemiesEC*> enemiesSpawners;
    std::vector<SpawnerEC*> otherSpawners;

  public:
    RoundManagerEC() = default;
    ~RoundManagerEC() = default;

    virtual void checkEvent();
    void setMinAddEnemies(int n);
    void setMaxAddEnemies(int n);
    void setEnemiesInRound(int n);

    void registerEnemySpawner(SpawnerEnemiesEC* spawn);
    void registerOtherSpawner(SpawnerEC* spawn);

    void enemyDied();
};