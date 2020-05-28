#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ReloadEC)

class SoundComponent;
class ReloadEC final : public EventComponent {
    float timeToReload_ = 0.7f;
    float timer_ = 0.0f;
    bool reloading_ = false;
    SoundComponent* soundManager_ = nullptr;

  public:
    void checkEvent() override;
    void starToReload();
    void setTime(float time);
    void gunChanged();
    void setSoundManager();
};
