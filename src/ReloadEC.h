#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ReloadEC);

class SoundComponent;

class ReloadEC final : public EventComponent {
  private:
    float timeToReload = 0.7f;
    float timer;
    bool reloading = false;
    SoundComponent* soundManager = nullptr;

  public:
    virtual void checkEvent();
    void starToReload();
    void setTime(float time);
    void gunChanged();
    void setSoundManager();
};
