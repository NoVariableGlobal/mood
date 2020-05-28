#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(DeadManagerEC)

class AnimationLC;
class DeadManagerEC final : public EventComponent {
    AnimationLC* playerAnimations_ = nullptr;

  public:
    DeadManagerEC();
    ~DeadManagerEC();

    void setActive(bool active) override;
    void checkEvent() override;
};
