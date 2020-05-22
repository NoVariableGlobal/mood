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
    int _bulletchamber = 0;    // Ammunition in chamber
    int _bulletchamberMax = 0; // Total ammunition in chamber
    int _munition = 0;         // Total ammunition stored
    int _munitionMax = 0;      // Total ammunition stored
    int _bulletDamage = 0;     // Damage of a single bullet
    int _bulletSpeed = 0;      // Speed of a single bullet
    double cadence_ = 0.0;     // Gun cadence
    double lastTimeCadence_ = 0.0;
    bool _automatic = false;    // One shot or multiple shot gun
    bool infiniteAmmo_ = false; // Whether or not this gun has infinite ammo
    bool instakill_ = false; // Whether or not this gun will insta-kill enemies
    std::string bulletComponentName_ = ""; // The component name of the bullet
    std::string _myBulletTag = "";         // Tag of my bullets
    std::string _myBulletType = "";        // Type of my bullets
    std::string _shotSound =
        ""; // Name of the sound that will play while shooting
    TransformComponent* myTransform;

    bool timeCadence();
    virtual void onPreShoot();
    virtual void onShoot(TransformComponent* transform, RigidbodyPC* rigidBody);

    Ogre::Quaternion getOrientation() const;

    SoundComponent* soundManager = nullptr;

  public:
    void destroy() override;

    // Tries to reload the gun, returns false if failed
    bool reload();

    // Tries to fire a shot, returns false if gun is empty
    bool shoot();

    // Returns wheter or not there is ammunition left in the gun
    bool mmunitionleft();

    void reset();
    // Returns whether or not the gun can shoot
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