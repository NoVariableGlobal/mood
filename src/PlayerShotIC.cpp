#include "PlayerShotIC.h"
#include "AnimationLC.h"
#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "ReloadEC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::handleInput(const SDL_Event& _event) {
    bool automatic = (dynamic_cast<WeaponControllerIC*>(
                          father_->getComponent("WeaponControllerIC")))
                         ->getCurrentGun()
                         ->getautomatic();
    if (_event.type == SDL_MOUSEBUTTONDOWN) {
        if (_event.button.button == SDL_BUTTON_LEFT && !reloading) {
            // TODO: Tell gun component to fire a shot
            if (!automatic)
                (dynamic_cast<WeaponControllerIC*>(
                     father_->getComponent("WeaponControllerIC")))
                    ->getCurrentGun()
                    ->shoot();
            else
                (dynamic_cast<AutomaticEC*>(
                     father_->getComponent("AutomaticEC")))
                    ->setShoot(true);
        }
    } else if (automatic && _event.type == SDL_MOUSEBUTTONUP) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            (dynamic_cast<AutomaticEC*>(father_->getComponent("AutomaticEC")))
                ->setShoot(false);
        }
    } else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            reloading = true;
            (dynamic_cast<ReloadEC*>(father_->getComponent("ReloadEC")))
                ->starToReload();
        }
    }
}

void PlayerShotIC::setReloading(bool reload) { reloading = reload; }

// FACTORY INFRASTRUCTURE
PlayerShotICFactory::PlayerShotICFactory() = default;

Component* PlayerShotICFactory::create(Entity* _father, Json::Value& _data,
                                       Scene* scene) {
    PlayerShotIC* playerShot = new PlayerShotIC();
    scene->getComponentsManager()->addIC(playerShot);

    playerShot->setFather(_father);
    playerShot->setScene(scene);

    return playerShot;
};

DEFINE_FACTORY(PlayerShotIC);
