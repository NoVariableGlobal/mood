#include "LifeC.h"

#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "Scene.h"

#include <json.h>

LifeC::LifeC() : invulnerability(false) {}

LifeC::~LifeC() {}

void LifeC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

float LifeC::getLife() { return currentLife; }

void LifeC::setLife(int _life) { currentLife = _life; }

int LifeC::getTotalLife() { return totalLife; }

void LifeC::setTotalLife(int _life) { totalLife = _life; }

bool LifeC::doDamage(float _damage) {
    if (!invulnerability)
        currentLife -= _damage;

    return currentLife <= 0;
}

void LifeC::heal(float _heal) {
    currentLife += _heal;

    if (currentLife > totalLife)
        currentLife = totalLife;
}

void LifeC::setInvulnerability(bool _invulnerability) {
    invulnerability = _invulnerability;
}

// FACTORY INFRASTRUCTURE
LifeCFactory::LifeCFactory(){};
Component* LifeCFactory::create(Entity* _father, Json::Value& _data,
                                Scene* _scene) {
    LifeC* life = new LifeC();
    _scene->getComponentsManager()->addDC(life);

    life->setFather(_father);
    life->setScene(_scene);

    if (!_data["life"].isInt()) { /*EXCEPCION*/
    }
    life->setTotalLife(_data["life"].asInt());
    life->setLife(_data["life"].asInt());

    return life;
};

DEFINE_FACTORY(LifeC);
