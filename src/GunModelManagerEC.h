#pragma once

#include "EventComponent.h"
#include "Factory.h"
#include <string>

DECLARE_FACTORY(GunModelManagerEC)

class Entity;
class GunModelManagerEC final : public EventComponent {
    Entity* currentGun_;
    Entity* handgun_;
    Entity* shotgun_;
    Entity* rifle_;
    Entity* sniper_;

  public:
    GunModelManagerEC();
    ~GunModelManagerEC();
    void checkEvent() override;
    void destroy() override;

    void init(Entity* handGun, Entity* shotgun, Entity* rifle, Entity* sniper);
    void changeGunModel(const std::string& gunId);
    void deactivateAll();
};
