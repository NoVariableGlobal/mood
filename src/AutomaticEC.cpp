#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <SoundComponent.h>
#include <iostream>
#include <json.h>
#include <time.h>

AutomaticEC::AutomaticEC() {}

AutomaticEC::~AutomaticEC() {}

void AutomaticEC::checkEvent() {
    cadence = (dynamic_cast<WeaponControllerIC*>(
                   father_->getComponent("WeaponControllerIC")))
                  ->getCurrentGun()
                  ->getcadence();
    if (shoot && timeCadence()) {
        (dynamic_cast<WeaponControllerIC*>(
             father_->getComponent("WeaponControllerIC")))
            ->getCurrentGun()
            ->shoot();
        if ((dynamic_cast<WeaponControllerIC*>(
                 father_->getComponent("WeaponControllerIC")))
                ->getCurrentGun()
                ->getbulletchamber() == 0)
            setShoot(false);
    }
}

bool AutomaticEC::timeCadence() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimecadence >= cadence) {
        lastTimecadence = seconds;
        return true;
    }

    return false;
}

void AutomaticEC::setCadence(double _cadence) { cadence = _cadence; }

void AutomaticEC::setShoot(bool _shoot) {
    shoot = _shoot;
    if (_soundComponent == nullptr)
        _soundComponent =
            dynamic_cast<SoundComponent*>(scene_->getEntityById("GameManager")
                                              ->getComponent("SoundComponent"));
    if (shoot) {
        _soundComponent->playSound(
            dynamic_cast<WeaponControllerIC*>(
                father_->getComponent("WeaponControllerIC"))
                ->getCurrentGun()
                ->getShotSound());
    } else {
        _soundComponent->stopSound(
            dynamic_cast<WeaponControllerIC*>(
                father_->getComponent("WeaponControllerIC"))
                ->getCurrentGun()
                ->getShotSound());
    }
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

    return automatic;
};

DEFINE_FACTORY(AutomaticEC);