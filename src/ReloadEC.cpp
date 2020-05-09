#include "ReloadEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "PlayerShotIC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include "SoundComponent.h"
#include <json.h>

void ReloadEC::checkEvent() {
    if (reloading) {

        float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
        if (seconds - timer >= timeToReload) {

            (dynamic_cast<WeaponControllerIC*>(
                 father_->getComponent("WeaponControllerIC")))
                ->getCurrentGun()
                ->reload();

            (dynamic_cast<PlayerShotIC*>(father_->getComponent("PlayerShotIC")))
                ->setReloading(false);

            reloading = false;
        }
    }
}

void ReloadEC::starToReload() {
    if (!reloading) {

        timer = clock() / static_cast<float>(CLOCKS_PER_SEC);
        reloading = true;
        soundManager->playSound("Reload");
    }
}

void ReloadEC::setTime(float time) { timeToReload = time; }

void ReloadEC::gunChanged() { reloading = false; }

void ReloadEC::setSoundManager() {
    soundManager = dynamic_cast<SoundComponent*>(
        scene_->getEntityById("GameManager")->getComponent("SoundComponent"));
}

// FACTORY INFRASTRUCTURE
ReloadECFactory::ReloadECFactory() = default;

Component* ReloadECFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* scene) {
    ReloadEC* reloadEC = new ReloadEC();
    scene->getComponentsManager()->addEC(reloadEC);
    reloadEC->setFather(_father);
    reloadEC->setScene(scene);
    reloadEC->setSoundManager();
    if (!_data["timeToReload"].isDouble())
        throw std::exception("ReloadEC: timeToReload is not a double");
    reloadEC->setTime(_data["timeToReload"].asDouble());

    reloadEC->setActive(true);

    return reloadEC;
};

DEFINE_FACTORY(ReloadEC);
