#pragma once
#include "Component.h"
#include "Factory.h"
#include <map>
#include <string>

DECLARE_FACTORY(PowerUpTrackerC)

class PowerUpTrackerC final : public Component {
    std::map<std::string, Component*> powerUps_;

  public:
    void destroy() override;

    Component* findComponent(std::string name);
    void addPowerUp(const std::string& name, Component* powerUp);
    void removePowerUp(const std::string& name);
    void setAllPowerUpsAsNotPersistent();
};
