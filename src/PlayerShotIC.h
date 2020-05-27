#pragma once
#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(PlayerShotIC)

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class PlayerShotIC final : public InputComponent {
    bool reloading_ = false;

  public:
    // On mouse button down, tells a gun component to fire a shot
    void handleInput(const SDL_Event& event) override;
    void setReloading(bool reload);
};
