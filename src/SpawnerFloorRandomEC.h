#pragma once
#include "Factory.h"
#include "SpawnerEC.h"

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<4, Real> Vector4f;
} // namespace Ogre

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerFloorRandomEC);

class SpawnerFloorRandomEC : public SpawnerEC {
  private:
    Ogre::Vector4f* floorDimensions;
    bool first = true;

  public:
    SpawnerFloorRandomEC();
    virtual ~SpawnerFloorRandomEC();
    virtual void checkEvent() override;
    void setFloorDimensions(Ogre::Vector4f _floorDimensions);
};
