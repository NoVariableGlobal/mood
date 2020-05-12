#pragma once

#include "EventComponent.h"
#include "Factory.h"
#include <string>

class Entity;

DECLARE_FACTORY(GunModelManagerEC);

class GunModelManagerEC : public EventComponent {
    Entity* _currentGun;

    Entity* _handgun;
    Entity* _shotgun;
    Entity* _rifle;
    Entity* _sniper;

  public:
    GunModelManagerEC();
    ~GunModelManagerEC();
    virtual void checkEvent() override;

    virtual void destroy();

    void init(Entity* handGun, Entity* shotgun, Entity* rifle, Entity* sniper);

    void changeGunModel(std::string _gunId);

    void deactivateAll();
};
