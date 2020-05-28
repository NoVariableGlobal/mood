#pragma once
#include "Component.h"
#include "Factory.h"

DECLARE_FACTORY(BulletC)

class BulletC : public Component {
    // damage of the bullet
    float damage_;

  public:
    BulletC();
    ~BulletC();
    virtual void destroy();

    void setDamage(float d);
    float getDamage();

    // method that specify what the bullet will do if it collide with something
    // in the case of a normal bullet, it will be destroyed
    virtual void dealCollision();
};
