#pragma once
#include "EventComponent.h"
#include "Factory.h"

#include <vector>

DECLARE_FACTORY(RoundManagerEC);

class SpawnerEnemiesEC;
class SpawnerFloorRandomEC;

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
    typedef Vector<4, Real> Vector4f;
} // namespace Ogre

class RoundManagerEC : public EventComponent {
  private:
    int enemiesInRound = 0;
    int enemiesDead = 0;
    int minAddEnemies = 0;
    int maxAddEnemies = 0;
    int timeBetweenRounds = 10;
    int roundNumber = 1;
    float timer = 0;
    bool roundEnd = false;

    int lastMap = 1;

    std::vector<SpawnerEnemiesEC*> enemiesSpawners;
    std::vector<SpawnerFloorRandomEC*> otherSpawners;

    std::vector<Ogre::Vector3> map1Spawners;
    std::vector<Ogre::Vector3> map2Spawners;
    std::vector<Ogre::Vector3> map3Spawners;
    std::vector<Ogre::Vector3> map4Spawners;

    std::vector<Ogre::Vector4f> otherSpawnersPos;

  public:
    RoundManagerEC() = default;
    ~RoundManagerEC() = default;

    virtual void checkEvent();

    void changeMap();

    void deactivateSpawnerEnemies();
    void deactivateOtherSpawners();

    void setMinAddEnemies(int n);
    void setMaxAddEnemies(int n);
    void setEnemiesInRound(int n);

    void setTimeBetweenRounds(int n);

    void registerEnemySpawner(SpawnerEnemiesEC* spawn);
    void registerOtherSpawner(SpawnerFloorRandomEC* spawn);

    int getRoundNumber();

    void enemyDied();

    void setEnemySpawnersPositions(Ogre::Vector3 pos, int map);

    void setOtherSpawnersPositions(Ogre::Vector4f pos);
};