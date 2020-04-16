#include "BulletHurtPlayerEC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "OgreRoot.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <json.h>

BulletHurtPlayerEC::BulletHurtPlayerEC() {}

BulletHurtPlayerEC::~BulletHurtPlayerEC() {}

void BulletHurtPlayerEC::checkEvent() {
    RigidbodyPC* rb =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));

    // if player collides with bullet
    if (rb->collidesWith("Player")) {
        // hurt player
        BulletC* bullet =
            dynamic_cast<BulletC*>(father->getComponent("BulletC"));
        int damage = bullet->getDamage();
        LifeC* playerHealth = dynamic_cast<LifeC*>(
            scene->getEntitybyId("Player")->getComponent("LifeC"));

        // if player dies sleep method is called
        if (playerHealth->doDamage(damage))
            ;
        // TODO(MiriamLeis): call `sleep()` when funcionality is available

        // destroy bullet
        bullet->dealCollision();
    }
}

// FACTORY INFRASTRUCTURE
BulletHurtPlayerECFactory::BulletHurtPlayerECFactory() = default;

Component* BulletHurtPlayerECFactory::create(Entity* _father,
                                             Json::Value& _data, Scene* scene) {
    BulletHurtPlayerEC* bulletHurtPlayer = new BulletHurtPlayerEC();
    scene->getComponentsManager()->addEC(bulletHurtPlayer);

    bulletHurtPlayer->setFather(_father);
    bulletHurtPlayer->setScene(scene);

    return bulletHurtPlayer;
};

DEFINE_FACTORY(BulletHurtPlayerEC);
