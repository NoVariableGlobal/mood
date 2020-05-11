#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include <json.h>
#include <time.h>
#include <utility>
#include <value.h>

BulletC::BulletC() {}

BulletC::~BulletC() {}

void BulletC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void BulletC::setDamage(float _d) { damage = _d; }

float BulletC::getDamage() { return damage; }

void BulletC::dealCollision() {
    scene_->deleteEntity(father_);
}

// FACTORY INFRASTRUCTURE
BulletCFactory::BulletCFactory() = default;

Component* BulletCFactory::create(Entity* _father, Json::Value& _data,
                                  Scene* _scene) {

    BulletC* bullet = new BulletC();
    _scene->getComponentsManager()->addDC(bullet);

    bullet->setFather(_father);
    bullet->setScene(_scene);

    return bullet;
};

DEFINE_FACTORY(BulletC);