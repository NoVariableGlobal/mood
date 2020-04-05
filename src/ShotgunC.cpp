#include "ShotgunC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Ogre.h"
#include "OgreQuaternion.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <json.h>

ShotgunC::ShotgunC() : GunC() {}

ShotgunC::~ShotgunC() {}

void ShotgunC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

bool ShotgunC::shoot() {
    if (!canShoot())
        return false;

    if (!getInfiniteAmmo())
        _bulletchamber--;

    // Save original rotation
    Ogre::SceneNode* node = dynamic_cast<TridimensionalObjectRC*>(
                                father->getComponent("TridimensionalObjectRC"))
                                ->getSceneNode();
    Ogre::Quaternion ori = node->getOrientation();

    // Orientate for the first pellet
    int firstPelletAngle = -dispAngle * (nPellets / 2);

    node->yaw(Ogre::Radian(Ogre::Degree(firstPelletAngle).valueRadians()));

    for (int i = 0; i < nPellets; i++) {
        auto spawner = reinterpret_cast<SpawnerBulletsC*>(
            scene->getEntitybyId("GameManager")
                ->getComponent("SpawnerBulletsC"));
        Entity* newBullet = spawner->getBullet(_myBulletType, _myBulletTag);

        BulletC* bullet =
            dynamic_cast<BulletC*>(newBullet->getComponent("BulletC"));

        bullet->setDamage(getCalculatedDamage());

        TransformComponent* bulletTransform = dynamic_cast<TransformComponent*>(
            newBullet->getComponent("TransformComponent"));

        bulletTransform->setPosition(myTransform->getPosition());
        bulletTransform->setOrientation(myTransform->getOrientation());

        RigidbodyPC* bulletRb =
            dynamic_cast<RigidbodyPC*>(newBullet->getComponent("RigidbodyPC"));

        Ogre::Quaternion quat = node->getOrientation();

        bulletRb->setLinearVelocity(-(quat * Ogre::Vector3::NEGATIVE_UNIT_Z) *
                                    _bulletSpeed);
        bulletRb->setPosition(myTransform->getPosition());

        // Rotate the node for the next bullet
        node->yaw(Ogre::Radian(Ogre::Degree(dispAngle).valueRadians()));
    }

    // Restore original rotation
    node->setOrientation(ori.w, ori.x, ori.y, ori.z);
}

void ShotgunC::setNPellets(int n) { nPellets = n; }

void ShotgunC::setDispersion(int n) { dispAngle = n; }

// FACTORY INFRASTRUCTURE
ShotgunCFactory::ShotgunCFactory() = default;

Component* ShotgunCFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* _scene) {

    ShotgunC* shotgun = new ShotgunC();

    _scene->getComponentsManager()->addDC(shotgun);
    shotgun->setFather(_father);
    shotgun->setScene(_scene);

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

    if (!_data["bulletType"].isString())
        throw std::exception("ShotgunC: bulletType is not a string");
    shotgun->setBulletType(_data["bulletType"].asString());

    shotgun->setTransform(dynamic_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));

    return shotgun;
};
DEFINE_FACTORY(ShotgunC);