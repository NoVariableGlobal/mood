#pragma once
#include "Factory.h"
#include "InputComponent.h"
#include <string>

DECLARE_FACTORY(OnEPressPickUpIC)

class RigidbodyPC;
class OnEPressPickUpIC final : public InputComponent {
    RigidbodyPC* rb_ = nullptr;
    std::string objectName_;

  public:
    OnEPressPickUpIC() = default;
    ~OnEPressPickUpIC() = default;

    void handleInput(const SDL_Event& event) override;
    void setObjectName(std::string name);
};
