#include "ExitWithEscapeEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "GuiLabelC.h"
#include "Scene.h"

#include <ctime>
#include <iostream>
#include <json.h>

void ExitWithEscapeEC::setPress(bool press) {
    std::cout << pressing_;
    pressing_ = press;
    if (press)
        startTime_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
    else
        reinterpret_cast<GuiLabelComponent*>(
            father_->getComponent("GuiLabelComponent"))
            ->setAlpha(0);
}

void ExitWithEscapeEC::setAlpha() {
    label_ = reinterpret_cast<GuiLabelComponent*>(
        father_->getComponent("GuiLabelComponent"));
    label_->setAlpha(0);
}

void ExitWithEscapeEC::checkEvent() {

    if (pressing_ && !out_) {

        float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
        if (seconds - startTime_ >= timeToExit_) {
            scene_->changeScene("mainmenu", true);
            out_ = true;
        } else
            label_->setAlpha((seconds - startTime_) / 2);
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