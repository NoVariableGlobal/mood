#include "RangedEnemyBehaviourEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "SoundComponent.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <Entity.h>
#include <json.h>
#include <utility>

void RangedEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();

    if (!dead_) {
        // attack every attackCooldown seconds
        if (getWithinRange()) {
            if (timeToAttack()) {
                setIdle(false);
                attacking_ = true;

                animations_->stopAnimations();
                animations_->startAnimation("Attack");

                shoot();
            } else if (!idle_ && animations_->animationFinished("Attack")) {
                animations_->stopAnimations();
                setIdle(true);
            }
        } else {
            if (idle_) {
                animations_->stopAnimations();
                animations_->startAnimation("Walk");
                setIdle(false);
            }
            if (attacking_ && animations_->animationFinished("Attack")) {
                attacking_ = false;
                animations_->stopAnimations();
                animations_->startAnimation("Walk");
            }
        }
    }
}

void RangedEnemyBehaviourEC::rotateToPlayer() {
    // set orientation towards player
    float angleInRad =
        atan2(transform_->getPosition().z - playerTransform_->getPosition().z,
              transform_->getPosition().x - playerTransform_->getPosition().x);
    float angleInDeg = -angleInRad * 180 / M_PI;

    // make the rotation
    mesh_->setRotation(Ogre::Vector3(0, angleInDeg + 90, 0));
}

std::string RangedEnemyBehaviourEC::getWeaponEquipped() {
    return weaponEquipped_;
}

void RangedEnemyBehaviourEC::setWeaponEquipped(std::string weaponEquipped) {
    weaponEquipped_ = std::move(weaponEquipped);
}

void RangedEnemyBehaviourEC::shoot() {
    gun_ = dynamic_cast<GunC*>(father_->getComponent(weaponEquipped_));
    if (gun_->getautomatic()) {
        if (soundComponent_ == nullptr)
            soundComponent_ = reinterpret_cast<SoundComponent*>(
                scene_->getEntityById("GameManager")
                    ->getComponent("SoundComponent"));
        soundComponent_->playSound(gun_->getShotSound());
    }

    gun_->shoot();
}

// FACTORY INFRASTRUCTURE
RangedEnemyBehaviourECFactory::RangedEnemyBehaviourECFactory() = default;

Component* RangedEnemyBehaviourECFactory::create(Entity* _father,
                                                 Json::Value& _data,
                                                 Scene* scene) {
    RangedEnemyBehaviourEC* rangedEnemyBehaviour = new RangedEnemyBehaviourEC();
    scene->getComponentsManager()->addEC(rangedEnemyBehaviour);

    rangedEnemyBehaviour->setFather(_father);
    rangedEnemyBehaviour->setScene(scene);

    rangedEnemyBehaviour->registerComponents();

    rangedEnemyBehaviour->registerInOtherEnemies();

    rangedEnemyBehaviour->setSoundManager();

    if (!_data["speed"].isDouble())
        throw std::exception("MeleeEnemyBehaviourEC: speed is not a float");
    rangedEnemyBehaviour->setSpeed(_data["speed"].asFloat());

    if (!_data["attack"].isInt())
        throw std::exception(
            "RangedMeleeEnemyBehaviourPC: attack is not an int");
    rangedEnemyBehaviour->setAttack(_data["attack"].asInt());

    if (!_data["attackCooldown"].isDouble())
        throw std::exception(
            "RangedEnemyBehaviourEC: attackCooldown is not a float");
    rangedEnemyBehaviour->setAttackCooldown(_data["attackCooldown"].asFloat());

    if (!_data["weaponEquipped"].isString())
        throw std::exception(
            "RangedEnemyBehaviourEC: weaponEquipped is not a string");
    rangedEnemyBehaviour->setWeaponEquipped(_data["weaponEquipped"].asString());

    if (!_data["aggroDistance"].isDouble())
        throw std::exception(
            "RangedEnemyBehaviourEC: aggroDistance is not a float");
    rangedEnemyBehaviour->setAggroDistance(_data["aggroDistance"].asFloat());

    if (!_data["separationRadius"].isInt())
        throw std::exception(
            "RangedEnemyBehaviourEC: separationRadius is not a int");
    rangedEnemyBehaviour->setSeparationRadius(
        _data["separationRadius"].asInt());

    return rangedEnemyBehaviour;
};

DEFINE_FACTORY(RangedEnemyBehaviourEC);
