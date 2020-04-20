#include "ObstacleDestroyBulletEC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <json.h>

ObstacleDestroyBulletEC::ObstacleDestroyBulletEC() {}

ObstacleDestroyBulletEC::~ObstacleDestroyBulletEC() {}

void ObstacleDestroyBulletEC::checkEvent() {
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    // if obstacle collides with bullet
    if (rb->collidesWithTag("Obstacle")) {
        BulletC* bullet =
            dynamic_cast<BulletC*>(father->getComponent("BulletC"));

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