#include "PersistentPowerUpEC.h"
#include "Entity.h"
#include "PowerUpTrackerC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"
#include <time.h>

void PersistentPowerUpEC::onDestroy() {
    PowerUpEC::onDestroy();

    // If this power-up has been activated, call setEffect with false to remove
    // them, as well as remove the power-up from the PowerUpTrackerC.
    if (activeEffect_) {
        activeEffect_ = false;
        setEffect(false);

        Entity* player = scene->getEntitybyId("Player");
        reinterpret_cast<PowerUpTrackerC*>(
            player->getComponent("PowerUpTrackerC"))
            ->removePowerUp(getName());
    }
}

void PersistentPowerUpEC::checkEvent() {
    PowerUpEC::checkEvent();

    if (!getPicked() && getCollisionWithPlayer()) {
        setPicked(true);

        Entity* player = scene->getEntitybyId("Player");
        auto tracker = reinterpret_cast<PowerUpTrackerC*>(
            player->getComponent("PowerUpTrackerC"));
        auto previous = dynamic_cast<PersistentPowerUpEC*>(
            tracker->findComponent(getName()));

        // If the player already has this powerup refresh it
        if (previous == nullptr) {
            resetTime();
            setEffect(true);
            activeEffect_ = true;

            father->getComponent("TridimensionalObjectRC")->setActive(false);
            father->getComponent("RigidbodyPC")->setActive(false);
            father->getComponent("TransformComponent")->setActive(false);
            father->setPersistent(true);
            // Add this powerUp to the tracker
            reinterpret_cast<PowerUpTrackerC*>(
                scene->getEntitybyId("Player")->getComponent("PowerUpTrackerC"))
                ->addPowerUp(getName(), this);
        } else {
            previous->resetTime();
            onDestroy();
        }
    } else if (timeDisappearEffect()) { // delete item when the effect has
                                        // passed
        onDestroy();
    }
}
