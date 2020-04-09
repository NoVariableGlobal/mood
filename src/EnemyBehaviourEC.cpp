#include "EnemyBehaviourEC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <json.h>
#include <math.h>
#include <time.h>
#include <utility>
#include <value.h>

EnemyBehaviourEC::EnemyBehaviourEC()
    : speed(0.0f), attack(0), attackCooldown(0.0f), aggroDistance(0.0f),
      withinRange(false) {
    directionToPlayer = new Ogre::Vector3();
    distanceToPlayer = new Ogre::Vector3();
}

EnemyBehaviourEC::~EnemyBehaviourEC() {
    delete directionToPlayer;
    delete distanceToPlayer;
}

void EnemyBehaviourEC::checkEvent() {
    TransformComponent* transform = dynamic_cast<TransformComponent*>(
        father->getComponent("TransformComponent"));
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    // obtain player position
    TransformComponent* playerTransform = dynamic_cast<TransformComponent*>(
        scene->getEntitybyId("Player")->getComponent("TransformComponent"));
    Ogre::Vector3 playerPosition = playerTransform->getPosition();

    *distanceToPlayer =
        Ogre::Vector3(playerPosition.x - transform->getPosition().x,
                      playerPosition.y - transform->getPosition().y,
                      playerPosition.z - transform->getPosition().z);

    *directionToPlayer = distanceToPlayer->normalisedCopy();

    // check collision with player
    collisionWithPlayer_ = rb->collidesWith("Player");

    // check if player is within range
    withinRange = getDistanceToPlayer().squaredLength() <= getAggroDistance();

    // if not colliding with player and not within attack range enemy moves
    // towards player
    Ogre::Vector3 velocity;
    if (!collisionWithPlayer_ && !withinRange) {
        velocity = Ogre::Vector3(directionToPlayer->x * speed, 0.0f,
                                 directionToPlayer->z * speed);

    } else {
        velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);
    }
    rb->setLinearVelocity(velocity);

    // set orientation towards player
    float angleInRad =
        atan2(transform->getPosition().z - playerTransform->getPosition().z,
              transform->getPosition().x - playerTransform->getPosition().x);
    float angleInDeg = -angleInRad * 180 / M_PI;
    // Make the rotation
    TridimensionalObjectRC* fatherRender =
        dynamic_cast<TridimensionalObjectRC*>(
            father->getComponent("TridimensionalObjectRC"));
    fatherRender->rotate(angleInDeg - 90, Ogre::Vector3(0, 1, 0));

    Entity* playerBullet = rb->collidesWithTag("PlayerBullet");
    if (playerBullet != nullptr) {
        LifeC* life = dynamic_cast<LifeC*>(father->getComponent("LifeC"));
        BulletC* bullet =
            dynamic_cast<BulletC*>(playerBullet->findComponent("BulletC"));
        if (bullet == nullptr)
            bullet = dynamic_cast<BulletC*>(
                playerBullet->findComponent("SniperBulletC"));

        life->doDamage(bullet->getDamage());
        bullet->dealCollision();

        if (!active) // if dead
            dynamic_cast<RoundManagerEC*>(scene->getEntitybyId("GameManager")
                                              ->getComponent("RoundManagerEC"))
                ->enemyDied();
    }
}

bool EnemyBehaviourEC::timeToAttack() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimeAttacked >= attackCooldown) {
        lastTimeAttacked = seconds;
        return true;
    }

    return false;
}

bool EnemyBehaviourEC::getCollisionWithPlayer() { return collisionWithPlayer_; }

void EnemyBehaviourEC::setCollisionWithPlayer(bool _collisionWithPlayer) {
    collisionWithPlayer_ = _collisionWithPlayer;
}

float EnemyBehaviourEC::getSpeed() { return speed; }

int EnemyBehaviourEC::getAttack() { return attack; }

float EnemyBehaviourEC::getAttackCooldown() { return attackCooldown; }

float EnemyBehaviourEC::getLastTimeAttacked() { return lastTimeAttacked; }

Ogre::Vector3 EnemyBehaviourEC::getDirectionToPlayer() {
    return *directionToPlayer;
}

Ogre::Vector3 EnemyBehaviourEC::getDistanceToPlayer() {
    return *distanceToPlayer;
}

float EnemyBehaviourEC::getAggroDistance() { return aggroDistance; }

bool EnemyBehaviourEC::getWithinRange() { return withinRange; }

void EnemyBehaviourEC::setSpeed(float _speed) { speed = _speed; }

void EnemyBehaviourEC::setAttack(float _attack) { attack = _attack; }

void EnemyBehaviourEC::setAttackCooldown(float _attackCooldown) {
    attackCooldown = _attackCooldown;
}

void EnemyBehaviourEC::setLastTimeAttacked(float _lastTimeAttacked) {
    lastTimeAttacked = _lastTimeAttacked;
}

void EnemyBehaviourEC::setDirectionToPlayer(Ogre::Vector3 _directionToPlayer) {
    *directionToPlayer = _directionToPlayer;
}

void EnemyBehaviourEC::setDistanceToPlayer(Ogre::Vector3 _distanceToPlayer) {
    *distanceToPlayer = _distanceToPlayer;
}

void EnemyBehaviourEC::setAggroDistance(float _aggroDistance) {
    aggroDistance = _aggroDistance;
}

void EnemyBehaviourEC::setWithinRange(bool _withinRange) {
    withinRange = _withinRange;
}
