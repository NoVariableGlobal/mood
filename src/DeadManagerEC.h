#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(DeadManagerEC);

class AnimationLC;

class DeadManagerEC : public EventComponent {
  private:
    // seconds to wait for scene change
    int timeToWait;
    int timeOfDeath = 0;
    bool dead = false;

    AnimationLC* playerAnimations = nullptr;

  public:
    DeadManagerEC();
    ~DeadManagerEC();

    virtual void setActive(bool active);
    virtual void setTimeToWait(int timeToWait_);
    virtual void checkEvent() override;
};