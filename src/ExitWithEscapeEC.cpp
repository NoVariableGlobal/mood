#include "ExitWithEscapeEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GuiLabelC.h"
#include "Scene.h"

#include <iostream>
#include <json.h>
#include <time.h>

ExitWithEscapeEC::ExitWithEscapeEC() {}

ExitWithEscapeEC::~ExitWithEscapeEC() {}

void ExitWithEscapeEC::setPress(bool press) {
    std::cout << pressing;
    pressing = press;
    if (press)
        startTime = clock() / static_cast<float>(CLOCKS_PER_SEC);
    else
        reinterpret_cast<GuiLabelComponent*>(
            father_->getComponent("GuiLabelComponent"))
            ->setAlpha(0);
}

void ExitWithEscapeEC::setAlpha() {
    label = reinterpret_cast<GuiLabelComponent*>(
        father_->getComponent("GuiLabelComponent"));
    label->setAlpha(0);
}

void ExitWithEscapeEC::checkEvent() {

    if (pressing && !out) {

        float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
        if (seconds - startTime >= timeToExit) {
            scene_->changeScene("mainmenu", true);
            out = true;
        } else
            label->setAlpha((seconds - startTime) / 2);
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

    manager->setActive(true);
    manager->setAlpha();
    return manager;
};

DEFINE_FACTORY(ExitWithEscapeEC);