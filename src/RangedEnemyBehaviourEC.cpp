#include "RangedEnemyBehaviourEC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SpawnerBulletsC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <Entity.h>
#include <json.h>
#include "GunC.h"

RangedEnemyBehaviourEC::RangedEnemyBehaviourEC() : EnemyBehaviourEC() {}

RangedEnemyBehaviourEC::~RangedEnemyBehaviourEC() {}

void RangedEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();
    if (active) {
        // attack every attackCooldown seconds
        if (timeToAttack()) {
            shoot();
        }
    }
}

std::string RangedEnemyBehaviourEC::getWeaponEquipped() {
    return weaponEquipped;
}

void RangedEnemyBehaviourEC::setWeaponEquipped(std::string _weaponEquipped) {
    weaponEquipped = _weaponEquipped;
}

void RangedEnemyBehaviourEC::shoot() {
    gun = dynamic_cast<GunC*>(father->getComponent(weaponEquipped));
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

    return rangedEnemyBehaviour;
};

DEFINE_FACTORY(RangedEnemyBehaviourEC);
