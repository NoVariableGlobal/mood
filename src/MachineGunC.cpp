#include "MachineGunC.h"
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

void MachineGunC::onShoot(TransformComponent* transform,
                              RigidbodyPC* rigidBody) {
    Ogre::Quaternion quat = getOrientation();

    transform->setPosition(myTransform->getPosition() +
                           (quat * Ogre::Vector3::UNIT_Z) * 10);
    transform->setOrientation(myTransform->getOrientation());

    rigidBody->setLinearVelocity((quat * Ogre::Vector3::UNIT_Z) * _bulletSpeed);
}

// FACTORY INFRASTRUCTURE
MachineGunCFactory::MachineGunCFactory() = default;

Component* MachineGunCFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {

    MachineGunC* machineGun = new MachineGunC();

    _scene->getComponentsManager()->addDC(machineGun);
    machineGun->setFather(_father);
    machineGun->setScene(_scene);

    if (!_data["bulletTag"].isString())
        throw std::exception("MachineGunC: bulletTag is not a string");
    machineGun->setBulletTag(_data["bulletTag"].asString());

    if (!_data["bulletchamberMax"].isInt())
        throw std::exception("MachineGunC: bulletchamberMax is not an int");
    machineGun->setbulletchamber(_data["bulletchamberMax"].asInt());

    if (!_data["munition"].isInt())
        throw std::exception("MachineGunC: munition is not an int");
    machineGun->setmunition(_data["munition"].asInt());

    if (!_data["bulletDamage"].isDouble())
        throw std::exception("MachineGunC: bulletDamage is not a double");
    machineGun->setbulletdamage(_data["bulletDamage"].asDouble());

    if (!_data["bulletSpeed"].isDouble())
        throw std::exception("MachineGunC: bulletSpeed is not a double");
    machineGun->setbulletspeed(_data["bulletSpeed"].asDouble());

    if (!_data["cadence"].isDouble())
        throw std::exception("MachineGunC: cadence is not an int");
    machineGun->setcadence(_data["cadence"].asFloat());

    if (!_data["automatic"].isBool())
        throw std::exception("MachineGunC: automatic is not a bool");
    machineGun->setautomatic(_data["automatic"].asBool());

    if (!_data["instakill"].isBool())
        throw std::exception("MachineGunC: instakill is not a bool");
    machineGun->setInstakill(_data["instakill"].asBool());

    if (_data["infiniteAmmo"].isBool())
        machineGun->setInfiniteAmmo(_data["infiniteAmmo"].asBool());

    if (!_data["bulletType"].isString())
        throw std::exception("MachineGunC: bulletType is not a string");
    machineGun->setBulletType(_data["bulletType"].asString());

    if (!_data["bulletComponent"].isString())
        throw std::exception(
            "MachineGunC: bulletComponent is not a string");
    machineGun->setBulletComponentName(_data["bulletComponent"].asString());

    if (!_data["shotSound"].isString())
        throw std::exception("MachineGunC: shotSound is not a string");
    machineGun->setShotSound(_data["shotSound"].asString());

    machineGun->setTransform(dynamic_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));

    return machineGun;
};

DEFINE_FACTORY(MachineGunC);
