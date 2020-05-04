#include "ReadNameIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiLabelC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

ReadNameIC::ReadNameIC() {}

ReadNameIC::~ReadNameIC() {}

void ReadNameIC::handleInput(const SDL_Event& _event) {

    if (_event.type == SDL_KEYDOWN) {

        switch (_event.key.keysym.sym) {

        case SDLK_q:
            addLetter('q');
            break;
        case SDLK_w:
            addLetter('w');
            break;
        case SDLK_e:
            addLetter('e');
            break;
        case SDLK_r:
            addLetter('r');
            break;
        case SDLK_t:
            addLetter('t');
            break;
        case SDLK_y:
            addLetter('y');
            break;
        case SDLK_u:
            addLetter('u');
            break;
        case SDLK_i:
            addLetter('i');
            break;
        case SDLK_o:
            addLetter('o');
            break;
        case SDLK_p:
            addLetter('p');
            break;
        case SDLK_a:
            addLetter('a');
            break;
        case SDLK_s:
            addLetter('s');
            break;
        case SDLK_d:
            addLetter('d');
            break;
        case SDLK_f:
            addLetter('f');
            break;
        case SDLK_g:
            addLetter('g');
            break;
        case SDLK_h:
            addLetter('h');
            break;
        case SDLK_j:
            addLetter('j');
            break;
        case SDLK_k:
            addLetter('k');
            break;
        case SDLK_l:
            addLetter('l');
            break;
        case SDLK_z:
            addLetter('z');
            break;
        case SDLK_x:
            addLetter('x');
            break;
        case SDLK_c:
            addLetter('c');
            break;
        case SDLK_v:
            addLetter('v');
            break;
        case SDLK_b:
            addLetter('b');
            break;
        case SDLK_n:
            addLetter('n');
            break;
        case SDLK_m:
            addLetter('m');
            break;
        case SDLK_BACKSPACE:
            removeLetter();
            break;
        default:
            break;
        }
    }
}

void ReadNameIC::addLetter(char letter) {
    name += letter;

    reinterpret_cast<GuiLabelComponent*>(
        scene_->getEntityById("GUI")->getComponent("GuiLabelComponent"))
        ->changeText(name);
}

void ReadNameIC::removeLetter() {
    name.pop_back();

    reinterpret_cast<GuiLabelComponent*>(
        scene_->getEntityById("GUI")->getComponent("GuiLabelComponent"))
        ->changeText(name);
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
