#include "HandGunC.h"
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

void HandGunC::onShoot(TransformComponent* transform, RigidbodyPC* rigidBody) {
    Ogre::Quaternion quat = getOrientation();

    transform->setPosition(myTransform->getPosition() +
                           (quat * Ogre::Vector3::UNIT_Z) * 10);
    transform->setOrientation(myTransform->getOrientation());

    rigidBody->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * _bulletSpeed);
}

// FACTORY INFRASTRUCTURE
HandGunCFactory::HandGunCFactory() = default;

Component* HandGunCFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* _scene) {

    HandGunC* hg = new HandGunC();

    _scene->getComponentsManager()->addDC(hg);
    hg->setFather(_father);
    hg->setScene(_scene);

    if (!_data["bulletTag"].isString())
        throw std::exception("HandGunC: bulletTag is not a string");
    hg->setBulletTag(_data["bulletTag"].asString());

    if (!_data["bulletchamberMax"].isInt())
        throw std::exception("HandGunC: bulletchamberMax is not an int");
    hg->setbulletchamber(_data["bulletchamberMax"].asInt());

    if (!_data["munition"].isInt())
        throw std::exception("HandGunC: munition is not an int");
    hg->setmunition(_data["munition"].asInt());

    if (!_data["bulletDamage"].isDouble())
        throw std::exception("HandGunC: bulletDamage is not a double");
    hg->setbulletdamage(_data["bulletDamage"].asDouble());

    if (!_data["bulletSpeed"].isDouble())
        throw std::exception("HandGunC: bulletSpeed is not a double");
    hg->setbulletspeed(_data["bulletSpeed"].asDouble());

    if (!_data["cadence"].isDouble())
        throw std::exception("HandGunC: cadence is not an int");
    hg->setcadence(_data["cadence"].asFloat());

    if (!_data["automatic"].isBool())
        throw std::exception("HandGunC: semiautomatic is not an bool");
    hg->setautomatic(_data["automatic"].asBool());

    if (!_data["instakill"].isBool())
        throw std::exception("HandGunC: instakill is not an bool");
    hg->setInstakill(_data["instakill"].asBool());

    if (_data["infiniteAmmo"].isBool())
        hg->setInfiniteAmmo(_data["infiniteAmmo"].asBool());

    if (!_data["bulletType"].isString())
        throw std::exception("HandGunC: bulletType is not a string");
    hg->setBulletType(_data["bulletType"].asString());

    if (!_data["bulletComponent"].isString())
        throw std::exception("HandGunC: bulletComponent is not a string");
    hg->setBulletComponentName(_data["bulletComponent"].asString());

    hg->setTransform(reinterpret_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));

    return hg;
};

DEFINE_FACTORY(HandGunC);
