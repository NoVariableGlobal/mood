#pragma once
#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(OrientateToMouseIC);
class OrientateToMouseIC : public InputComponent {
  public:
    OrientateToMouseIC() = default;
    ~OrientateToMouseIC() = default;
    void handleInput(const SDL_Event& _event);
};
