#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(BulletHurtPlayerEC)

class SoundComponent;
class BulletHurtPlayerEC final : public EventComponent {
    SoundComponent* soundManager_ = nullptr;

  public:
    BulletHurtPlayerEC();
    ~BulletHurtPlayerEC();
    void checkEvent() override;
    void setSoundManager();
};