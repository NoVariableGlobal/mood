#include "OnEPressPickUpIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GunC.h"
#include "PowerUpC.h"
#include "RigidbodyPC.h"
#include "Scene.h"

#include <iostream>
#include <json.h>
#include <utility>

void OnEPressPickUpIC::handleInput(const SDL_Event& event) {
    rb_ = dynamic_cast<RigidbodyPC*>(father_->getComponent("RigidbodyPC"));
    if (rb_->collidesWith("Player")) {
        // TODO: Mostrar un icono con la "E" cuando haya interfaz

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e) {
            dynamic_cast<PowerUpC*>(father_->getComponent(objectName_))
                ->onPickUp();
            scene_->deleteEntity(father_);
        }
    }
}

void OnEPressPickUpIC::setObjectName(std::string name) {
    objectName_ = std::move(name);
}

// FACTORY INFRASTRUCTURE
OnEPressPickUpICFactory::OnEPressPickUpICFactory() = default;
Component* OnEPressPickUpICFactory::create(Entity* _father, Json::Value& _data,
                                           Scene* changeScene) {
    // Create the component
    OnEPressPickUpIC* onEPressPickUpIC = new OnEPressPickUpIC();
    onEPressPickUpIC->setScene(changeScene);
    changeScene->getComponentsManager()->addIC(onEPressPickUpIC);

    onEPressPickUpIC->setObjectName(_data["objectName"].asString());

    // Set the component's father as the entity it was instanced for
    onEPressPickUpIC->setFather(_father);

    return onEPressPickUpIC;
};

DEFINE_FACTORY(OnEPressPickUpIC);
