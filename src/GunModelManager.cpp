#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunModelManagerC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <iostream>
#include <json.h>

GunModelManagerC::GunModelManagerC() = default;

GunModelManagerC::~GunModelManagerC() = default;

void GunModelManagerC::checkEvent() {
    TransformComponent* _playerTransform =
        reinterpret_cast<TransformComponent*>(
            father_->getComponent("TransformComponent"));
    TransformComponent* myTransform = reinterpret_cast<TransformComponent*>(
        _currentGun->getComponent("TransformComponent"));

    Ogre::Quaternion quat = reinterpret_cast<TridimensionalObjectRC*>(
                                father_->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode()
                                ->getOrientation();

    myTransform->setOrientation(_playerTransform->getOrientation());
    if (_currentGun == _handgun) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -2 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 25 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 9);
    } else if (_currentGun == _shotgun) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -0.5 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 24.2 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    } else if (_currentGun == _rifle) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -3 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 25 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    } else if (_currentGun = _sniper) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -1 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 25 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    }
}
/*
                {
          "type": "TransformComponent",
          "attributes": {
            "position": [ 0, 10, 0 ],
            "orientation": [ 0, 90, 0 ],
            "scale": [ 0.2, 1, 0.8 ]
          }
        },
        {
          "type": "TridimensionalObjectRC",
          "attributes": {
            "mesh": "rifle.mesh",
            "node": "nWeaponModel",
            "material": "BrownColourMaterial"
          }
        }
*/
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
    _currentGun = _handgun;
}

void GunModelManagerC::changeGunModel(std::string _gunId) {
    deactivateAll();

    if (_gunId == "HandGunC") {
        _handgun->setActive(true);
        _currentGun = _handgun;
    } else if (_gunId == "ShotgunC") {
        _shotgun->setActive(true);
        _currentGun = _shotgun;
    } else if (_gunId == "AutomaticRifleC") {
        _rifle->setActive(true);
        _currentGun = _rifle;
    } else if (_gunId == "SniperGunC") {
        _sniper->setActive(true);
        _currentGun = _sniper;
    }
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

    _scene->getComponentsManager()->addEC(gunModelManagerC);
    gunModelManagerC->setFather(_father);
    gunModelManagerC->setScene(_scene);

    return gunModelManagerC;
};

DEFINE_FACTORY(GunModelManagerC);