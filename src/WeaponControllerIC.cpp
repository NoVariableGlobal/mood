#include "WeaponControllerIC.h"
#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiImageC.h"
#include "GunModelManagerEC.h"
#include "HandGunC.h"
#include "ReloadEC.h"
#include "Scene.h"
#include <SDL.h>
#include <SoundComponent.h>
#include <iostream>
#include <json.h>

void WeaponControllerIC::init() {
    currentGun_ =
        reinterpret_cast<HandGunC*>(father_->getComponent("HandGunC"));
}

void WeaponControllerIC::handleInput(const SDL_Event& event) {

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        if (secondaryGun_ != nullptr) {

            soundManager_->playSound("SwapGun");
            if (currentGun_->getautomatic()) {

                if (automaticEc_ == nullptr)
                    automaticEc_ = reinterpret_cast<AutomaticEC*>(
                        father_->getComponent("AutomaticEC"));
                automaticEc_->setShoot(false);
            }

            GunC* aux = currentGun_;
            currentGun_ = secondaryGun_;
            secondaryGun_ = aux;

            reinterpret_cast<ReloadEC*>(father_->getComponent("ReloadEC"))
                ->gunChanged();

            currentGun_->updateAmmoTracker();

            std::string image, gunName;
            if (currentGun_->getBulletType() == "HandgunBullet") {
                image = "TaharezLook/HandgunIcon";
                gunName = "HandGunC";
            } else if (currentGun_->getBulletType() == "ShotgunBullet") {
                image = "TaharezLook/ShotgunIcon";
                gunName = "ShotgunC";
            } else if (currentGun_->getBulletType() == "AutomaticRifleBullet") {
                image = "TaharezLook/RifleIcon";
                gunName = "AutomaticRifleC";
            } else if (currentGun_->getBulletType() == "SniperBullet") {
                image = "TaharezLook/SniperIcon";
                gunName = "SniperGunC";
            }

            // Change GUI
            reinterpret_cast<GuiImageComponent*>(
                scene_->getEntityById("GunIconHUD")
                    ->getComponent("GuiImageComponent"))
                ->changeImage(image);

            // Change gun model
            reinterpret_cast<GunModelManagerEC*>(
                father_->getComponent("GunModelManagerEC"))
                ->changeGunModel(gunName);
        }
    }
}

GunC* WeaponControllerIC::getCurrentGun() { return currentGun_; }

GunC* WeaponControllerIC::getSecondaryGun() { return secondaryGun_; }

void WeaponControllerIC::pickUpGun(const std::string& gunName) {
    soundManager_->playSound("SwapGun");
    // Deactivate old gun
    if (secondaryGun_ != nullptr) {
        if (secondaryGun_ ==
            reinterpret_cast<HandGunC*>(father_->getComponent("HandGunC"))) {
            currentGun_->setActive(false);
        } else {
            secondaryGun_->setActive(false);
            secondaryGun_ = currentGun_;
        }

        // Activate ned gun and equip it
        currentGun_ = dynamic_cast<GunC*>(father_->getComponent(gunName));
        currentGun_->setActive(true);
        currentGun_->reset();
    } else {
        secondaryGun_ = currentGun_;
        // Activate ned gun and equip it
        currentGun_ = dynamic_cast<GunC*>(father_->getComponent(gunName));
        currentGun_->setActive(true);

        currentGun_->reset();
    }

    // Change GUI
    currentGun_->updateAmmoTracker();

    // Change gun model
    reinterpret_cast<GunModelManagerEC*>(
        father_->getComponent("GunModelManagerEC"))
        ->changeGunModel(gunName);
}

void WeaponControllerIC::setSoundManager() {
    soundManager_ = reinterpret_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}

// FACTORY INFRASTRUCTURE
WeaponControllerICFactory::WeaponControllerICFactory() = default;

Component* WeaponControllerICFactory::create(Entity* _father,
                                             Json::Value& _data,
                                             Scene* _scene) {
    WeaponControllerIC* weaponControllerIC = new WeaponControllerIC();
    _scene->getComponentsManager()->addIC(weaponControllerIC);

    weaponControllerIC->setFather(_father);
    weaponControllerIC->setScene(_scene);
    weaponControllerIC->setSoundManager();
    weaponControllerIC->init();

    return weaponControllerIC;
};

DEFINE_FACTORY(WeaponControllerIC);
