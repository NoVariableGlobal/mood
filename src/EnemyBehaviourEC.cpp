#include "EnemyBehaviourEC.h"
#include "AnimationLC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "LifeC.h"
#include "RigidbodyPC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "SniperBulletC.h"
#include "SoundComponent.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <ctime>
#include <json.h>
#include <value.h>

EnemyBehaviourEC::EnemyBehaviourEC()
    : speed_(0.0f), attack_(0), attackCooldown_(0.0f), aggroDistance_(0.0f),
      withinRange_(false) {
    directionToPlayer_ = new Ogre::Vector3();
    distanceToPlayer_ = new Ogre::Vector3();
}

EnemyBehaviourEC::~EnemyBehaviourEC() {
    delete directionToPlayer_;
    delete distanceToPlayer_;
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
    transform_ = reinterpret_cast<TransformComponent*>(
        father_->getComponent("TransformComponent"));
    playerTransform_ = reinterpret_cast<TransformComponent*>(
        scene_->getEntityById("Player")->getComponent("TransformComponent"));
    rigidBody_ =
        reinterpret_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));
    life_ = reinterpret_cast<LifeC*>(father_->getComponent("LifeC"));
    animations_ =
        reinterpret_cast<AnimationLC*>(father_->getComponent("AnimationLC"));
    mesh_ = reinterpret_cast<TridimensionalObjectRC*>(
        father_->getComponent("TridimensionalObjectRC"));
}

void EnemyBehaviourEC::removeTransforms(EnemyBehaviourEC* behaviour) {

    behaviour->unRegisterInOtherTransforms(transform_);
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
    behaviour->registerInOtherTransforms(transform_);

    otherTransform_.push_back(other);
}

void EnemyBehaviourEC::checkEvent() {
    if (!dead_) {
        rigidBody_->setLinearVelocity(Ogre::Vector3(0, 0, 0));

        updatePossibilityToAttackPlayer();

        if (!attacking_)
            moveTowardsPlayer();
        else if (animations_->animationFinished("Attack") && !idle_) {
            attacking_ = false;
            animations_->startAnimation("Walk");
        }

        checkDamage();

        rotateToPlayer();

        LifeC* playerHealth = reinterpret_cast<LifeC*>(
            (scene_->getEntityById("Player")->getComponent("LifeC")));
        if (playerHealth->getLife() <= 0) {
            rigidBody_->setLinearVelocity(Ogre::Vector3(0, 0, 0));
            if (!idle_)
                setIdle(true);
        }

    } else {
        if (animations_->animationFinished("Dead"))
            scene_->deleteEntity(father_);
    }
}

bool EnemyBehaviourEC::timeToAttack() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimeAttacked_ >= attackCooldown_) {
        lastTimeAttacked_ = seconds;
        return true;
    }

    return false;
}

void EnemyBehaviourEC::checkDamage() {
    Entity* playerBullet = rigidBody_->collidesWithTag("PlayerBullet");
    if (playerBullet != nullptr) {
        BulletC* bullet =
            reinterpret_cast<BulletC*>(playerBullet->findComponent("BulletC"));
        if (bullet == nullptr)
            bullet = reinterpret_cast<SniperBulletC*>(
                playerBullet->findComponent("SniperBulletC"));
        // sonido daño enemigo

        Component* comp = father_->findComponent("MeleeEnemyBehaviourEC");
        if (comp != nullptr)
            soundManager_->playSound("MeleeHit");
        else {
            comp = father_->findComponent("RangedEnemyBehaviourEC");

            if (comp != nullptr)
                soundManager_->playSound("RangedHit");
            else
                soundManager_->playSound("BigMeleeHit");
        }

        // enemy is destroyed if it dies
        if (life_->doDamage(bullet->getDamage()))
            die();

        bullet->dealCollision();
    }
}

void EnemyBehaviourEC::die(bool withSound) {
    if (!dead_) {
        dead_ = true;

        rigidBody_->setLinearVelocity(Ogre::Vector3(0, 0, 0));

        animations_->stopAnimations();
        animations_->startAnimation("Dead");

        rigidBody_->setActive(false);

        dynamic_cast<RoundManagerEC*>(scene_->getEntityById("GameManager")
                                          ->getComponent("RoundManagerEC"))
            ->enemyDied();

        Component* comp = father_->findComponent("MeleeEnemyBehaviourEC");
        if (comp != nullptr && withSound)
            soundManager_->playSound("MeleeDeath");
        else {
            comp = father_->findComponent("RangedEnemyBehaviourEC");

            if (withSound) {
                if (comp != nullptr)
                    soundManager_->playSound("RangedDeath");
                else
                    soundManager_->playSound("BigMeleeDeath");
            }
        }
    }
}

