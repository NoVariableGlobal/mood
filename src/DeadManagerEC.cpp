#include "DeadManagerEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "RankingManagerC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "WeaponControllerIC.h"

#include <iostream>
#include <json.h>
#include <time.h>

DeadManagerEC::DeadManagerEC() {}

DeadManagerEC::~DeadManagerEC() {}

void DeadManagerEC::setActive(bool _active) {
    active_ = _active;
    if (active_)
        playerAnimations = reinterpret_cast<AnimationLC*>(
            scene_->getEntityById("Player")->getComponent("AnimationLC"));
}

void DeadManagerEC::checkEvent() {
    if (playerAnimations->animationFinished("Dead")) {
        reinterpret_cast<RankingManagerC*>(
            father_->getComponent("RankingManagerC"))
            ->playerDied();

        RoundManagerEC* roundM = reinterpret_cast<RoundManagerEC*>(
            father_->getComponent("RoundManagerEC"));

        roundM->deactivateSpawnerEnemies();
        roundM->deactivateOtherSpawners();

        scene_->getEntityById("LifeHUD")->setPersistent(false);
        scene_->getEntityById("SpeedHUD")->setPersistent(false);
        scene_->getEntityById("ShieldHUD")->setPersistent(false);
        scene_->getEntityById("AmmoHUD")->setPersistent(false);
        scene_->getEntityById("KillHUD")->setPersistent(false);
        scene_->getEntityById("RoundHUD")->setPersistent(false);
        scene_->getEntityById("GunFrameworkHUD")->setPersistent(false);
        scene_->getEntityById("GunIconHUD")->setPersistent(false);

        scene_->getEntityById("Player")->setActive(false);

        scene_->changeScene("DeadMenu");

        active_ = false;
    }
}

// FACTORY INFRASTRUCTURE
DeadManagerECFactory::DeadManagerECFactory() = default;

Component* DeadManagerECFactory::create(Entity* _father, Json::Value& _data,
                                        Scene* scene) {
    DeadManagerEC* manager = new DeadManagerEC();
    scene->getComponentsManager()->addEC(manager);

    manager->setFather(_father);
    manager->setScene(scene);

    manager->setActive(false);

    return manager;
};

DEFINE_FACTORY(DeadManagerEC);