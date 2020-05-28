#pragma once
#include "Factory.h"
#include "PersistentPowerUpEC.h"

DECLARE_FACTORY(IncreaseSpeedEC)

class IncreaseSpeedEC final : public PersistentPowerUpEC {
    double speedIncrement_ = 0.0;
    double originalSpeed_ = 0.0;

  public:
    void setSpeedIncrement(double value);
    void setEffect(bool value) override;
    std::string getName() override;
};