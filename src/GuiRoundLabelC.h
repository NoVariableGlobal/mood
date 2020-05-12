#pragma once
#pragma once

#include "Factory.h"
#include "GuiLabelC.h"
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class Window;
}

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiRoundLabelC);

class GuiRoundLabelC final : public GuiLabelComponent {
  private:
  public:
    GuiRoundLabelC();

    void createText();
};