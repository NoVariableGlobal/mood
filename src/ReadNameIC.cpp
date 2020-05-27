#include "ReadNameIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiLabelC.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

void ReadNameIC::handleInput(const SDL_Event& event) {

    if (event.type == SDL_KEYDOWN) {

        if (event.key.keysym.sym == SDLK_BACKSPACE)
            removeLetter();
        else if (event.key.keysym.sym >= SDLK_a &&
                 event.key.keysym.sym <= SDLK_z)
            addLetter(static_cast<char>(event.key.keysym.sym));
    }
}

void ReadNameIC::addLetter(char letter) {
    name_ += letter;

    reinterpret_cast<GuiLabelComponent*>(
        scene_->getEntityById("GUI")->getComponent("GuiLabelComponent"))
        ->changeText(name_);
}

void ReadNameIC::removeLetter() {
    if (name_.size() > 0) {

        name_.pop_back();

        reinterpret_cast<GuiLabelComponent*>(
            scene_->getEntityById("GUI")->getComponent("GuiLabelComponent"))
            ->changeText(name_);
    }
}

std::string ReadNameIC::gatName() { return name_; }

// FACTORY INFRASTRUCTURE
ReadNameICFactory::ReadNameICFactory() = default;

Component* ReadNameICFactory::create(Entity* _father, Json::Value& _data,
                                     Scene* scene) {
    ReadNameIC* readNameIC = new ReadNameIC();
    scene->getComponentsManager()->addIC(readNameIC);

    readNameIC->setFather(_father);
    readNameIC->setScene(scene);

    return readNameIC;
};

DEFINE_FACTORY(ReadNameIC);
