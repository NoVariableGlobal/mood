#pragma once

#include "Component.h"
#include "Factory.h"
#include <string>

class Entity;

DECLARE_FACTORY(GunModelManagerC);

class GunModelManagerC : public Component {
    Entity* _handgun;
    Entity* _shotgun;
    Entity* _rifle;
    Entity* _sniper;

  public:
    virtual void destroy();

    void init(Entity* handGun, Entity* shotgun, Entity* rifle, Entity* sniper);

    void changeGunModel(std::string _gunId);

	void deactivateAll();
};
