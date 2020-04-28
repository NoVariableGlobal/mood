#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(AnimationPlayerEC);

class AnimationLC;

class AnimationPlayerEC : public EventComponent {
  private:
    bool idle;
    bool run;
    AnimationLC* playerAnimations = nullptr;

  public:
    AnimationPlayerEC();
    ~AnimationPlayerEC();

    virtual void setActive(bool active);
    virtual void checkEvent() override;
};