#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ObstacleDestroyBulletEC)

class ObstacleDestroyBulletEC final : public EventComponent {
  public:
    ObstacleDestroyBulletEC();
    ~ObstacleDestroyBulletEC();
    void checkEvent() override;
};