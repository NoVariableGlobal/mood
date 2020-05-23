#include "IncreaseSpeedEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "PlayerMovementIC.h"
#include "Scene.h"
#include "SoundComponent.h"
#include <json.h>

void IncreaseSpeedEC::setEffect(bool value) {
    Entity* player = scene_->getEntityById("Player");
    auto* movement = reinterpret_cast<PlayerMovementIC*>(
        player->getComponent("PlayerMovementIC"));

    soundManager->playSound("Speed");

    if (value) {
        originalSpeed_ = movement->getMovementSpeed();
        movement->setMovementSpeed(originalSpeed_ * (1 + speedIncrement_));
    } else {
        movement->setMovementSpeed(originalSpeed_);
    }
}

std::string IncreaseSpeedEC::getName() { return "IncreaseSpeedEC"; }

void IncreaseSpeedEC::setSpeedIncrement(double value) {
    speedIncrement_ = value;
}

// FACTORY INFRASTRUCTURE
IncreaseSpeedECFactory::IncreaseSpeedECFactory() = default;

Component* IncreaseSpeedECFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* scene) {
    IncreaseSpeedEC* increaseSpeed = new IncreaseSpeedEC();
    scene->getComponentsManager()->addEC(increaseSpeed);
    increaseSpeed->setFather(_father);
    increaseSpeed->setScene(scene);

    increaseSpeed->setSoundManager();

    if (!_data["time"].isDouble())
        throw std::exception("IncreaseSpeed: time is not a double");
    increaseSpeed->setDuration(_data["time"].asDouble());
    if (!_data["timeEffect"].isDouble())
        throw std::exception("IncreaseSpeed: timeEffect is not a double");
    increaseSpeed->setDuration(_data["timeEffect"].asDouble());
    if (!_data["speedIncrement"].isDouble())
        throw std::exception("IncreaseSpeed: speedIncrement is not a double");
    increaseSpeed->setSpeedIncrement(_data["speedIncrement"].asDouble());

    increaseSpeed->setHUDName("SpeedHUD");

    increaseSpeed->setActive(true);

    return increaseSpeed;
}

DEFINE_FACTORY(IncreaseSpeedEC);
