#include "EnemyBehaviourEC.h"
#include "AnimationLC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "LifeC.h"
#include "MeleeEnemyBehaviourEC.h"
#include "OgreRoot.h"
#include "RangedEnemyBehaviourEC.h"
#include "RigidbodyPC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "SoundComponent.h"
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

void EnemyBehaviourEC::destroy() {
    std::vector<Entity*> enemies = scene_->getEntitiesByTag("Enemy");

    for (auto it : enemies) {
        if (it != father_) {

            Component* comp = it->findComponent("MeleeEnemyBehaviourEC");
            if (comp == nullptr) {
                comp = it->findComponent("TankMeleeEnemyBehaviourEC");

                if (comp == nullptr)
                    comp = it->getComponent("RangedEnemyBehaviourEC");
            }

            removeTransforms(dynamic_cast<EnemyBehaviourEC*>(comp));
        }
    }
    EventComponent::destroy();
}

void EnemyBehaviourEC::registerComponents() {
    transform = reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"));
    playerTransform = reinterpret_cast<TransformComponent*>(
        scene_->getEntityById("Player")->getComponent("TransformComponent"));
    rigidbody =
        reinterpret_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));
    life = reinterpret_cast<LifeC*>(father_->getComponent("LifeC"));
    animations =
        reinterpret_cast<AnimationLC*>(father_->getComponent("AnimationLC"));
    mesh = dynamic_cast<TridimensionalObjectRC*>(
        father_->getComponent("TridimensionalObjectRC"));
}

void EnemyBehaviourEC::removeTransforms(EnemyBehaviourEC* behaviour) {

    behaviour->unRegisterInOtherTransforms(transform);
}

void EnemyBehaviourEC::registerInOtherEnemies() {
    std::vector<Entity*> enemies = scene_->getEntitiesByTag("Enemy");

    for (auto it : enemies) {

        Component* comp = it->findComponent("MeleeEnemyBehaviourEC");
        if (comp == nullptr) {
            comp = it->findComponent("TankMeleeEnemyBehaviourEC");

            if (comp == nullptr)
                comp = it->getComponent("RangedEnemyBehaviourEC");
        }

        addTransforms(dynamic_cast<EnemyBehaviourEC*>(comp),
                      reinterpret_cast<TransformComponent*>(
                          it->getComponent("TransformComponent")));
    }
}

void EnemyBehaviourEC::addTransforms(EnemyBehaviourEC* behaviour,
                                     TransformComponent* other) {
    behaviour->registerInOtherTransforms(transform);

    otherTransform.push_back(other);
}

void EnemyBehaviourEC::checkEvent() {
    if (!dead) {
        rigidbody->setLinearVelocity(Ogre::Vector3(0, 0, 0));

        updatePosibilityToAttackPlayer();

        if (!attacking)
            moveTowardsPlayer();
        else if (animations->animationFinished("Attack")) {
            attacking = false;
            animations->startAnimation("Walk");
        }

        checkDamage();

        rotateToPlayer();

    } else {
        if (animations->animationFinished("Dead"))
            scene_->deleteEntity(father_);
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

void EnemyBehaviourEC::checkDamage() {
    Entity* playerBullet = rigidbody->collidesWithTag("PlayerBullet");
    if (playerBullet != nullptr) {
        BulletC* bullet =
            dynamic_cast<BulletC*>(playerBullet->findComponent("BulletC"));
        if (bullet == nullptr)
            bullet = dynamic_cast<BulletC*>(
                playerBullet->findComponent("SniperBulletC"));
        // sonido da�o enemigo

        Component* comp = father_->findComponent("MeleeEnemyBehaviourEC");
        if (comp != nullptr)
            soundManager->playSound("MeleeHit");
        else {
            comp = father_->findComponent("RangedEnemyBehaviourEC");

            if (comp != nullptr)
                soundManager->playSound("RangedHit");
            else
                soundManager->playSound("BigMeleeHit");
        }

        // enemy is destroyed if it dies
        if (life->doDamage(bullet->getDamage()))
            die();

        bullet->dealCollision();
    }
}

void EnemyBehaviourEC::die() {
    if (!dead) {

        dead = true;

        rigidbody->setLinearVelocity(Ogre::Vector3(0, 0, 0));

        animations->stopAnimations();
        animations->startAnimation("Dead");

        rigidbody->setActive(false);

        dynamic_cast<RoundManagerEC*>(scene_->getEntityById("GameManager")
                                          ->getComponent("RoundManagerEC"))
            ->enemyDied();

        Component* comp = father_->findComponent("MeleeEnemyBehaviourEC");
        if (comp != nullptr)
            soundManager->playSound("MeleeDeath");
        else {
            comp = father_->getComponent("RangedEnemyBehaviourEC");

            if (comp != nullptr)
                soundManager->playSound("RangedDeath");
            else
                soundManager->playSound("BigMeleeDeath");
        }
    }
}

void EnemyBehaviourEC::moveTowardsPlayer() {
    *directionToPlayer = distanceToPlayer->normalisedCopy();

    Ogre::Vector3 velocity;
    if (!collisionWithPlayer && !withinRange) {
        velocity = Ogre::Vector3(directionToPlayer->x * speed, 0.0f,
                                 directionToPlayer->z * speed);

    } else {
        velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);
    }

    rigidbody->setLinearVelocity(velocity * 0.2 + separate() * 0.8);
}

Ogre::Vector3 EnemyBehaviourEC::separate() {

    Ogre::Vector3 result = Ogre::Vector3(0, 0, 0);
    int numAgents = otherTransform.size();
    for (int i = 0; i < numAgents; i++) {
        TransformComponent* objective = otherTransform[i];

        Ogre::Vector3 myPos = transform->getPosition();

        Ogre::Vector3 direction = myPos - objective->getPosition();

        float distance = direction.squaredLength();

        if (distance < separationRadius) {
            if (distance < 0.1f)
                distance = 0.5f;
            float force = 1000 / distance;

            direction = direction.normalisedCopy();
            result += force * direction;
        }
    }

    return result;
}

void EnemyBehaviourEC::updatePosibilityToAttackPlayer() {
    // check collision with player
    collisionWithPlayer = rigidbody->collidesWith("Player");

    // check if player is within range
    Ogre::Vector3 playerPosition = playerTransform->getPosition();

    *distanceToPlayer =
        Ogre::Vector3(playerPosition.x - transform->getPosition().x,
                      playerPosition.y - transform->getPosition().y,
                      playerPosition.z - transform->getPosition().z);

    withinRange = (*distanceToPlayer).squaredLength() <= aggroDistance;
}

bool EnemyBehaviourEC::getCollisionWithPlayer() { return collisionWithPlayer; }

void EnemyBehaviourEC::setCollisionWithPlayer(bool _collisionWithPlayer) {
    collisionWithPlayer = _collisionWithPlayer;
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

void EnemyBehaviourEC::setSeparationRadius(int radius) {
    separationRadius = radius;
}

void EnemyBehaviourEC::registerInOtherTransforms(TransformComponent* trans) {
    otherTransform.push_back(trans);
}

void EnemyBehaviourEC::unRegisterInOtherTransforms(TransformComponent* trans) {
    auto it = otherTransform.begin();
    bool found = false;
    while (it != otherTransform.end() && !found) {
        if ((*it) == trans)
            found = true;
        else
            it++;
    }
    if (found)
        otherTransform.erase(it);
}

void EnemyBehaviourEC::setSoundManager() {
    soundManager = dynamic_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}
