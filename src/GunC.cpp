#include "GunC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "Ogre.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

Ogre::Quaternion GunC::getOrientation() const {
    return reinterpret_cast<TridimensionalObjectRC*>(
               father->getComponent("TridimensionalObjectRC"))
        ->getSceneNode()
        ->getOrientation();
}

void GunC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

bool GunC::reload() {
    if (_bulletchamber < _bulletchamberMax && _munition > 0) {
        int gunreload = _bulletchamberMax - _bulletchamber;

        if (gunreload > _munition)
            gunreload = _munition;

        _bulletchamber += gunreload;
        _munition -= gunreload;

        return true;
    } else
        return false;
}

bool GunC::shoot() {
    if (!canShoot())
        return false;

    if (!getInfiniteAmmo())
        _bulletchamber--;

    onPreShoot();
    return true;
}

void GunC::onPreShoot() {
    auto spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene->getEntitybyId("GameManager")->getComponent("SpawnerBulletsC"));

    Entity* newBullet = spawner->getBullet(_myBulletType, _myBulletTag);

    BulletC* bullet =
        dynamic_cast<BulletC*>(newBullet->getComponent(bulletComponentName_));
    bullet->setDamage(getCalculatedDamage());

    TransformComponent* transform = reinterpret_cast<TransformComponent*>(
        newBullet->getComponent("TransformComponent"));

    RigidbodyPC* bulletRb =
        reinterpret_cast<RigidbodyPC*>(newBullet->getComponent("RigidbodyPC"));
    bulletRb->setPosition(transform->getPosition());

    onShoot(bullet, transform, bulletRb);
}

std::string GunC::getBulletType() { return _myBulletType; }

std::string GunC::getBulletTag() { return _myBulletTag; }

std::string GunC::getBulletComponentName() { return bulletComponentName_; }

int GunC::getbulletchamber() { return _bulletchamber; }

int GunC::getmunition() { return _munition; }

int GunC::getbulletdamage() { return _bulletDamage; }

int GunC::getbulletspeed() { return _bulletSpeed; }

float GunC::getcadence() { return _cadence; }

bool GunC::getautomatic() { return _automatic; }

void GunC::setBulletType(std::string bulletType) { _myBulletType = bulletType; }

void GunC::setBulletTag(std::string bulletTag) { _myBulletTag = bulletTag; }

void GunC::setBulletComponentName(std::string name) {
    bulletComponentName_ = name;
}

bool GunC::getInfiniteAmmo() { return infiniteAmmo_; }

bool GunC::getInstakill() { return instakill_; }

void GunC::setbulletchamber(int bulletchamberMax) {
    _bulletchamberMax = bulletchamberMax;
    _bulletchamber = bulletchamberMax;
}

void GunC::setmunition(int munition) {
    _munition = munition;
    _munitionMax = munition;
}

void GunC::setbulletdamage(int damage) { _bulletDamage = damage; }

void GunC::setbulletspeed(int speed) { _bulletSpeed = speed; }

void GunC::setcadence(float cadence) { _cadence = cadence; }

void GunC::setautomatic(bool automatic) { _automatic = automatic; }

void GunC::setInfiniteAmmo(bool infinite) { infiniteAmmo_ = infinite; }

void GunC::setInstakill(bool instakill) { instakill_ = instakill; }

void GunC::setTransform(TransformComponent* trans) { myTransform = trans; }

bool GunC::mmunitionleft() {
    if (_bulletchamber == 0 && _munition == 0)
        return false;
    else
        return true;
}

void GunC::reset() {
    _bulletchamber = _bulletchamberMax;
    _munition = _munitionMax;
}
bool GunC::canShoot() { return infiniteAmmo_ || _bulletchamber != 0; }

int GunC::getCalculatedDamage() {
    return instakill_ ? std::numeric_limits<int>::max() : _bulletDamage;
}
