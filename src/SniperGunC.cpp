#include "SniperGunC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <OgreQuaternion.h>
#include <OgreSceneNode.h>
#include <json.h>

void SniperGunC::onShoot(TransformComponent* transform,
                         RigidbodyPC* rigidBody) {
    Ogre::Quaternion quat = getOrientation();

    transform->setPosition(myTransform->getPosition() +
                           (quat * Ogre::Vector3::UNIT_Z) * 10);
    transform->setOrientation(myTransform->getOrientation());
    rigidBody->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * _bulletSpeed);
    GunC::onShoot(transform, rigidBody);
}

// FACTORY INFRASTRUCTURE
SniperGunCFactory::SniperGunCFactory() = default;

Component* SniperGunCFactory::create(Entity* _father, Json::Value& _data,
                                     Scene* _scene) {

    SniperGunC* sniper = new SniperGunC();

    _scene->getComponentsManager()->addDC(sniper);
    sniper->setFather(_father);
    sniper->setScene(_scene);

    if (!_data["bulletTag"].isString())
        throw std::exception("SniperGunC: bulletTag is not a string");
    sniper->setBulletTag(_data["bulletTag"].asString());

    if (!_data["bulletchamberMax"].isInt())
        throw std::exception("SniperGunC: bulletchamberMax is not an int");
    sniper->setbulletchamber(_data["bulletchamberMax"].asInt());

    if (!_data["munition"].isInt())
        throw std::exception("SniperGunC: munition is not an int");
    sniper->setmunition(_data["munition"].asInt());

    if (!_data["bulletDamage"].isDouble())
        throw std::exception("SniperGunC: bulletDamage is not a double");
    sniper->setbulletdamage(_data["bulletDamage"].asDouble());

    if (!_data["bulletSpeed"].isDouble())
        throw std::exception("SniperGunC: bulletSpeed is not a double");
    sniper->setbulletspeed(_data["bulletSpeed"].asDouble());

    if (!_data["cadence"].isDouble())
        throw std::exception("SniperGunC: cadence is not an int");
    sniper->setcadence(_data["cadence"].asFloat());

    if (!_data["instakill"].isBool())
        throw std::exception("SniperGunC: instakill is not an bool");
    sniper->setInstakill(_data["instakill"].asBool());

    if (_data["infiniteAmmo"].isBool())
        sniper->setInfiniteAmmo(_data["infiniteAmmo"].asBool());

    if (!_data["bulletType"].isString())
        throw std::exception("SniperGunC: bulletType is not a string");
    sniper->setBulletType(_data["bulletType"].asString());

    if (!_data["bulletComponent"].isString())
        throw std::exception("SniperGunC: bulletComponent is not a string");
    sniper->setBulletComponentName(_data["bulletComponent"].asString());

    if (!_data["shotSound"].isString())
        throw std::exception("SniperGunC: shotSound is not a string");
    sniper->setShotSound(_data["shotSound"].asString());

    sniper->setautomatic(false);

    sniper->setTransform(reinterpret_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));

    return sniper;
};
DEFINE_FACTORY(SniperGunC);
