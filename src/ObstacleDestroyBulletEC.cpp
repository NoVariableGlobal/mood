#include "ObstacleDestroyBulletEC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <json.h>

ObstacleDestroyBulletEC::ObstacleDestroyBulletEC() {}

ObstacleDestroyBulletEC::~ObstacleDestroyBulletEC() {}

void ObstacleDestroyBulletEC::checkEvent() {
    RigidbodyPC* rb =
        reinterpret_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));

    // if obstacle collides with bullet
    if (rb->collidesWithTag("Obstacle")) {
        BulletC* bullet =
            reinterpret_cast<BulletC*>(father_->getComponent("BulletC"));

        // destroy bullet
        bullet->dealCollision();
    }
}

// FACTORY INFRASTRUCTURE
ObstacleDestroyBulletECFactory::ObstacleDestroyBulletECFactory() = default;

Component* ObstacleDestroyBulletECFactory::create(Entity* _father,
                                                  Json::Value& _data,
                                                  Scene* scene) {
    ObstacleDestroyBulletEC* obstacleDestroyBullet =
        new ObstacleDestroyBulletEC();
    scene->getComponentsManager()->addEC(obstacleDestroyBullet);

    obstacleDestroyBullet->setFather(_father);
    obstacleDestroyBullet->setScene(scene);

    return obstacleDestroyBullet;
};

DEFINE_FACTORY(ObstacleDestroyBulletEC);
