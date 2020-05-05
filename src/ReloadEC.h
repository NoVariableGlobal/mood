#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ReloadEC);

class ReloadEC final : public EventComponent {
  private:
    float timeToReload = 1;
    float timer;
    bool reloading = false;

  public:
    virtual void checkEvent();
    void starToReload();
    void setTime(float time);
    void gunChanged();
};
