#include "PlayerMovementIC.h"
#include "AnimationLC.h"
#include "Component.h"
#include "ComponentsManager.h"
#include "FactoriesFactory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <Entity.h>
#include <SDL.h>
#include <iostream>
#include <json.h>

void PlayerMovementIC::handleInput(const SDL_Event& event) {
    RigidbodyPC* body =
        dynamic_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            wDown_ = true;
            break;

        case SDLK_s:
            sDown_ = true;
            break;

        case SDLK_a:
            aDown_ = true;
            break;

        case SDLK_d:
            dDown_ = true;
            break;

        default:
            break;
        }
        if (!hit_) {
            animations_->stopAnimations();
            animations_->startAnimation("Run Down");
            hit_ = true;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            wDown_ = false;
            break;

        case SDLK_s:
            sDown_ = false;
            break;

        case SDLK_a:
            aDown_ = false;
            break;

        case SDLK_d:
            dDown_ = false;
            break;

        default:
            break;
        }
    }

    Ogre::Vector3 velocity = Ogre::Vector3(0.0f, 0.0f, 0.0f);

    if (wDown_)
        velocity += Ogre::Vector3(0.0f, 0.0f, -speed_);
    if (sDown_)
        velocity += Ogre::Vector3(0.0f, 0.0f, speed_);
    if (aDown_)
        velocity += Ogre::Vector3(-speed_, 0.0f, 0.0f);
    if (dDown_)
        velocity += Ogre::Vector3(speed_, 0.0f, 0.0f);

    body->setLinearVelocity(velocity);

    if (hit_ && velocity == Ogre::Vector3(0.0f, 0.0f, 0.0f)) {
        animations_->stopAnimations();
        animations_->startAnimation("Idle");
        hit_ = false;
    }
}

float PlayerMovementIC::getMovementSpeed() { return speed_; }

void PlayerMovementIC::setMovementSpeed(float speed) { speed_ = speed; }

void PlayerMovementIC::setIdleAnimation() {
    animations_ =
        reinterpret_cast<AnimationLC*>(father_->getComponent("AnimationLC"));
    animations_->stopAnimations();
    animations_->startAnimation("Idle");
}

// FACTORY INFRASTRUCTURE
PlayerMovementICFactory::PlayerMovementICFactory() = default;

Component* PlayerMovementICFactory::create(Entity* _father, Json::Value& _data,
                                           Scene* _scene) {
    PlayerMovementIC* playerMovement = new PlayerMovementIC();
    _scene->getComponentsManager()->addIC(playerMovement);

    playerMovement->setFather(_father);
    playerMovement->setScene(_scene);

    if (!_data["speed"].asInt())
        throw std::exception("PlayerMovementIC: speed is not an int");
    playerMovement->setMovementSpeed(_data["speed"].asFloat());
    playerMovement->setIdleAnimation();

    return playerMovement;
};

DEFINE_FACTORY(PlayerMovementIC);
