#pragma once
#include "Factory.h"
#include "GunC.h"
#include <string>

DECLARE_FACTORY(AutomaticRifleC);

class AutomaticRifleC : public GunC {
  public:
    AutomaticRifleC();
    ~AutomaticRifleC();

    virtual void destroy();
    virtual bool shoot();
};