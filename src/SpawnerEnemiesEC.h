#pragma once
#include "Factory.h"
#include "SpawnerEC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerEnemiesEC);
class TransformComponent;

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class SpawnerEnemiesEC : public SpawnerEC {
  private:
    TransformComponent* transform = nullptr;
    int enemies;

  public:
    SpawnerEnemiesEC();
    virtual void checkEvent() override;

    void setTransform(TransformComponent* trans);
    void setEnemies(int _enemies);
    virtual void registerInRoundManager();

    void changePosition(Ogre::Vector3 newPos);
};
