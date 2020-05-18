#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <SoundComponent.h>
#include <iostream>
#include <json.h>

AutomaticEC::AutomaticEC() {}

AutomaticEC::~AutomaticEC() {}

void AutomaticEC::checkEvent() {
    if (shoot)
        weaponController->getCurrentGun()->shoot();
}

void AutomaticEC::setShoot(bool _shoot) { shoot = _shoot; }

void AutomaticEC::setWeaponControllerAndSound() {
    weaponController = dynamic_cast<WeaponControllerIC*>(
        father_->getComponent("WeaponControllerIC"));

    _soundComponent = dynamic_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}

// FACTORY INFRASTRUCTURE
AutomaticECFactory::AutomaticECFactory() = default;

Component* AutomaticECFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* scene) {
    AutomaticEC* automatic = new AutomaticEC();

    automatic->setFather(_father);
    automatic->setScene(scene);

    scene->getComponentsManager()->addEC(automatic);

    automatic->setActive(true);
    automatic->setWeaponControllerAndSound();
    return automatic;
};

DEFINE_FACTORY(AutomaticEC);