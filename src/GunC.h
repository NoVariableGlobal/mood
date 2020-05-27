#pragma once

#include "Component.h"
#include <string>

class TransformComponent;
class BulletC;
class RigidbodyPC;
class SoundComponent;

namespace Ogre {
    class Quaternion;
}

class GunC : public Component {
  protected:
    /**
     * \brief Ammunition in chamber.
     */
    int bulletChamber_ = 0;

    /**
     * \brief Total ammunition in chamber.
     */
    int bulletChamberMax_ = 0;

    /**
     * \brief Total ammunition stored.
     */
    int munition_ = 0;

    /**
     * \brief Total ammunition stored.
     */
    int munitionMax_ = 0;

    /**
     * \brief Damage of a single bullet.
     */
    int bulletDamage_ = 0;

    /**
     * \brief Speed of a single bullet.
     */
    int bulletSpeed_ = 0;

    /**
     * \brief Gun cadence.
     */
    double cadence_ = 0.0;

    double lastTimeCadence_ = 0.0;
    /**
     * \brief One shot or multiple shot gun.
     */
    bool automatic_ = false;

    /**
     * \brief Whether or not this gun has infinite ammo.
     */
    bool infiniteAmmo_ = false;

    /**
     * \brief Whether or not this gun will instantly kill enemies.
     */
    bool instantKill_ = false;

    /**
     * \brief The component name of the bullet.
     */
    std::string bulletComponentName_ = "";

    /**
     * \brief Tag of my bullets.
     */
    std::string myBulletTag_ = "";

    /**
     * \brief Type of my bullets.
     */
    std::string myBulletType_ = "";

    /**
     * \brief Name of the sound that will play while shooting.
     */
    std::string shotSound_ = "";

    TransformComponent* myTransform_ = nullptr;
    SoundComponent* soundManager_ = nullptr;

    bool timeCadence();
    virtual void onPreShoot();
    virtual void onShoot(TransformComponent* transform, RigidbodyPC* rigidBody);

    Ogre::Quaternion getOrientation() const;

  public:
    void destroy() override;

    /**
     * \brief Tries to reload the gun.
     * \return Whether or not the operation succeeded.
     */
    bool reload();

    /**
     * \brief Tries to fire a shot.
     * \return Whether or not the gun was not empty.
     */
    bool shoot();

    /**
     * \brief Retrieves the remaining ammo.
     * \return Whether or not there is ammunition left in the gun.
     */
    bool getRemainingAmmo();

    /**
     * \brief Checks if the bullet chamber has as many bullets as a full clip.
     * \return Whether or not the bullet chamber is full.
     */
    bool fullAmmo();

    void reset();

    /**
     * \brief Checks if the gun can shoot taking into account its ammo and the
     * player's power-ups.
     * \return Whether or not the gun can shoot.
     */
    bool canShoot();

    // Returns the calculated damage
    int getCalculatedDamage();

    // Updates the weapon GUI
    void updateAmmoTracker();

    // Getters
    std::string getBulletType();          // Return the tag of my bullets
    std::string getBulletTag();           // Return the tag of my bullets
    std::string getBulletComponentName(); // Returns the bullet's component name
    const std::string&
    getShotSound() const;   // Returns the name of the sound to shoot.
    int getbulletchamber(); // Return the remaining ammunition in the chamber
    int getmunition();      // Return the remaining ammo
    int getbulletdamage();  // Returns the damage of a single bullet
    int getbulletspeed();   // Returns the speed of a single bullet
    float getcadence();     // Returns the cadence of a bullet
    bool getautomatic();    // Returns if a weapon is semi-automatic
    bool getInfiniteAmmo(); // Returns if the weapon's ammo is infinite

    // Returns whether or not this gun will insta-kill enemies
    bool getInstakill();

    // Setters
    void setBulletType(std::string _bulletType);
    void setBulletTag(std::string _bulletTag);
    void setBulletComponentName(std::string name);
    void setShotSound(std::string shotSound);
    void setbulletchamber(int bulletchamberMax);
    void setmunition(int munition);
    void setbulletdamage(int damage);
    void setbulletspeed(int speed);
    void setcadence(float cadence);
    void setautomatic(bool semiautomatic);
    void setInfiniteAmmo(bool infinite);
    void setInstakill(bool instakill);

    void setTransform(TransformComponent* trans);

    void setSoundManager();
};