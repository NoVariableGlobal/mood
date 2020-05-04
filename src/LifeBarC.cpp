#include "LifeBarC.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "Scene.h"

#include <json.h>

LifeBarC::LifeBarC() : invulnerability(false) {}

LifeBarC::~LifeBarC() {}

void LifeBarC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void LifeBarC::updateLifeBar(int life, int maxLife) {

    float newWidthRatio = ((float(myself->getW()) * life) / float(maxLife)) /
                          float(myself->getW());
    setClippingAreaSize(newWidthRatio, 1);
    setSize(_clipArea.w, _clipArea.h);

    // Cambiar color de la barra dependiendo de la vida que tenga
    if (life >= maxLife * 0.75)
        _image->setColor(30, 235, 30);
    else if (life >= maxLife * 0.5)
        _image->setColor(235, 214, 30);
    else if (life >= maxLife * 0.25)
        _image->setColor(209, 104, 43);
    else
        _image->setColor(209, 43, 43);
}

// FACTORY INFRASTRUCTURE
LifeBarCFactory::LifeBarCFactory(){};
Component* LifeBarCFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* _scene) {
    LifeBarC* life = new LifeBarC();
    _scene->getComponentsManager()->addDC(life);

    life->setFather(_father);
    life->setScene(_scene);

    return life;
};

DEFINE_FACTORY(LifeBarC);
