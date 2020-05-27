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

void PlayerShotIC::handleInput(const SDL_Event& event) {
    bool automatic = (dynamic_cast<WeaponControllerIC*>(
                          father_->getComponent("WeaponControllerIC")))
                         ->getCurrentGun()
                         ->getautomatic();
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT && !reloading_) {
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
    } else if (automatic && event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            (dynamic_cast<AutomaticEC*>(father_->getComponent("AutomaticEC")))
                ->setShoot(false);
        }
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_r) {
            if (!(dynamic_cast<WeaponControllerIC*>(
                      father_->getComponent("WeaponControllerIC")))
                     ->getCurrentGun()
                     ->fullAmmo()) {
                reloading_ = true;
                (dynamic_cast<ReloadEC*>(father_->getComponent("ReloadEC")))
                    ->starToReload();
            }
        }
    }
}

void PlayerShotIC::setReloading(bool reload) { reloading_ = reload; }

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
