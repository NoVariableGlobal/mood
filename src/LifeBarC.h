#pragma once

#include "GuiImageC.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(LifeBarC);

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class LifeBarC : public GuiImageComponent {
  public:
    LifeBarC();
    virtual ~LifeBarC();

    virtual void destroy();

    void updateLifeBar(int life, int maxLife);
};
