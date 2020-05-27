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

#include <utility>

void GunC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

bool GunC::reload() {
    // For weapons with limited ammo
    if (bulletChamber_ < bulletChamberMax_ && munition_ > 0) {
        int remainder = bulletChamberMax_ - bulletChamber_;

        if (remainder > munition_)
            remainder = munition_;

        bulletChamber_ += remainder;
        munition_ -= remainder;

        updateAmmoTracker();

        return true;
    }

    // For weapons with unlimited ammo
    if (bulletChamber_ < bulletChamberMax_ && munition_ < 0) {
        bulletChamber_ = bulletChamberMax_;
        updateAmmoTracker();

        return true;
    }

    return false;
}

bool GunC::shoot() {
    if (!timeCadence())
        return false;

    if (!canShoot()) {
        soundManager_->playSound("EmptyGun");
        return false;
    }

    if (!getInfiniteAmmo()) {
        bulletChamber_--;

        updateAmmoTracker();
    }

    onPreShoot();
    return true;
}

void GunC::onPreShoot() {
    auto* spawner = reinterpret_cast<SpawnerBulletsC*>(
        scene_->getEntityById("GameManager")->getComponent("SpawnerBulletsC"));

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
}

Ogre::Quaternion GunC::getOrientation() const {
    return reinterpret_cast<TridimensionalObjectRC*>(
               father_->getComponent("TridimensionalObjectRC"))
        ->getSceneNode()
        ->getOrientation();
}

void GunC::onShoot(TransformComponent* transform, RigidbodyPC* rigidBody) {

    soundManager_->playSound(shotSound_);
}

bool GunC::timeCadence() {
    const float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimeCadence_ >= cadence_) {
        lastTimeCadence_ = seconds;
        return true;
    }

    return false;
}

std::string GunC::getBulletType() { return myBulletType_; }

std::string GunC::getBulletTag() { return myBulletTag_; }

std::string GunC::getBulletComponentName() { return bulletComponentName_; }

const std::string& GunC::getShotSound() const { return shotSound_; }

int GunC::getbulletchamber() { return bulletChamber_; }

int GunC::getmunition() { return munition_; }

int GunC::getbulletdamage() { return bulletDamage_; }

int GunC::getbulletspeed() { return bulletSpeed_; }

float GunC::getcadence() { return cadence_; }

bool GunC::getautomatic() { return automatic_; }

void GunC::setBulletType(std::string bulletType) {
    myBulletType_ = std::move(bulletType);
}

void GunC::setBulletTag(std::string bulletTag) {
    myBulletTag_ = std::move(bulletTag);
}

void GunC::setBulletComponentName(std::string name) {
    bulletComponentName_ = std::move(name);
}

void GunC::setShotSound(std::string shotSound) {
    shotSound_ = std::move(shotSound);
}

bool GunC::getInfiniteAmmo() { return infiniteAmmo_; }

bool GunC::getInstakill() { return instantKill_; }

void GunC::setbulletchamber(int bulletchamberMax) {
    bulletChamberMax_ = bulletchamberMax;
    bulletChamber_ = bulletchamberMax;
}

void GunC::setmunition(int munition) {
    munition_ = munition;
    munitionMax_ = munition;
}

void GunC::setbulletdamage(int damage) { bulletDamage_ = damage; }

void GunC::setbulletspeed(int speed) { bulletSpeed_ = speed; }

void GunC::setcadence(float cadence) { cadence_ = cadence; }

void GunC::setautomatic(bool automatic) { automatic_ = automatic; }

void GunC::setInfiniteAmmo(bool infinite) { infiniteAmmo_ = infinite; }

void GunC::setInstakill(bool instakill) { instantKill_ = instakill; }

void GunC::setTransform(TransformComponent* trans) { myTransform_ = trans; }

void GunC::setSoundManager() {
    soundManager_ = dynamic_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}

bool GunC::getRemainingAmmo() {
    if (bulletChamber_ == 0 && munition_ == 0)
        return false;
    else
        return true;
}

bool GunC::fullAmmo() { return bulletChamber_ == bulletChamberMax_; }
void GunC::reset() {
    bulletChamber_ = bulletChamberMax_;
    munition_ = munitionMax_;
}
bool GunC::canShoot() { return infiniteAmmo_ || bulletChamber_ != 0; }

int GunC::getCalculatedDamage() {
    return instantKill_ ? std::numeric_limits<int>::max() : bulletDamage_;
}

void GunC::updateAmmoTracker() {
    // For weapons with limited ammo
    if (munition_ < 0) {
        reinterpret_cast<GuiLabelComponent*>(
            scene_->getEntityById("GunFrameworkHUD")
                ->getComponent("GuiLabelComponent"))
            ->changeText(std::to_string(bulletChamber_) + " / Unlimited");

        // For weapons with unlimited ammo
    } else {
        reinterpret_cast<GuiLabelComponent*>(
            scene_->getEntityById("GunFrameworkHUD")
                ->getComponent("GuiLabelComponent"))
            ->changeText(std::to_string(bulletChamber_) + " / " +
                         std::to_string(munition_));
    }
}
