#pragma once
#include "PowerUpEC.h"
#include <string>

class PersistentPowerUpEC : public PowerUpEC {
    bool activeEffect_ = false;
    std::string hudName_;

  protected:
    virtual void setEffect(bool value) = 0;
    virtual void onDestroy();
    virtual std::string getName() = 0;

  public:
    void checkEvent();
    void setHeadsUpDisplayName(std::string name);
};
