#pragma once
#include "Component.h"

class PowerUpC : public Component {
    float duration_ = 0.0f;
    bool instantaneous_ = false;

  public:
    virtual void onPickUp() = 0;

    void setDuration(float duration);
    void isInstantaneous(bool instantaneous);
};
