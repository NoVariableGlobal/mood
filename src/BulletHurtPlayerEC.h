#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(BulletHurtPlayerEC);

class SoundComponent;
class BulletHurtPlayerEC : public EventComponent {

  private:
    SoundComponent* soundManager = nullptr;

  public:
    BulletHurtPlayerEC();
    ~BulletHurtPlayerEC();
    virtual void checkEvent();

    void setSoundManager();
};