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

    float newWidth = ((x_ * life) / maxLife);

    myself->setWidth(CEGUI::UDim(0, newWidth));
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
        throw std::exception("LifeBarC: image is not a string");
    lifeBar->setImage(_data["image"].asString());

    if (!_data["position"].isArray())
        throw std::exception("LifeBarC: position is not an array");
    lifeBar->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                   _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("LifeBarC: size is not an array");
    lifeBar->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("LifeBarC: name is not a string");
    lifeBar->setName(_data["name"].asString());

    lifeBar->create();
    lifeBar->setInitSize(lifeBar->getWindow()->getWidth().d_offset,
                         lifeBar->getWindow()->getHeight().d_offset);

    return lifeBar;
};

DEFINE_FACTORY(LifeBarC);
