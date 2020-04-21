#include "AutomaticRifleC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Ogre.h"
#include "OgreQuaternion.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"

#include <json.h>

void AutomaticRifleC::onShoot(TransformComponent* transform,
                              RigidbodyPC* rigidBody) {
    Ogre::Quaternion quat = getOrientation();

    transform->setPosition(myTransform->getPosition() +
                           (quat * Ogre::Vector3::UNIT_Z) * 10);
    transform->setOrientation(myTransform->getOrientation());

    rigidBody->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * _bulletSpeed);
}

// FACTORY INFRASTRUCTURE
AutomaticRifleCFactory::AutomaticRifleCFactory() = default;

Component* AutomaticRifleCFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {

    AutomaticRifleC* automaticRifle = new AutomaticRifleC();

    _scene->getComponentsManager()->addDC(automaticRifle);
    automaticRifle->setFather(_father);
    automaticRifle->setScene(_scene);

    if (!_data["bulletTag"].isString())
        throw std::exception("AutomaticRifleC: bulletTag is not a string");
    automaticRifle->setBulletTag(_data["bulletTag"].asString());

    if (!_data["bulletchamberMax"].isInt())
        throw std::exception("AutomaticRifleC: bulletchamberMax is not an int");
    automaticRifle->setbulletchamber(_data["bulletchamberMax"].asInt());

    if (!_data["munition"].isInt())
        throw std::exception("AutomaticRifleC: munition is not an int");
    automaticRifle->setmunition(_data["munition"].asInt());

    if (!_data["bulletDamage"].isDouble())
        throw std::exception("AutomaticRifleC: bulletDamage is not a double");
    automaticRifle->setbulletdamage(_data["bulletDamage"].asDouble());

    if (!_data["bulletSpeed"].isDouble())
        throw std::exception("AutomaticRifleC: bulletSpeed is not a double");
    automaticRifle->setbulletspeed(_data["bulletSpeed"].asDouble());

    if (!_data["cadence"].isDouble())
        throw std::exception("AutomaticRifleC: cadence is not an int");
    automaticRifle->setcadence(_data["cadence"].asFloat());

    if (!_data["automatic"].isBool())
        throw std::exception("AutomaticRifleC: automatic is not a bool");
    automaticRifle->setautomatic(_data["automatic"].asBool());

    if (!_data["instakill"].isBool())
        throw std::exception("AutomaticRifleC: instakill is not a bool");
    automaticRifle->setInstakill(_data["instakill"].asBool());

    if (_data["infiniteAmmo"].isBool())
        automaticRifle->setInfiniteAmmo(_data["infiniteAmmo"].asBool());

    if (!_data["bulletType"].isString())
        throw std::exception("AutomaticRifleC: bulletType is not a string");
    automaticRifle->setBulletType(_data["bulletType"].asString());

    if (!_data["bulletComponent"].isString())
        throw std::exception(
            "AutomaticRifleC: bulletComponent is not a string");
    automaticRifle->setBulletComponentName(_data["bulletComponent"].asString());

    if (!_data["shotSound"].isString())
        throw std::exception("AutomaticRifleC: shotSound is not a string");
    automaticRifle->setShotSound(_data["shotSound"].asString());

    automaticRifle->setTransform(dynamic_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));

    return automaticRifle;
};

DEFINE_FACTORY(AutomaticRifleC);
