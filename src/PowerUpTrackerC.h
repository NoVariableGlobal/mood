#pragma once

#include "Component.h"

#include "Factory.h"
#include <map>
#include <string>

DECLARE_FACTORY(PowerUpTrackerC);
class PowerUpTrackerC : public Component {
  private:
    std::map<std::string, Component*> powerUps;

  public:
    PowerUpTrackerC() = default;
    ~PowerUpTrackerC() = default;

    void destroy();

    Component* findComponent(std::string name);
    void addPowerUp(std::string name, Component* powerUp);
    void removePowerUp(std::string name);
};
