#include "PowerUpTrackerC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "Util.h"
#include <utility>

void PowerUpTrackerC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

Component* PowerUpTrackerC::findComponent(std::string name) {
    return try_find(powerUps_, std::move(name));
}

void PowerUpTrackerC::addPowerUp(const std::string& name, Component* powerUp) {
    powerUps_.insert({name, powerUp});
}

void PowerUpTrackerC::removePowerUp(const std::string& name) {
    auto it = powerUps_.begin();
    while (it != powerUps_.end()) {
        if (it->first == name) {
            powerUps_.erase(it);
            break;
        }
        it++;
    }
}

void PowerUpTrackerC::setAllPowerUpsAsNotPersistent() {
    for (auto p : powerUps_)
        p.second->getFather()->setPersistent(false);
}

// FACTORY INFRASTRUCTURE
PowerUpTrackerCFactory::PowerUpTrackerCFactory() = default;

Component* PowerUpTrackerCFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {
    PowerUpTrackerC* powerUpTracker = new PowerUpTrackerC();
    _scene->getComponentsManager()->addDC(powerUpTracker);

    powerUpTracker->setFather(_father);
    powerUpTracker->setScene(_scene);

    return powerUpTracker;
};

DEFINE_FACTORY(PowerUpTrackerC);