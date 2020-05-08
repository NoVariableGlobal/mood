#include "ComponentsManager.h"
#include "DynamicTridimensionalObjectRC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunModelManagerC.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

void GunModelManagerC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void GunModelManagerC::init(Entity* handGun, Entity* shotgun, Entity* rifle,
                            Entity* sniper) {
    _handgun = handGun;
    _shotgun = shotgun;
    _rifle = rifle;
    _sniper = sniper;

    deactivateAll();
    _handgun->setActive(true);
}

void GunModelManagerC::changeGunModel(std::string _gunId) {
    deactivateAll();

    if (_gunId == "HandGunC")
        _handgun->setActive(true);
    else if (_gunId == "ShotgunC")
        _shotgun->setActive(true);
    else if (_gunId == "AutomaticRifleC")
        _rifle->setActive(true);
    else if (_gunId == "SniperGunC")
        _sniper->setActive(true);
}

void GunModelManagerC::deactivateAll() {
    _handgun->setActive(false);
    _shotgun->setActive(false);
    _rifle->setActive(false);
    _sniper->setActive(false);
}

// FACTORY INFRASTRUCTURE
GunModelManagerCFactory::GunModelManagerCFactory() = default;

Component* GunModelManagerCFactory::create(Entity* _father, Json::Value& _data,
                                           Scene* _scene) {

    GunModelManagerC* gunModelManagerC = new GunModelManagerC();

    Entity* handgun = _scene->getEntityById("HandgunModel");
    Entity* shotgun = _scene->getEntityById("ShotgunModel");
    Entity* rifle = _scene->getEntityById("RifleModel");
    Entity* sniper = _scene->getEntityById("SniperModel");

    gunModelManagerC->init(handgun, shotgun, rifle, sniper);

    _scene->getComponentsManager()->addDC(gunModelManagerC);
    gunModelManagerC->setFather(_father);
    gunModelManagerC->setScene(_scene);

    return gunModelManagerC;
};

DEFINE_FACTORY(GunModelManagerC);