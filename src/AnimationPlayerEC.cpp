#include "AnimationPlayerEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "Scene.h"
#include "RigidbodyPC.h"
#include "OgreRoot.h"
#include <iostream>
#include <json.h>
#include <time.h>

AnimationPlayerEC::AnimationPlayerEC() {}

AnimationPlayerEC::~AnimationPlayerEC() {}

void AnimationPlayerEC::setActive(bool active) {
    idle = false;
    run = false;
    if (active)
        playerAnimations = reinterpret_cast<AnimationLC*>(
            scene->getEntitybyId("Player")->getComponent("AnimationLC"));
}

void AnimationPlayerEC::checkEvent() { 
	RigidbodyPC* body =
        dynamic_cast<RigidbodyPC*>(father->getComponent("RigidbodyPC"));
    if (!idle && body->getLinearVelocity() == Ogre::Vector3(0.0f, 0.0f, 0.0f)) {
            playerAnimations->stopAnimations();
			playerAnimations->startAnimation("Idle");
            idle = true;
            run = false;
    } else if (!run &&
               body->getLinearVelocity() != Ogre::Vector3(0.0f, 0.0f, 0.0f)) {
        playerAnimations->stopAnimations();
        playerAnimations->startAnimation("Run Down");
        idle = false;
        run = true;
    }
}

// FACTORY INFRASTRUCTURE
AnimationPlayerECFactory::AnimationPlayerECFactory() = default;

Component* AnimationPlayerECFactory::create(Entity* _father, Json::Value& _data,
                                 Scene* scene) {
    AnimationPlayerEC* anim = new AnimationPlayerEC();
    scene->getComponentsManager()->addEC(anim);
    anim->setFather(_father);
    anim->setScene(scene);

    anim->setActive(true);

    return anim;
};

DEFINE_FACTORY(AnimationPlayerEC);
