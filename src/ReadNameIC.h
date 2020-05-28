#pragma once
#include "Factory.h"
#include "InputComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(ReadNameIC);

class ReadNameIC final : public InputComponent {
    std::string name_;

  public:
    void addLetter(char letter);
    void removeLetter();

    std::string gatName();
    // On mouse button down, tells a gun component to fire a shot
    void handleInput(const SDL_Event& event) override;
};
