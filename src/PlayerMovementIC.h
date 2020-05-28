#pragma once
#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(PlayerMovementIC)

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class AnimationLC;
class PlayerMovementIC;
class PlayerMovementIC final : public InputComponent {
    float speed_ = 0;
    AnimationLC* animations_ = nullptr;

    bool wDown_ = false;
    bool sDown_ = false;
    bool aDown_ = false;
    bool dDown_ = false;

  public:
    // TODO(kyranet): Encapsulate this
    bool hit_ = false;

    // Updates the entity's transform's
    // position upon pressing WASD keys
    void handleInput(const SDL_Event& event) override;

    // getter for _speed
    float getMovementSpeed();

    // Sets the speed the entity moves at
    void setMovementSpeed(float speed);

    void setIdleAnimation();
};
