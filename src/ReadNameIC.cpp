#include "ReadNameIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiLabelC.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

ReadNameIC::ReadNameIC() {}

ReadNameIC::~ReadNameIC() {}

void ReadNameIC::handleInput(const SDL_Event& _event) {

    if (_event.type == SDL_KEYDOWN) {

        if (_event.key.keysym.sym == SDLK_BACKSPACE)
            removeLetter();
        else if (_event.key.keysym.sym >= SDLK_a &&
                 _event.key.keysym.sym <= SDLK_z)
            addLetter(static_cast<char>(_event.key.keysym.sym));
    }
}

void ReadNameIC::addLetter(char letter) {
    name += letter;

    reinterpret_cast<GuiLabelComponent*>(
        scene_->getEntityById("GUI")->getComponent("GuiLabelComponent"))
        ->changeText(name);
}

void ReadNameIC::removeLetter() {
    if (name.size() > 0) {

        name.pop_back();

        reinterpret_cast<GuiLabelComponent*>(
            scene_->getEntityById("GUI")->getComponent("GuiLabelComponent"))
            ->changeText(name);
    }
}

std::string ReadNameIC::gatName() { return name; }

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
