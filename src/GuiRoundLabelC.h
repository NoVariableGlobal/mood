#pragma once
#include "Factory.h"
#include "GuiLabelC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiRoundLabelC);

class GuiRoundLabelC final : public GuiLabelComponent {
  private:
  public:
    GuiRoundLabelC();

    void createText();
};