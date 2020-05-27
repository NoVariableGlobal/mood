#pragma once
#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(OrientateToMouseIC)

class OrientateToMouseIC final : public InputComponent {
  public:
    void handleInput(const SDL_Event& event) override;
};
