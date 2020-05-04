#pragma once

#include "GuiImageC.h"
#include "Factory.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(LifeBarC);

class LifeBarC : public GuiImageComponent {
  private:
    float x_, y_;
  public:
    LifeBarC();
    virtual ~LifeBarC();

    virtual void destroy();

    void setInitSize(float x, float y);
    void updateLifeBar(float life, float maxLife);
};
