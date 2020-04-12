#include "PlayerShotIC.h"
#include "AutomaticEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "OgreRoot.h"
#include "Scene.h"
#include "WeaponControllerIC.h"
#include <iostream>
#include <json.h>

#include "TridimensionalObjectRC.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderTargetListener.h>
#include <OgreSkeleton.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>
#include <OgreParticleIterator.h>
#include <OgreParticleSystem.h>

PlayerShotIC::PlayerShotIC() {}

PlayerShotIC::~PlayerShotIC() {}

void PlayerShotIC::handleInput(const SDL_Event& _event) {
    bool automatic = (dynamic_cast<WeaponControllerIC*>(
                          father->getComponent("WeaponControllerIC")))
                         ->getCurrentGun()
                         ->getautomatic();
    if (_event.type == SDL_MOUSEBUTTONDOWN) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            // TODO: Tell gun component to fire a shot
            if (!automatic)
                (dynamic_cast<WeaponControllerIC*>(
                     father->getComponent("WeaponControllerIC")))
                    ->getCurrentGun()
                    ->shoot();
            else
                (dynamic_cast<AutomaticEC*>(
                     father->getComponent("AutomaticEC")))
                    ->setShoot(true);
        }
    } else if (automatic && _event.type == SDL_MOUSEBUTTONUP) {
        if (_event.button.button == SDL_BUTTON_LEFT) {
            (dynamic_cast<AutomaticEC*>(father->getComponent("AutomaticEC")))
                ->setShoot(false);
        }
    } else if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_r) {
            (dynamic_cast<WeaponControllerIC*>(
                 father->getComponent("WeaponControllerIC")))
                ->getCurrentGun()
                ->reload();

            for (Entity* e : scene->getEntitiesbyTag("Enemy")) {
            Ogre::AnimationState* anim =
                dynamic_cast<TridimensionalObjectRC*>(
                    e->getComponent("TridimensionalObjectRC"))
                    ->getOgreEntity()
                        ->getAnimationState("Walk");
                anim->setWeight(1);
                anim->setEnabled(true);
            }
        }
    }
}

// FACTORY INFRASTRUCTURE
PlayerShotICFactory::PlayerShotICFactory() = default;

Component* PlayerShotICFactory::create(Entity* _father, Json::Value& _data,
                                       Scene* scene) {
    PlayerShotIC* playerShot = new PlayerShotIC();
    scene->getComponentsManager()->addIC(playerShot);

    playerShot->setFather(_father);
    playerShot->setScene(scene);

    return playerShot;
};

DEFINE_FACTORY(PlayerShotIC);
