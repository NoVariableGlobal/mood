#include "TankMeleeEnemyBehaviourEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "DeadManagerEC.h"
#include "EnemyBehaviourEC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "OrientateToMouseIC.h"
#include "PlayerMovementIC.h"
#include "PlayerShotIC.h"
#include "RankingManagerC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SoundComponent.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <json.h>

TankMeleeEnemyBehaviourEC::TankMeleeEnemyBehaviourEC() : EnemyBehaviourEC() {}

TankMeleeEnemyBehaviourEC::~TankMeleeEnemyBehaviourEC() {}

void TankMeleeEnemyBehaviourEC::checkEvent() {
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
                scene_->getEntityById("Player")->getComponent("LifeC"));

            // if player dies sleep method is called
            if (playerHealth->doDamage(getAttack())) {
                Entity* player = scene_->getEntityById("Player");

                AnimationLC* animations = reinterpret_cast<AnimationLC*>(
                    player->getComponent(
                        "AnimationLC"));

                animations->stopAnimations();
                animations->startAnimation("Dead");

                reinterpret_cast<RigidbodyPC*>(
                    player->getComponent("RigidbodyPC"))
                    ->setActive(false);
                reinterpret_cast<PlayerShotIC*>(
                    player->getComponent("PlayerShotIC"))
                    ->setActive(false);
                reinterpret_cast<PlayerMovementIC*>(
                    player->getComponent("PlayerMovementIC"))
                    ->setActive(false);
                reinterpret_cast<OrientateToMouseIC*>(
                    player->getComponent("OrientateToMouseIC"))
                    ->setActive(false);

                reinterpret_cast<DeadManagerEC*>(
                    scene_->getEntityById("GameManager")
                        ->getComponent("DeadManagerEC"))
                    ->setActive(true);
            }
        }
    }
}

void TankMeleeEnemyBehaviourEC::rotateToPlayer() {
    // set orientation towards player
    float angleInRad =
        atan2(transform->getPosition().z - playerTransform->getPosition().z,
              transform->getPosition().x - playerTransform->getPosition().x);
    float angleInDeg = -angleInRad * 180 / M_PI;

    // make the rotation
    mesh->setRotation(Ogre::Vector3(0, angleInDeg, 0));
}

// FACTORY INFRASTRUCTURE
TankMeleeEnemyBehaviourECFactory::TankMeleeEnemyBehaviourECFactory() = default;

Component* TankMeleeEnemyBehaviourECFactory::create(Entity* _father,
                                                Json::Value& _data,
                                                Scene* scene) {
    TankMeleeEnemyBehaviourEC* tank =
        new TankMeleeEnemyBehaviourEC();
    scene->getComponentsManager()->addEC(tank);

    tank->setFather(_father);
    tank->setScene(scene);

    tank->setSoundManager();

    tank->registerComponents();

    tank->registerInOtherEnemies();

    if (!_data["speed"].isDouble())
        throw std::exception("TankMeleeEnemyBehaviourEC: speed is not a float");
    tank->setSpeed(_data["speed"].asFloat());

    if (!_data["attack"].isInt())
        throw std::exception("TankMeleeEnemyBehaviourEC: attack is not an int");
    tank->setAttack(_data["attack"].asInt());

    if (!_data["attackCooldown"].isDouble())
        throw std::exception(
            "TankMeleeEnemyBehaviourEC: attackCooldown is not a float");
    tank->setAttackCooldown(_data["attackCooldown"].asFloat());

    if (!_data["separationRadius"].isInt())
        throw std::exception(
            "TankMeleeEnemyBehaviourEC: separationRadius is not a int");
    tank->setSeparationRadius(_data["separationRadius"].asInt());

    return tank;
};

DEFINE_FACTORY(TankMeleeEnemyBehaviourEC);
