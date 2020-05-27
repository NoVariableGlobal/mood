#pragma once
#include "EventComponent.h"
#include "Factory.h"
#include <vector>

DECLARE_FACTORY(RoundManagerEC)

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
    typedef Vector<4, Real> Vector4f;
} // namespace Ogre

class SpawnerEnemiesEC;
class SpawnerFloorRandomEC;
class RoundManagerEC final : public EventComponent {
    int enemiesInRound_ = 0;
    int enemiesDead_ = 0;
    int minAddEnemies_ = 0;
    int maxAddEnemies_ = 0;
    int timeBetweenRounds_ = 10;
    int roundNumber_ = 1;
    float timer_ = 0;
    bool roundEnd_ = false;

    int lastMap_ = 1;

    std::vector<SpawnerEnemiesEC*> enemiesSpawners_;
    std::vector<SpawnerFloorRandomEC*> otherSpawners_;

    std::vector<Ogre::Vector3> map1Spawners_;
    std::vector<Ogre::Vector3> map2Spawners_;
    std::vector<Ogre::Vector3> map3Spawners_;
    std::vector<Ogre::Vector3> map4Spawners_;

    std::vector<Ogre::Vector4f> otherSpawnersPos_;

  public:
    void checkEvent() override;

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