#include "SpawnerBulletsC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include <json.h>

void SpawnerBulletsC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

Entity* SpawnerBulletsC::getBullet(const std::string& type,
                                   const std::string& tag) {
    return scene_->getInstanceOf(type, type + std::to_string(count_++), tag);
}

// FACTORY INFRASTRUCTURE
SpawnerBulletsCFactory::SpawnerBulletsCFactory(){};
Component* SpawnerBulletsCFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {
    SpawnerBulletsC* spawner = new SpawnerBulletsC();
    _scene->getComponentsManager()->addDC(spawner);

    spawner->setFather(_father);
    spawner->setScene(_scene);

    return spawner;
};

DEFINE_FACTORY(SpawnerBulletsC);
