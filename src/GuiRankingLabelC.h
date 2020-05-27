#pragma once

#include "Factory.h"
#include "GuiLabelC.h"

namespace CEGUI {
    class Window;
}

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GuiRankingLabelC)

class GuiRankingLabelC final : public GuiLabelComponent {
  public:
    GuiRankingLabelC();

    void createText(bool roundNumber, int rankingPosition);
};
