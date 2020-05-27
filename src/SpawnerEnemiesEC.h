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

class SpawnerEnemiesEC final : public SpawnerEC {
    TransformComponent* transform_ = nullptr;
    int enemies_ = 0;

  public:
    void checkEvent() override;

    void setTransform(TransformComponent* trans);
    void setEnemies(int _enemies);
    void registerInRoundManager() override;

    void changePosition(Ogre::Vector3 newPos);
};
