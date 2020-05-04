#include "LifeBarC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "Scene.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI\Window.h>
#include <json.h>

LifeBarC::LifeBarC() {}

LifeBarC::~LifeBarC() {}

void LifeBarC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void LifeBarC::setInitSize(float x, float y) {
    x_ = x;
    y_ = y;
}

void LifeBarC::updateLifeBar(float life, float maxLife) {

    CEGUI::UDim newWidth = ((myself->getWidth() * CEGUI::UDim(0, life)) / CEGUI::UDim(0, maxLife)) /myself->getWidth();

    myself->setWidth(newWidth);

    // Cambiar color de la barra dependiendo de la vida que tenga
    //if (life >= maxLife * 0.75)
    //    _image->setColor(30, 235, 30);
    //else if (life >= maxLife * 0.5)
    //    _image->setColor(235, 214, 30);
    //else if (life >= maxLife * 0.25)
    //    _image->setColor(209, 104, 43);
    //else
    //    _image->setColor(209, 43, 43);
}

// FACTORY INFRASTRUCTURE
LifeBarCFactory::LifeBarCFactory(){};
Component* LifeBarCFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* _scene) {
    LifeBarC* lifeBar = new LifeBarC();
    _scene->getComponentsManager()->addDC(lifeBar);

    lifeBar->setFather(_father);
    lifeBar->setScene(_scene);

    if (!_data["image"].isString())
        throw std::exception("GuiImageComponent: image is not a string");
    lifeBar->setImage(_data["image"].asString());

    if (!_data["position"].isArray())
        throw std::exception("GuiImageComponent: position is not an array");
    lifeBar->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                             _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("GuiImageComponent: size is not an array");
    lifeBar->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("GuiImageComponent: name is not a string");
    lifeBar->setName(_data["name"].asString());

    lifeBar->create();
    lifeBar->setInitSize();

    return lifeBar;
};

DEFINE_FACTORY(LifeBarC);
