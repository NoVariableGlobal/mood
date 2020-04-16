#include "MeleeEnemyBehaviourEC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "PlayerMovementIC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <json.h>

#include <iostream>
MeleeEnemyBehaviourEC::MeleeEnemyBehaviourEC() : EnemyBehaviourEC() {}

MeleeEnemyBehaviourEC::~MeleeEnemyBehaviourEC() {}

void MeleeEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();

    // attack every attackCooldown seconds
    if (timeToAttack()) {
        if (active) {
            // if enemy is colliding with player
            if (getCollisionWithPlayer()) {
                // attack player
                LifeC* playerHealth = dynamic_cast<LifeC*>(
                    scene->getEntitybyId("Player")->getComponent("LifeC"));
                // if player dies sleep method is called
                if (playerHealth->doDamage(getAttack()))
                    ;
                // TODO(MiriamLeis): call `sleep()` when funcionality is
                // available
            }
        }
    }
}

// FACTORY INFRASTRUCTURE
MeleeEnemyBehaviourECFactory::MeleeEnemyBehaviourECFactory() = default;

Component* MeleeEnemyBehaviourECFactory::create(Entity* _father,
                                                Json::Value& _data,
                                                Scene* scene) {
    MeleeEnemyBehaviourEC* meleeEnemyBehaviour = new MeleeEnemyBehaviourEC();
    scene->getComponentsManager()->addEC(meleeEnemyBehaviour);

    meleeEnemyBehaviour->setFather(_father);
    meleeEnemyBehaviour->setScene(scene);

    meleeEnemyBehaviour->registerInOtherEnemies();

    if (!_data["speed"].isDouble())
        throw std::exception("MeleeEnemyBehaviourEC: speed is not a float");
    meleeEnemyBehaviour->setSpeed(_data["speed"].asFloat());

    if (!_data["attack"].isInt())
        throw std::exception("MeleeEnemyBehaviourEC: attack is not an int");
    meleeEnemyBehaviour->setAttack(_data["attack"].asInt());

    if (!_data["attackCooldown"].isDouble())
        throw std::exception(
            "MeleeEnemyBehaviourEC: attackCooldown is not a float");
    meleeEnemyBehaviour->setAttackCooldown(_data["attackCooldown"].asFloat());

    if (!_data["separationRadius"].isInt())
        throw std::exception(
            "MeleeEnemyBehaviourEC: separationRadius is not a int");
    meleeEnemyBehaviour->setSeparationRadius(_data["separationRadius"].asInt());

    return meleeEnemyBehaviour;
};

DEFINE_FACTORY(MeleeEnemyBehaviourEC);
