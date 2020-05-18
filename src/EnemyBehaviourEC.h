#pragma once
#include "EventComponent.h"
#include <vector>

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class TransformComponent;
class RigidbodyPC;
class LifeC;
class TridimensionalObjectRC;
class AnimationLC;
class SoundComponent;

class EnemyBehaviourEC : public EventComponent {
  private:
    // speed at which enemy follows the player
    float speed;

    // true if enemy is colliding with player
    bool collisionWithPlayer = false;

    // amount of damage the enemy deals to the player
    int attack;

    // enemy deals damage every "attackCooldown" seconds
    float attackCooldown;
    float lastTimeAttacked = 0;

    // direction vector from enemy to player
    Ogre::Vector3* directionToPlayer;

    // distance to player
    Ogre::Vector3* distanceToPlayer;

    // maximum distance to aggro player
    float aggroDistance;

    // player is within aggroDistance
    bool withinRange;

    // other enemies transforms
    std::vector<TransformComponent*> otherTransform;

    // Separation Radius
    int separationRadius = 0;

    // Pointers to components
    RigidbodyPC* rigidbody = nullptr;
    LifeC* life = nullptr;

  protected:
    // true if enemy is colliding with player
    bool attacking = false;
    // true if enemy is colliding with player
    bool dead = false;
    // true if player is dead and enemy is in idle animation
    bool idle = false;

    SoundComponent* soundManager = nullptr;

    // Pointer to animation component
    AnimationLC* animations = nullptr;
    TridimensionalObjectRC* mesh = nullptr;
    TransformComponent* transform = nullptr;
    TransformComponent* playerTransform = nullptr;

  public:
    EnemyBehaviourEC();
    ~EnemyBehaviourEC();
    virtual void destroy();

    void registerComponents();

    void removeTransforms(EnemyBehaviourEC* behaviour);
    void registerInOtherEnemies();
    void addTransforms(EnemyBehaviourEC* behaviour, TransformComponent* other);

    virtual void checkEvent();
    bool timeToAttack();
    virtual void checkDamage();
    virtual void die();
    virtual void moveTowardsPlayer();
    virtual void rotateToPlayer() = 0;
    void setIdle();
    Ogre::Vector3 separate();

    void updatePosibilityToAttackPlayer();

    // getters and setters
    float getSpeed();
    bool getCollisionWithPlayer();
    int getAttack();
    float getAttackCooldown();
    float getLastTimeAttacked();
    Ogre::Vector3 getDirectionToPlayer();
    Ogre::Vector3 getDistanceToPlayer();
    float getAggroDistance();
    bool getWithinRange();

    void setSpeed(float _speed);
    void setCollisionWithPlayer(bool _collisionWithPlayer);
    void setAttack(float _attack);
    void setAttackCooldown(float _attackCooldown);
    void setLastTimeAttacked(float _lastTimeAttacked);
    void setDirectionToPlayer(Ogre::Vector3 _directionToPlayer);
    void setDistanceToPlayer(Ogre::Vector3 _distanceToPlayer);
    void setAggroDistance(float _aggroDistance);
    void setWithinRange(bool _withinRange);
    void setSeparationRadius(int radius);

    void registerInOtherTransforms(TransformComponent* trans);
    void unRegisterInOtherTransforms(TransformComponent* trans);

    void setSoundManager();
};
