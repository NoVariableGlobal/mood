#include "ShotgunC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SoundComponent.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <json.h>

void ShotgunC::onPreShoot() {
    auto* spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene_->getEntityById("GameManager")->getComponent("SpawnerBulletsC"));

    // Save original rotation
    Ogre::SceneNode* node = reinterpret_cast<TridimensionalObjectRC*>(
                                father_->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode();
    const Ogre::Quaternion originalOrientation = node->getOrientation();

    // Orientate for the first pellet
    const Ogre::Real firstPelletAngle = -dispersionAngle_ * (nPellets_ / 2.0f);

    node->yaw(Ogre::Radian(Ogre::Degree(firstPelletAngle).valueRadians()));

    for (int i = 0; i < nPellets_; i++) {
        Entity* entity = spawner->getBullet(myBulletType_, myBulletTag_);

        auto* bullet =
            dynamic_cast<BulletC*>(entity->getComponent(bulletComponentName_));
        bullet->setDamage(static_cast<float>(getCalculatedDamage()));

        auto* transform = reinterpret_cast<TransformComponent*>(
            entity->getComponent("TransformComponent"));

        auto* rigidBody =
            reinterpret_cast<RigidbodyPC*>(entity->getComponent("RigidbodyPC"));

        onShoot(transform, rigidBody);

        rigidBody->setPosition(transform->getPosition());
        // Rotate the node for the next bullet
        node->yaw(Ogre::Radian(Ogre::Degree(dispersionAngle_).valueRadians()));
    }

    // Restore original rotation
    node->setOrientation(originalOrientation.w, originalOrientation.x,
                         originalOrientation.y, originalOrientation.z);

    soundManager_->playSound(shotSound_);
}

void ShotgunC::onShoot(TransformComponent* transform, RigidbodyPC* rigidBody) {
    Ogre::Quaternion quat = getOrientation();
    transform->setPosition(myTransform_->getPosition() +
                           (quat * Ogre::Vector3::UNIT_Y) * 25);
    transform->setOrientation(myTransform_->getOrientation());

    rigidBody->setLinearVelocity(-(quat * Ogre::Vector3::NEGATIVE_UNIT_Z) *
                                 bulletSpeed_);
}

void ShotgunC::setNPellets(int n) { nPellets_ = n; }

void ShotgunC::setDispersion(int n) { dispersionAngle_ = n; }

// FACTORY INFRASTRUCTURE
ShotgunCFactory::ShotgunCFactory() = default;

Component* ShotgunCFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* _scene) {

    ShotgunC* shotgun = new ShotgunC();

    _scene->getComponentsManager()->addDC(shotgun);
    shotgun->setFather(_father);
    shotgun->setScene(_scene);

    shotgun->setSoundManager();

    if (!_data["bulletTag"].isString())
        throw std::exception("ShotgunC: bulletTag is not a string");
    shotgun->setBulletTag(_data["bulletTag"].asString());

    if (!_data["bulletchamberMax"].isInt())
        throw std::exception("ShotgunC: bulletchamberMax is not an int");
    shotgun->setbulletchamber(_data["bulletchamberMax"].asInt());

    if (!_data["munition"].isInt())
        throw std::exception("ShotgunC: munition is not an int");
    shotgun->setmunition(_data["munition"].asInt());

    if (!_data["bulletDamage"].isDouble())
        throw std::exception("ShotgunC: bulletDamage is not a double");
    shotgun->setbulletdamage(_data["bulletDamage"].asDouble());

    if (!_data["bulletSpeed"].isDouble())
        throw std::exception("ShotgunC: bulletSpeed is not a double");
    shotgun->setbulletspeed(_data["bulletSpeed"].asDouble());

    if (!_data["cadence"].isDouble())
        throw std::exception("ShotgunC: cadence is not an int");
    shotgun->setcadence(_data["cadence"].asFloat());

    if (!_data["automatic"].isBool())
        throw std::exception("ShotgunC: semiautomatic is not an bool");
    shotgun->setautomatic(_data["automatic"].asBool());

    if (!_data["nPellets"].isDouble())
        throw std::exception("ShotgunC: nPellets is not an int");
    shotgun->setNPellets(_data["nPellets"].asFloat());

    if (!_data["dispersion"].isDouble())
        throw std::exception("ShotgunC: dispersion is not an int");
    shotgun->setDispersion(_data["dispersion"].asFloat());

    if (!_data["instakill"].isBool())
        throw std::exception("ShotgunC: instakill is not an bool");
    shotgun->setInstakill(_data["instakill"].asBool());

    if (_data["infiniteAmmo"].isBool())
        shotgun->setInfiniteAmmo(_data["infiniteAmmo"].asBool());

    if (!_data["bulletType"].isString())
        throw std::exception("ShotgunC: bulletType is not a string");
    shotgun->setBulletType(_data["bulletType"].asString());

    if (!_data["bulletComponent"].isString())
        throw std::exception("ShotgunC: bulletComponent is not a string");
    shotgun->setBulletComponentName(_data["bulletComponent"].asString());

    if (!_data["shotSound"].isString())
        throw std::exception("ShotgunC: shotSound is not a string");
    shotgun->setShotSound(_data["shotSound"].asString());

    shotgun->setTransform(reinterpret_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));

    return shotgun;
};

DEFINE_FACTORY(ShotgunC);
