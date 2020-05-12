#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(DeadManagerEC);

class AnimationLC;

class DeadManagerEC : public EventComponent {
  private:
    AnimationLC* playerAnimations = nullptr;

  public:
    DeadManagerEC();
    ~DeadManagerEC();

    virtual void setActive(bool active);
    virtual void checkEvent() override;
};