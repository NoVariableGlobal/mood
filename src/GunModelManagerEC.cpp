#include "GunModelManagerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <iostream>
#include <json.h>

GunModelManagerEC::GunModelManagerEC() = default;

GunModelManagerEC::~GunModelManagerEC() = default;

void GunModelManagerEC::checkEvent() {
    TransformComponent* _playerTransform =
        reinterpret_cast<TransformComponent*>(
            father_->getComponent("TransformComponent"));
    TransformComponent* myTransform = reinterpret_cast<TransformComponent*>(
        currentGun_->getComponent("TransformComponent"));

    Ogre::Quaternion quat = reinterpret_cast<TridimensionalObjectRC*>(
                                father_->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode()
                                ->getOrientation();

    myTransform->setOrientation(_playerTransform->getOrientation());
    if (currentGun_ == handgun_) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -2 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 25 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 9);
    } else if (currentGun_ == shotgun_) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -0.5 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 24.2 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    } else if (currentGun_ == rifle_) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -3 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 25 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    } else if (currentGun_ = sniper_) {
        myTransform->setPosition(_playerTransform->getPosition() +
                                 (quat * Ogre::Vector3::UNIT_X) * -1 +
                                 (quat * Ogre::Vector3::UNIT_Y) * 25 +
                                 (quat * Ogre::Vector3::UNIT_Z) * 10);
    }
}

void GunModelManagerEC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseEC(this);
}

void GunModelManagerEC::init(Entity* handGun, Entity* shotgun, Entity* rifle,
                             Entity* sniper) {
    handgun_ = handGun;
    shotgun_ = shotgun;
    rifle_ = rifle;
    sniper_ = sniper;

    deactivateAll();
    handgun_->setActive(true);
    currentGun_ = handgun_;
}

void GunModelManagerEC::changeGunModel(const std::string& gunId) {
    deactivateAll();

    if (gunId == "HandGunC") {
        handgun_->setActive(true);
        currentGun_ = handgun_;
    } else if (gunId == "ShotgunC") {
        shotgun_->setActive(true);
        currentGun_ = shotgun_;
    } else if (gunId == "AutomaticRifleC") {
        rifle_->setActive(true);
        currentGun_ = rifle_;
    } else if (gunId == "SniperGunC") {
        sniper_->setActive(true);
        currentGun_ = sniper_;
    }
}

void GunModelManagerEC::deactivateAll() {
    handgun_->setActive(false);
    shotgun_->setActive(false);
    rifle_->setActive(false);
    sniper_->setActive(false);
}

// FACTORY INFRASTRUCTURE
GunModelManagerECFactory::GunModelManagerECFactory() = default;

Component* GunModelManagerECFactory::create(Entity* _father, Json::Value& _data,
                                            Scene* _scene) {

    GunModelManagerEC* gunModelManagerC = new GunModelManagerEC();

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

DEFINE_FACTORY(GunModelManagerEC);