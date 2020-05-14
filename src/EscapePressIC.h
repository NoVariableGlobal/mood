#pragma once

#include "Factory.h"
#include "InputComponent.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(EscapePressIC);

class EscapePressIC : public InputComponent {
  private:
    bool pressing = false;
    bool up = false;

  public:
    EscapePressIC();
    virtual ~EscapePressIC();

    virtual void handleInput(const SDL_Event& _event);
};
