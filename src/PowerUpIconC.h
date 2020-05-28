#pragma once
#include "Factory.h"
#include "GuiImageC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(PowerUpIconC);

class PowerUpIconC final : public GuiImageComponent {
  public:
    void destroy() override;

    void activePowerUpIcon();
    void deactivatePowerUpIcon();
};
