#include "DeadManagerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include "AnimationLC.h"
#include "RankingManagerC.h"
#include "RoundManagerEC.h"

#include <json.h>
#include <time.h>
#include <iostream>

DeadManagerEC::DeadManagerEC() {}

DeadManagerEC::~DeadManagerEC() {}

void DeadManagerEC::setActive(bool _active) {
    active = _active;
    if (active)
        playerAnimations = reinterpret_cast<AnimationLC*>(
            scene->getEntitybyId("Player")->getComponent("AnimationLC"));
}

void DeadManagerEC::checkEvent() { 
    if (playerAnimations->animationFinished("Dance")) {
        reinterpret_cast<RankingManagerC*>(
            father->getComponent("RankingManagerC"))
            ->playerDied();

        RoundManagerEC* roundM = reinterpret_cast<RoundManagerEC*>(
            father->getComponent("RoundManagerEC"));

        roundM->deactivateSpawnerEnemies();
        roundM->deactivateOtherSpawners();

        scene->getEntitybyId("Player")->setActive(false);

        scene->changeScene("DeadMenu");

        active = false;
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