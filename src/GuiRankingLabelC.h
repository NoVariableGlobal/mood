#pragma once


#include "Factory.h"
#include "GuiLabelC.h"
#include <glm/glm.hpp>
#include <string>

namespace CEGUI {
    class Window;
}

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiRankingLabelC);

class GuiRankingLabelC final : public GuiLabelComponent {
  private:

  public:
    GuiRankingLabelC();

    void createText(bool roundNumber, int rankingPosition);
};
