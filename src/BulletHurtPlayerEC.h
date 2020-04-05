#pragma once
#include "Factory.h"
#include "EventComponent.h"

DECLARE_FACTORY(BulletHurtPlayerEC);
class BulletHurtPlayerEC : public EventComponent {
  public:
    BulletHurtPlayerEC();
    ~BulletHurtPlayerEC();
    virtual void checkEvent();
};