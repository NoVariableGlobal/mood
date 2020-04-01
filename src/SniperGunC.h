#pragma once
#include "Factory.h"
#include "GunC.h"

DECLARE_FACTORY(SniperGunC);
class SniperGunC : public GunC {

    virtual void destroy();

    virtual bool shoot();
};
