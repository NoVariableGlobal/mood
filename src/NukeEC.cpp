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

    soundManager->playSound("Nuke");

    for (auto it : enemies) {

        Component* comp = it->findComponent("MeleeEnemyBehaviourEC");
        if (comp == nullptr) {
            comp = it->findComponent("TankMeleeEnemyBehaviourEC");

            if (comp == nullptr)
                comp = it->getComponent("RangedEnemyBehaviourEC");
        }
        dynamic_cast<EnemyBehaviourEC*>(comp)->die(false);
    }
}

// FACTORY INFRASTRUCTURE
NukeECFactory::NukeECFactory() = default;

Component* NukeECFactory::create(Entity* _father, Json::Value& _data,
                                 Scene* scene) {
    NukeEC* nukeEC = new NukeEC();
    scene->getComponentsManager()->addEC(nukeEC);
    nukeEC->setFather(_father);
    nukeEC->setScene(scene);

    nukeEC->setSoundManager();

    if (!_data["time"].isDouble())
        throw std::exception("NukeEC: time is not a double");
    nukeEC->setDuration(_data["time"].asDouble());

    nukeEC->setActive(true);

    return nukeEC;
};

DEFINE_FACTORY(NukeEC);
