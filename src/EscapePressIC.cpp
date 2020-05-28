#include "EscapePressIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "ExitWithEscapeEC.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

void EscapePressIC::handleInput(const SDL_Event& event) {

    if (event.type == SDL_KEYDOWN && !pressing_) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            reinterpret_cast<ExitWithEscapeEC*>(
                father_->getComponent("ExitWithEscapeEC"))
                ->setPress(true);
            pressing_ = true;
        }
    } else if (event.type == SDL_KEYUP && !up_) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            reinterpret_cast<ExitWithEscapeEC*>(
                father_->getComponent("ExitWithEscapeEC"))
                ->setPress(false);
            pressing_ = false;
        }
    }
}

// FACTORY INFRASTRUCTURE
EscapePressICFactory::EscapePressICFactory() = default;

Component* EscapePressICFactory::create(Entity* _father, Json::Value& _data,
                                        Scene* scene) {
    EscapePressIC* playerShot = new EscapePressIC();
    scene->getComponentsManager()->addIC(playerShot);

    playerShot->setFather(_father);
    playerShot->setScene(scene);

    return playerShot;
};

DEFINE_FACTORY(EscapePressIC);
