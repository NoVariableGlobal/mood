#include "WeaponControllerIC.h"
#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "HandGunC.h"
#include "ReloadEC.h"
#include "Scene.h"
#include <SDL.h>
#include <SoundComponent.h>
#include <iostream>
#include <json.h>

WeaponControllerIC::WeaponControllerIC() {}

WeaponControllerIC::~WeaponControllerIC() {}

void WeaponControllerIC::init() {
    currentGun = dynamic_cast<HandGunC*>(father_->getComponent("HandGunC"));
}

void WeaponControllerIC::handleInput(const SDL_Event& _event) {

    if (_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_SPACE) {
        if (secondaryGun != nullptr) {
            if (currentGun->getautomatic()) {
                if (_soundComponent == nullptr)
                    _soundComponent = dynamic_cast<SoundComponent*>(
                        scene_->getEntityById("GameManager")
                            ->getComponent("SoundComponent"));
                _soundComponent->stopSound(currentGun->getShotSound());

                if (_automaticEC == nullptr)
                    _automaticEC = dynamic_cast<AutomaticEC*>(
                        father_->getComponent("AutomaticEC"));
                _automaticEC->setShoot(false);
            }

            GunC* aux = currentGun;
            currentGun = secondaryGun;
            secondaryGun = aux;
            (dynamic_cast<ReloadEC*>(father_->getComponent("ReloadEC")))
                ->gunChanged();
        }
    }
}

GunC* WeaponControllerIC::getCurrentGun() { return currentGun; }

GunC* WeaponControllerIC::getSecondaryGun() { return secondaryGun; }

void WeaponControllerIC::pickUpGun(std::string _gunName) {
    // Deactivate old gun
    if (secondaryGun != nullptr) {
        if (secondaryGun ==
            dynamic_cast<HandGunC*>(father_->getComponent("HandGunC"))) {
            currentGun->setActive(false);

            // Activate ned gun and equip it
            currentGun = dynamic_cast<GunC*>(father_->getComponent(_gunName));
            currentGun->setActive(true);
            currentGun->reset();
        }

        else {
            secondaryGun->setActive(false);
            secondaryGun = currentGun;
            // Activate ned gun and equip it
            currentGun = dynamic_cast<GunC*>(father_->getComponent(_gunName));
            currentGun->setActive(true);

            currentGun->reset();
        }
    } else {
        secondaryGun = currentGun;
        // Activate ned gun and equip it
        currentGun = dynamic_cast<GunC*>(father_->getComponent(_gunName));
        currentGun->setActive(true);

        currentGun->reset();
    }
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
    weaponControllerIC->init();

    return weaponControllerIC;
};

DEFINE_FACTORY(WeaponControllerIC);
