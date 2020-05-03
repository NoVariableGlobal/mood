#pragma once

#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(PlayerShotIC);

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class PlayerShotIC : public InputComponent {
  private:
    bool reloading = false;
  public:
    PlayerShotIC();
    virtual ~PlayerShotIC();

    // On mouse button down, tells a gun component to fire a shot
    virtual void handleInput(const SDL_Event& _event);
    void setReloading(bool reload);
};
