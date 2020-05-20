#pragma once
#include "Factory.h"
#include "InputComponent.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(ReadNameIC);

class ReadNameIC : public InputComponent {
  private:
    std::string name;

  public:
    ReadNameIC();
    virtual ~ReadNameIC();

    void addLetter(char letter);
    void removeLetter();

    std::string gatName();
    // On mouse button down, tells a gun component to fire a shot
    virtual void handleInput(const SDL_Event& _event);
};
