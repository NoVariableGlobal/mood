#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(BulletHurtPlayerEC);
class BulletHurtPlayerEC : public EventComponent {
  public:
    BulletHurtPlayerEC();
    ~BulletHurtPlayerEC();
    virtual void checkEvent();
};