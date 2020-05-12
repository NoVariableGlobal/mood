#include "GunC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "GuiLabelC.h"
#include "Ogre.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <SoundComponent.h>

void GunC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

bool GunC::reload() {
	// For weapons with limited ammo
    if (_bulletchamber < _bulletchamberMax && _munition > 0) {
        int remainder = _bulletchamberMax - _bulletchamber;

        if (remainder > _munition)
            remainder = _munition;

        _bulletchamber += remainder;
        _munition -= remainder;

        updateAmmoTracker();

        return true;

	// For weapons with unlimited ammo
    } else if (_bulletchamber < _bulletchamberMax && _munition < 0) {
        _bulletchamber = _bulletchamberMax;
        updateAmmoTracker();

        return true;
    }

    return false;
}

bool GunC::shoot() {
    if (!timeCadence())
        return false;

    if (!canShoot()) {
        soundManager->playSound("EmptyGun");
        return false;
    }

    if (!getInfiniteAmmo()) {
        _bulletchamber--;

        updateAmmoTracker();
    }

    onPreShoot();
    return true;
}

void GunC::onPreShoot() {
    auto* spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene_->getEntityById("GameManager")->getComponent("SpawnerBulletsC"));

    Entity* entity = spawner->getBullet(_myBulletType, _myBulletTag);

    auto* bullet =
        dynamic_cast<BulletC*>(entity->getComponent(bulletComponentName_));
    bullet->setDamage(static_cast<float>(getCalculatedDamage()));

    auto* transform = reinterpret_cast<TransformComponent*>(
        entity->getComponent("TransformComponent"));

    auto* rigidBody =
        reinterpret_cast<RigidbodyPC*>(entity->getComponent("RigidbodyPC"));

    onShoot(transform, rigidBody);

    rigidBody->setPosition(transform->getPosition());
}

Ogre::Quaternion GunC::getOrientation() const {
    return reinterpret_cast<TridimensionalObjectRC*>(
               father_->getComponent("TridimensionalObjectRC"))
        ->getSceneNode()
        ->getOrientation();
}

void GunC::onShoot(TransformComponent* transform, RigidbodyPC* rigidBody) {
    if (_soundComponent == nullptr)
        _soundComponent =
            dynamic_cast<SoundComponent*>(scene_->getEntityById("GameManager")
                                              ->getComponent("SoundComponent"));
    _soundComponent->playSound(_shotSound);
}

bool GunC::timeCadence() {
    const float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimeCadence_ >= cadence_) {
        lastTimeCadence_ = seconds;
        return true;
    }

    return false;
}

std::string GunC::getBulletType() { return _myBulletType; }

std::string GunC::getBulletTag() { return _myBulletTag; }

std::string GunC::getBulletComponentName() { return bulletComponentName_; }

const std::string& GunC::getShotSound() const { return _shotSound; }

int GunC::getbulletchamber() { return _bulletchamber; }

int GunC::getmunition() { return _munition; }

int GunC::getbulletdamage() { return _bulletDamage; }

int GunC::getbulletspeed() { return _bulletSpeed; }

float GunC::getcadence() { return cadence_; }

bool GunC::getautomatic() { return _automatic; }

void GunC::setBulletType(std::string bulletType) { _myBulletType = bulletType; }

void GunC::setBulletTag(std::string bulletTag) { _myBulletTag = bulletTag; }

void GunC::setBulletComponentName(std::string name) {
    bulletComponentName_ = name;
}

void GunC::setShotSound(std::string shotSound) { _shotSound = shotSound; }

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

void GunC::setcadence(float cadence) { cadence_ = cadence; }

void GunC::setautomatic(bool automatic) { _automatic = automatic; }

void GunC::setInfiniteAmmo(bool infinite) { infiniteAmmo_ = infinite; }

void GunC::setInstakill(bool instakill) { instakill_ = instakill; }

void GunC::setTransform(TransformComponent* trans) { myTransform = trans; }

void GunC::setSoundManager() {
    soundManager = dynamic_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}

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

void GunC::updateAmmoTracker() {
    // For weapons with limited ammo
    if (_munition < 0) {
        reinterpret_cast<GuiLabelComponent*>(
            scene_->getEntityById("GunFrameworkHUD")
                ->getComponent("GuiLabelComponent"))
            ->changeText(std::to_string(_bulletchamber) + " / Unlimited");
       
	// For weapons with unlimited ammo
    } else {
        reinterpret_cast<GuiLabelComponent*>(
            scene_->getEntityById("GunFrameworkHUD")
                ->getComponent("GuiLabelComponent"))
            ->changeText(std::to_string(_bulletchamber) + " / " +
                         std::to_string(_munition));
    }
}