void EnemyBehaviourEC::moveTowardsPlayer() {
    *directionToPlayer_ = distanceToPlayer_->normalisedCopy();

    Ogre::Vector3 velocity;
    if (!collisionWithPlayer_ && !withinRange_) {
        velocity = Ogre::Vector3(directionToPlayer_->x * speed_, 0.0f,
                                 directionToPlayer_->z * speed_);

    } else {
        velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);
    }

    rigidBody_->setLinearVelocity(velocity * 0.2 + separate() * 0.8);
}

void EnemyBehaviourEC::setIdle(bool active) {
    idle_ = active;

    if (active)
        animations_->startAnimation("Idle");
}

Ogre::Vector3 EnemyBehaviourEC::separate() {

    Ogre::Vector3 result = Ogre::Vector3(0, 0, 0);
    int numAgents = otherTransform_.size();
    for (int i = 0; i < numAgents; i++) {
        TransformComponent* objective = otherTransform_[i];

        Ogre::Vector3 myPos = transform_->getPosition();

        Ogre::Vector3 direction = myPos - objective->getPosition();

        float distance = direction.squaredLength();

        if (distance < separationRadius_) {
            if (distance < 0.1f)
                distance = 0.5f;
            float force = 1000 / distance;

            direction = direction.normalisedCopy();
            result += force * direction;
        }
    }

    return result;
}

void EnemyBehaviourEC::updatePossibilityToAttackPlayer() {
    // check collision with player
    collisionWithPlayer_ = rigidBody_->collidesWith("Player");

    // check if player is within range
    Ogre::Vector3 playerPosition = playerTransform_->getPosition();

    *distanceToPlayer_ =
        Ogre::Vector3(playerPosition.x - transform_->getPosition().x,
                      playerPosition.y - transform_->getPosition().y,
                      playerPosition.z - transform_->getPosition().z);

    withinRange_ = (*distanceToPlayer_).squaredLength() <= aggroDistance_;
}

bool EnemyBehaviourEC::getCollisionWithPlayer() { return collisionWithPlayer_; }

void EnemyBehaviourEC::setCollisionWithPlayer(bool collisionWithPlayer) {
    collisionWithPlayer_ = collisionWithPlayer;
}

float EnemyBehaviourEC::getSpeed() { return speed_; }

int EnemyBehaviourEC::getAttack() { return attack_; }

float EnemyBehaviourEC::getAttackCooldown() { return attackCooldown_; }

float EnemyBehaviourEC::getLastTimeAttacked() { return lastTimeAttacked_; }

Ogre::Vector3 EnemyBehaviourEC::getDirectionToPlayer() {
    return *directionToPlayer_;
}

Ogre::Vector3 EnemyBehaviourEC::getDistanceToPlayer() {
    return *distanceToPlayer_;
}

float EnemyBehaviourEC::getAggroDistance() { return aggroDistance_; }

bool EnemyBehaviourEC::getWithinRange() { return withinRange_; }

void EnemyBehaviourEC::setSpeed(float speed) { speed_ = speed; }

void EnemyBehaviourEC::setAttack(float attack) { attack_ = attack; }

void EnemyBehaviourEC::setAttackCooldown(float attackCooldown) {
    attackCooldown_ = attackCooldown;
}

void EnemyBehaviourEC::setLastTimeAttacked(float lastTimeAttacked) {
    lastTimeAttacked_ = lastTimeAttacked;
}

void EnemyBehaviourEC::setDirectionToPlayer(Ogre::Vector3 directionToPlayer) {
    *directionToPlayer_ = directionToPlayer;
}

void EnemyBehaviourEC::setDistanceToPlayer(Ogre::Vector3 distanceToPlayer) {
    *distanceToPlayer_ = distanceToPlayer;
}

void EnemyBehaviourEC::setAggroDistance(float aggroDistance) {
    aggroDistance_ = aggroDistance;
}

void EnemyBehaviourEC::setWithinRange(bool withinRange) {
    withinRange_ = withinRange;
}

void EnemyBehaviourEC::setSeparationRadius(int radius) {
    separationRadius_ = radius;
}

void EnemyBehaviourEC::registerInOtherTransforms(TransformComponent* trans) {
    otherTransform_.push_back(trans);
}

void EnemyBehaviourEC::unRegisterInOtherTransforms(TransformComponent* trans) {
    auto it = otherTransform_.begin();
    bool found = false;
    while (it != otherTransform_.end() && !found) {
        if ((*it) == trans)
            found = true;
        else
            it++;
    }
    if (found)
        otherTransform_.erase(it);
}

void EnemyBehaviourEC::setSoundManager() {
    soundManager_ = reinterpret_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}
