#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ObstacleDestroyBulletEC);
class ObstacleDestroyBulletEC : public EventComponent {
  public:
    ObstacleDestroyBulletEC();
    ~ObstacleDestroyBulletEC();
    virtual void checkEvent();
};