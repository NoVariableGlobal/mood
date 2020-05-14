#include "EscapePressIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "ExitWithEscapeEC.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

EscapePressIC::EscapePressIC() {}

EscapePressIC::~EscapePressIC() {}

void EscapePressIC::handleInput(const SDL_Event& _event) {

    if (_event.type == SDL_KEYDOWN && !pressing) {
        if (_event.key.keysym.sym == SDLK_ESCAPE) {
            reinterpret_cast<ExitWithEscapeEC*>(
                father_->getComponent("ExitWithEscapeEC"))
                ->setPress(true);
            pressing = true;
        }
    } else if (_event.type == SDL_KEYUP && !up) {
        if (_event.key.keysym.sym == SDLK_ESCAPE) {
            reinterpret_cast<ExitWithEscapeEC*>(
                father_->getComponent("ExitWithEscapeEC"))
                ->setPress(false);
            pressing = false;
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
