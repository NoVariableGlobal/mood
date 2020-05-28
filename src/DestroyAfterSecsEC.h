#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(DestroyAfterSecsEC)

class DestroyAfterSecsEC final : public EventComponent {
    int lifeTime_ = 0;
    bool firstTime_ = true;
    float creationTime_ = 0;

  public:
    void checkEvent() override;
    void setLifeTime(int n);
};