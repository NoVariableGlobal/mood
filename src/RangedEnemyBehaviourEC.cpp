#include "RangedEnemyBehaviourEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SoundComponent.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <Entity.h>
#include <json.h>

RangedEnemyBehaviourEC::RangedEnemyBehaviourEC() : EnemyBehaviourEC() {}

RangedEnemyBehaviourEC::~RangedEnemyBehaviourEC() {}

void RangedEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();

    if (!dead) {
        // attack every attackCooldown seconds
        if (getWithinRange() && timeToAttack()) {
            attacking = true;

            animations->stopAnimations();
            animations->startAnimation("Attack");

            shoot();
        }
    }
}

void RangedEnemyBehaviourEC::rotateToPlayer() {
    // set orientation towards player
    float angleInRad =
        atan2(transform->getPosition().z - playerTransform->getPosition().z,
              transform->getPosition().x - playerTransform->getPosition().x);
    float angleInDeg = -angleInRad * 180 / M_PI;

    // make the rotation
    mesh->setRotation(Ogre::Vector3(0, angleInDeg + 90, 0));
}

std::string RangedEnemyBehaviourEC::getWeaponEquipped() {
    return weaponEquipped;
}

void RangedEnemyBehaviourEC::setWeaponEquipped(std::string _weaponEquipped) {
    weaponEquipped = _weaponEquipped;
}

void RangedEnemyBehaviourEC::shoot() {
    gun = dynamic_cast<GunC*>(father_->getComponent(weaponEquipped));
    if (gun->getautomatic()) {
        if (_soundComponent == nullptr)
            _soundComponent = dynamic_cast<SoundComponent*>(
                scene_->getEntityById("GameManager")
                    ->getComponent("SoundComponent"));
        _soundComponent->playSound(gun->getShotSound());
    }

    gun->shoot();
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
