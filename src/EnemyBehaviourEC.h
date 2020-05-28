#pragma once
#include "EventComponent.h"
#include <vector>

namespace Ogre {
    typedef float Real;
    template <int Dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class TransformComponent;
class RigidbodyPC;
class LifeC;
class TridimensionalObjectRC;
class AnimationLC;
class SoundComponent;

class EnemyBehaviourEC : public EventComponent {
    // speed at which enemy follows the player
    float speed_;

    // true if enemy is colliding with player
    bool collisionWithPlayer_ = false;

    // amount of damage the enemy deals to the player
    int attack_;

    // enemy deals damage every "attackCooldown" seconds
    float attackCooldown_;
    float lastTimeAttacked_ = 0;

    // direction vector from enemy to player
    Ogre::Vector3* directionToPlayer_;

    // distance to player
    Ogre::Vector3* distanceToPlayer_;

    // maximum distance to aggro player
    float aggroDistance_;

    // player is within aggroDistance
    bool withinRange_;

    // other enemies transforms
    std::vector<TransformComponent*> otherTransform_;

    // Separation Radius
    int separationRadius_ = 0;

    // Pointers to components
    RigidbodyPC* rigidBody_ = nullptr;
    LifeC* life_ = nullptr;

  protected:
    // true if enemy is colliding with player
    bool attacking_ = false;
    // true if enemy is colliding with player
    bool dead_ = false;
    // true if player is dead and enemy is in idle animation
    bool idle_ = false;

    SoundComponent* soundManager_ = nullptr;

    // Pointer to animation component
    AnimationLC* animations_ = nullptr;
    TridimensionalObjectRC* mesh_ = nullptr;
    TransformComponent* transform_ = nullptr;
    TransformComponent* playerTransform_ = nullptr;

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

    // by defect is true and allows to play sounds
    virtual void die(bool withSound = true);
    virtual void moveTowardsPlayer();
    virtual void rotateToPlayer() = 0;
    void setIdle(bool active);
    Ogre::Vector3 separate();

    void updatePossibilityToAttackPlayer();

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

    void setSpeed(float speed);
    void setCollisionWithPlayer(bool collisionWithPlayer);
    void setAttack(float attack);
    void setAttackCooldown(float attackCooldown);
    void setLastTimeAttacked(float lastTimeAttacked);
    void setDirectionToPlayer(Ogre::Vector3 directionToPlayer);
    void setDistanceToPlayer(Ogre::Vector3 distanceToPlayer);
    void setAggroDistance(float aggroDistance);
    void setWithinRange(bool withinRange);
    void setSeparationRadius(int radius);

    void registerInOtherTransforms(TransformComponent* trans);
    void unRegisterInOtherTransforms(TransformComponent* trans);

    void setSoundManager();
};
