#pragma once
#include "EventComponent.h"

namespace Ogre {
    typedef float Real;
    template <int dims, typename T> class Vector;
    typedef Vector<3, Real> Vector3;
} // namespace Ogre

class EnemyBehaviourEC : public EventComponent {
  private:
    // speed at which enemy follows the player
    float speed;

    // true if enemy is colliding with player
    bool collisionWithPlayer_ = false;

    // amount of damage the enemy deals to the player
    int attack;

    // enemy deals damage every "attackCooldown" seconds
    float attackCooldown;
    float lastTimeAttacked = 0;

    // direction vector from enemy to player
    Ogre::Vector3* directionToPlayer;

    // distance to player
    Ogre::Vector3* distanceToPlayer;

  public:
    EnemyBehaviourEC();
    ~EnemyBehaviourEC();
    virtual void checkEvent();
    bool timeToAttack();

    // getters and setters
    float getSpeed();
    bool getCollisionWithPlayer();
    int getAttack();
    float getAttackCooldown();
    float getLastTimeAttacked();
    Ogre::Vector3 getDirectionToPlayer();
    Ogre::Vector3 getDistanceToPlayer();

    void setSpeed(float _speed);
    void setCollisionWithPlayer(bool _collisionWithPlayer);
    void setAttack(float _attack);
    void setAttackCooldown(float _attackCooldown);
    void setLastTimeAttacked(float _lastTimeAttacked);
    void setDirectionToPlayer(Ogre::Vector3 _directionToPlayer);
    void setDistanceToPlayer(Ogre::Vector3 _distanceToPlayer);
};
