#include "GunPowerUpC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiImageC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>

void GunPowerUpC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void GunPowerUpC::onPickUp() {
    dynamic_cast<WeaponControllerIC*>(
        scene_->getEntityById("Player")->getComponent("WeaponControllerIC"))
        ->pickUpGun(gunId_);

    std::string image;
    if (gunId_ == "HandGunC")
        image = "TaharezLook/HandgunIcon";
    else if (gunId_ == "ShotgunC")
        image = "TaharezLook/ShotgunIcon";
    else if (gunId_ == "AutomaticRifleC")
        image = "TaharezLook/RifleIcon";
    else if (gunId_ == "SniperGunC")
        image = "TaharezLook/SniperIcon";

    reinterpret_cast<GuiImageComponent*>(
        scene_->getEntityById("GunIconHUD")->getComponent("GuiImageComponent"))
        ->changeImage(image);
}

void GunPowerUpC::setGunId(const std::string& gunId) { gunId_ = gunId; }

// FACTORY INFRASTRUCTURE
GunPowerUpCFactory::GunPowerUpCFactory() = default;

Component* GunPowerUpCFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* _scene) {

    GunPowerUpC* gunPowerUpC = new GunPowerUpC();

    if (!_data["gunId"].isString())
        throw std::exception("GunPowerUpC: gunId is not a string");
    gunPowerUpC->setGunId(_data["gunId"].asString());

    _scene->getComponentsManager()->addDC(gunPowerUpC);
    gunPowerUpC->setFather(_father);
    gunPowerUpC->setScene(_scene);

    return gunPowerUpC;
};

DEFINE_FACTORY(GunPowerUpC);