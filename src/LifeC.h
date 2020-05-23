#pragma once

#include "Component.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(LifeC);

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class LifeC : public Component {
  private:
    int totalLife = 0;
    float currentLife = 0.0f;
    bool invulnerability = false;

  public:
    LifeC();
    virtual ~LifeC();

    virtual void destroy();

    // get the current life
    float getLife();
    // set the current life
    void setLife(int _life);

    // get the total life
    int getTotalLife();
    // set the total life
    void setTotalLife(int _life);

    // Subtract the damage to the life. Returns a `boolean` value defining
    // whether or not `currentLife` reached 0.
    bool doDamage(float _damage);
    // subtract the damage to the life
    void heal(float _heal);
    void setInvulnerability(bool _invulnerability);
};
