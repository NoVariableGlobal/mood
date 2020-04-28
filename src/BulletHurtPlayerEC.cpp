#include "BulletHurtPlayerEC.h"
#include "AnimationLC.h"
#include "BulletC.h"
#include "ComponentsManager.h"
#include "DeadManagerEC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SleepEC.h"

#include <json.h>

BulletHurtPlayerEC::BulletHurtPlayerEC() {}

BulletHurtPlayerEC::~BulletHurtPlayerEC() {}

void BulletHurtPlayerEC::checkEvent() {
    RigidbodyPC* rb =
        reinterpret_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));

    // if player collides with bullet
    if (rb->collidesWith("Player")) {
        // hurt player
        BulletC* bullet =
            reinterpret_cast<BulletC*>(father_->getComponent("BulletC"));
        int damage = bullet->getDamage();

        LifeC* playerHealth = reinterpret_cast<LifeC*>(
            scene_->getEntityById("Player")->getComponent("LifeC"));

        // if player dies sleep method is called
        if (playerHealth->doDamage(damage)) {
            AnimationLC* animations = reinterpret_cast<AnimationLC*>(
                scene_->getEntityById("Player")->getComponent("AnimationLC"));

            animations->stopAnimations();
            animations->startAnimation("Dance");

            reinterpret_cast<RigidbodyPC*>(
                scene_->getEntityById("Player")->getComponent("RigidbodyPC"))
                ->setActive(false);

            reinterpret_cast<DeadManagerEC*>(
                scene_->getEntityById("GameManager")
                    ->getComponent("DeadManagerEC"))
                ->setActive(true);
        }

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
