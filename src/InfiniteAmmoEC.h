#pragma once
#include "Factory.h"
#include "PersistentPowerUpEC.h"

DECLARE_FACTORY(InfiniteAmmoEC);
class InfiniteAmmoEC final : public PersistentPowerUpEC {
  public:
    void setEffect(bool value) override;
    std::string getName() override;
};
