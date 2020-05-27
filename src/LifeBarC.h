#pragma once

#include "Factory.h"
#include "GuiImageC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(LifeBarC)

class LifeBarC final : public GuiImageComponent {
    float x_ = 0.0f;
    float y_ = 0.0f;

  public:
    void destroy() override;
    void setInitSize(float x, float y);
    void updateLifeBar(float life, float maxLife);
};
