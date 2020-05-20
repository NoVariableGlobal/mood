#pragma once
#include "Factory.h"
#include "InputComponent.h"
class AnimationLC;

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(PlayerMovementIC);

class PlayerMovementIC;

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class PlayerMovementIC : public InputComponent {
  private:
    float _speed = 0;
    AnimationLC* animations = nullptr;

    bool wDown = false, sDown = false, aDown = false, dDown = false;

  public:
    bool hit = false;
    PlayerMovementIC();
    virtual ~PlayerMovementIC();

    // Updates the entity's transform's
    // position upon pressing WASD keys
    virtual void handleInput(const SDL_Event& _event);

    // getter for _speed
    float getMovementSpeed();

    // Sets the speed the entity moves at
    void setMovementSpeed(float speed);

    void setIdleAnimation();
};
