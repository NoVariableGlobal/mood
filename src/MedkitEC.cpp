#include "MedkitEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "LifeC.h"
#include "Scene.h"
#include "SoundComponent.h"
#include <json.h>

void MedkitEC::onPick() {
    Entity* player = scene_->getEntityById("Player");
    auto playerHealth = reinterpret_cast<LifeC*>(player->getComponent("LifeC"));
    playerHealth->heal(playerHealth->getTotalLife());

    soundManager_->playSound("MedKit");
}

// FACTORY INFRASTRUCTURE DEFINE

MedkitECFactory::MedkitECFactory() = default;

Component* MedkitECFactory::create(Entity* _father, Json::Value& _data,
                                   Scene* scene) {
    MedkitEC* medkitEC = new MedkitEC();
    scene->getComponentsManager()->addEC(medkitEC);
    medkitEC->setFather(_father);
    medkitEC->setScene(scene);

    medkitEC->setSoundManager();

    if (!_data["time"].isDouble())
        throw std::exception("Medkit: time is not a double");
    medkitEC->setDuration(_data["time"].asDouble());

    medkitEC->setActive(true);

    return medkitEC;
};

DEFINE_FACTORY(MedkitEC);
