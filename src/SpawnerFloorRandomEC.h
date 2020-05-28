#pragma once
#include "Factory.h"
#include "SpawnerEC.h"

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<4, Real> Vector4f;
} // namespace Ogre

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerFloorRandomEC)

class SpawnerFloorRandomEC final : public SpawnerEC {
    Ogre::Vector4f* floorDimensions_;
    bool first_ = true;

  public:
    SpawnerFloorRandomEC();
    ~SpawnerFloorRandomEC();

    void checkEvent() override;
    void setFloorDimensions(Ogre::Vector4f floorDimensions);
    void registerInRoundManager() override;
};
