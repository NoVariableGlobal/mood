#include "ExitWithEscapeEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"

#include <iostream>
#include <json.h>
#include <time.h>

ExitWithEscapeEC::ExitWithEscapeEC() {}

ExitWithEscapeEC::~ExitWithEscapeEC() {}

void ExitWithEscapeEC::setPress(bool press) {
    pressing = press;
    if (press)
        startTime = clock() / static_cast<float>(CLOCKS_PER_SEC);
}

void ExitWithEscapeEC::checkEvent() {

    if (pressing) {

        float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
        if (seconds - startTime >= timeToExit) {
            scene_->changeScene("mainmenu", true);
        }
    }
}

// FACTORY INFRASTRUCTURE
ExitWithEscapeECFactory::ExitWithEscapeECFactory() = default;

Component* ExitWithEscapeECFactory::create(Entity* _father, Json::Value& _data,
                                           Scene* scene) {
    ExitWithEscapeEC* manager = new ExitWithEscapeEC();
    scene->getComponentsManager()->addEC(manager);

    manager->setFather(_father);
    manager->setScene(scene);

    manager->setActive(false);

    return manager;
};

DEFINE_FACTORY(ExitWithEscapeEC);