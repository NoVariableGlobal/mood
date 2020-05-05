#include "NukeEC.h"
#include "ComponentsManager.h"
#include "EnemyBehaviourEC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SoundComponent.h"
#include <json.h>

void NukeEC::onPick() {
    std::vector<Entity*> enemies = scene_->getEntitiesByTag("Enemy");

    if (_soundComponent == nullptr)
        _soundComponent =
            dynamic_cast<SoundComponent*>(scene_->getEntityById("GameManager")
                                              ->getComponent("SoundComponent"));
    _soundComponent->playSound(_sound);

    for (auto it : enemies) {

        Component* comp = it->findComponent("MeleeEnemyBehaviourEC");
        if (comp == nullptr)
            comp = it->getComponent("RangedEnemyBehaviourEC");
        dynamic_cast<EnemyBehaviourEC*>(comp)->die();
    }

}

void NukeEC::setSound(const std::string& sound) { _sound = sound; }

// FACTORY INFRASTRUCTURE
NukeECFactory::NukeECFactory() = default;

Component* NukeECFactory::create(Entity* _father, Json::Value& _data,
                                 Scene* scene) {
    NukeEC* nukeEC = new NukeEC();
    scene->getComponentsManager()->addEC(nukeEC);
    nukeEC->setFather(_father);
    nukeEC->setScene(scene);

    if (!_data["time"].isDouble())
        throw std::exception("NukeEC: time is not a double");
    nukeEC->setDuration(_data["time"].asDouble());

    
    if (!_data["sound"].isString())
        throw std::exception("NukeEC: sound is not a string");
    nukeEC->setSound(_data["sound"].asString());

    nukeEC->setActive(true);

    return nukeEC;
};

DEFINE_FACTORY(NukeEC);
