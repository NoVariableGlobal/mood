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
  private:
    float x_, y_;
  public:
    LifeBarC();
    virtual ~LifeBarC();

    virtual void destroy();

    void setInitSize(float x, float y);
    void updateLifeBar(float life, float maxLife);
};
