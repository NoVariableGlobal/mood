#pragma once
#include "Factory.h"
#include "GunC.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(HandGunC);

class HandGunC : public GunC {
  private:
  public:
    HandGunC();
    ~HandGunC();

    virtual void destroy();

    virtual bool shoot();
};
