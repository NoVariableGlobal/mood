#include "MeleeEnemyBehaviourEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "DeadManagerEC.h"
#include "EnemyBehaviourEC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "PlayerMovementIC.h"
#include "RankingManagerC.h"
#include "RigidbodyPC.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include "Scene.h"
#include "OgreRoot.h"

#include <json.h>

MeleeEnemyBehaviourEC::MeleeEnemyBehaviourEC() : EnemyBehaviourEC() {}

MeleeEnemyBehaviourEC::~MeleeEnemyBehaviourEC() {}

void MeleeEnemyBehaviourEC::checkEvent() {
    EnemyBehaviourEC::checkEvent();

    // attack every attackCooldown seconds
    if (!dead) {
        // if enemy is colliding with player
        if (getCollisionWithPlayer() && timeToAttack()) {
            attacking = true;

            animations->stopAnimations();
            animations->startAnimation("Attack");

            // attack player
            LifeC* playerHealth = dynamic_cast<LifeC*>(
                scene->getEntitybyId("Player")->getComponent("LifeC"));

            // if player dies sleep method is called
            if (playerHealth->doDamage(getAttack())) {
                AnimationLC* animations = reinterpret_cast<AnimationLC*>(
                    scene->getEntitybyId("Player")->getComponent(
                        "AnimationLC"));

                animations->stopAnimations();
                animations->startAnimation("Dance");

                reinterpret_cast<RigidbodyPC*>(
                    scene->getEntitybyId("Player")->getComponent("RigidbodyPC"))
                    ->setActive(false);

                reinterpret_cast<DeadManagerEC*>(
                    scene->getEntitybyId("GameManager")
                        ->getComponent("DeadManagerEC"))
                    ->setActive(true);
            }
        }
    }
}

void MeleeEnemyBehaviourEC::rotateToPlayer() {
    // set orientation towards player
    float angleInRad =
        atan2(transform->getPosition().z - playerTransform->getPosition().z,
              transform->getPosition().x - playerTransform->getPosition().x);
    float angleInDeg = -angleInRad * 180 / M_PI;

    // make the rotation
    mesh->setRotation(Ogre::Vector3(0, 0, angleInDeg + 90));
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

    meleeEnemyBehaviour->registerComponents();

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
