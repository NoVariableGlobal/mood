#include "PersistentPowerUpEC.h"

#include "Entity.h"
#include "ParticleC.h"
#include "PowerUpIconC.h"
#include "PowerUpTrackerC.h"
#include "Scene.h"
#include <utility>

void PersistentPowerUpEC::onDestroy() {
    PowerUpEC::onDestroy();

    // If this power-up has been activated, call setEffect with false to remove
    // them, as well as remove the power-up from the PowerUpTrackerC.
    if (activeEffect_) {
        activeEffect_ = false;
        setEffect(false);

        Entity* player = scene_->getEntityById("Player");
        reinterpret_cast<PowerUpTrackerC*>(
            player->getComponent("PowerUpTrackerC"))
            ->removePowerUp(getName());
    }
}

void PersistentPowerUpEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!getPicked() && getCollisionWithPlayer()) {
        setPicked(true);

        Entity* player = scene_->getEntityById("Player");
        auto tracker = reinterpret_cast<PowerUpTrackerC*>(
            player->getComponent("PowerUpTrackerC"));
        auto previous = dynamic_cast<PersistentPowerUpEC*>(
            tracker->findComponent(getName()));

        reinterpret_cast<PowerUpIconC*>(
            scene_->getEntityById(hudName_)->getComponent("PowerUpIconC"))
            ->activePowerUpIcon();

        reinterpret_cast<ParticleC*>(
            scene_->getEntityById(hudName_)->getComponent("ParticleC"))
            ->emitParticles(hudName_ + "Particles");

        // If the player already has this powerup refresh it
        if (previous == nullptr) {
            resetTime();
            setEffect(true);
            activeEffect_ = true;

            father_->getComponent("TridimensionalObjectRC")->setActive(false);
            father_->getComponent("RigidbodyPC")->setActive(false);
            father_->getComponent("TransformComponent")->setActive(false);
            father_->setPersistent(true);
            // Add this powerUp to the tracker
            reinterpret_cast<PowerUpTrackerC*>(
                scene_->getEntityById("Player")->getComponent(
                    "PowerUpTrackerC"))
                ->addPowerUp(getName(), this);
        } else {
            previous->resetTime();
            onDestroy();
        }
    } else if (getPicked() &&
               timeDisappearEffect()) { // delete item and disabled icon if you
                                        // picked the power up and the effect
                                        // has passed
        reinterpret_cast<PowerUpIconC*>(
            scene_->getEntityById(hudName_)->getComponent("PowerUpIconC"))
            ->deactivatePowerUpIcon();

        reinterpret_cast<ParticleC*>(
            scene_->getEntityById(hudName_)->getComponent("ParticleC"))
            ->stopParticles(hudName_ + "Particles");

        onDestroy();

    } else if (timeDisappearEffect()) { // delete item when the effect has
                                        // passed
        onDestroy();
    }
}

void PersistentPowerUpEC::setHeadsUpDisplayName(std::string name) {
    hudName_ = std::move(name);
}
