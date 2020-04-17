#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(DeadManagerEC);

class AnimationLC;

class DeadManagerEC : public EventComponent {
  private:
    int timeToWait = 0;

    AnimationLC* playerAnimations = nullptr;

  public:
    DeadManagerEC();
    ~DeadManagerEC();

    virtual void setActive(bool active);
    virtual void checkEvent() override;
};