#pragma once
#include "Factory.h"
#include "GuiImageC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(PowerUpIconC);

class PowerUpIconC : public GuiImageComponent {
  public:
    PowerUpIconC() = default;
    virtual ~PowerUpIconC() = default;

    virtual void destroy();

    void activePowerUpIcon();
    void desactivePowerUpIcon();
};
