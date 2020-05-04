#include "PowerUpIconC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "Scene.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI\Window.h>
#include <json.h>

void PowerUpIconC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void PowerUpIconC::activePowerUpIcon() { myself->setAlpha(1.0); }

void PowerUpIconC::desactivePowerUpIcon() { myself->setAlpha(0.1); }

// FACTORY INFRASTRUCTURE
PowerUpIconCFactory::PowerUpIconCFactory(){};
Component* PowerUpIconCFactory::create(Entity* _father, Json::Value& _data,
                                       Scene* _scene) {
    PowerUpIconC* icon = new PowerUpIconC();
    _scene->getComponentsManager()->addDC(icon);

    icon->setFather(_father);
    icon->setScene(_scene);

    if (!_data["image"].isString())
        throw std::exception("PowerUpIconC: image is not a string");
    icon->setImage(_data["image"].asString());

    if (!_data["position"].isArray())
        throw std::exception("PowerUpIconC: position is not an array");
    icon->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("PowerUpIconC: size is not an array");
    icon->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("PowerUpIconC: name is not a string");
    icon->setName(_data["name"].asString());

    icon->create();

    icon->desactivePowerUpIcon();

    return icon;
};

DEFINE_FACTORY(PowerUpIconC);
