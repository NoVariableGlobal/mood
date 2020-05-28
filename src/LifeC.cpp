#include "LifeC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeBarC.h"
#include "Scene.h"

#include <json.h>

void LifeC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

float LifeC::getLife() { return currentLife_; }

void LifeC::setLife(int _life) { currentLife_ = _life; }

int LifeC::getTotalLife() { return totalLife_; }

void LifeC::setTotalLife(int _life) { totalLife_ = _life; }

bool LifeC::doDamage(float _damage) {
    if (!invulnerability_) {
        currentLife_ -= _damage;

        if (father_->getId() == "Player")
            reinterpret_cast<LifeBarC*>(
                scene_->getEntityById("LifeHUD")->getComponent("LifeBarC"))
                ->updateLifeBar(currentLife_, totalLife_);
    }

    return currentLife_ <= 0;
}

void LifeC::heal(float _heal) {
    currentLife_ += _heal;

    if (currentLife_ > totalLife_)
        currentLife_ = totalLife_;

    if (father_->getId() == "Player")
        reinterpret_cast<LifeBarC*>(
            scene_->getEntityById("LifeHUD")->getComponent("LifeBarC"))
            ->updateLifeBar(currentLife_, totalLife_);
}

void LifeC::setInvulnerability(bool _invulnerability) {
    invulnerability_ = _invulnerability;
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
