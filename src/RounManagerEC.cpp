#include "RoundManagerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"

#include <iostream>
#include <time.h>
#include <value.h>

void RoundManagerEC::checkEvent() { 
    if (enemiesDead == enemiesInRound) //Ronda Terminada
}

void RoundManagerEC::setMinAddEnemies(int n) { minAddEnemies = n; }

void RoundManagerEC::setMaxAddEnemies(int n) { maxAddEnemies = n; }

void RoundManagerEC::setEnemiesInRound(int n) { enemiesInRound = n; }

void RoundManagerEC::registerEnemySpawner(SpawnerEnemiesEC* spawn) {
    enemiesSpawners.push_back(spawn);
}

void RoundManagerEC::registerOtherSpawner(SpawnerEC* spawn) {
    otherSpawners.push_back(spawn);
}

void RoundManagerEC::enemyDied() { enemiesDead++; }

// FACTORY INFRASTRUCTURE
RoundManagerECFactory::RoundManagerECFactory() = default;

Component* RoundManagerECFactory::create(Entity* _father,
                                             Json::Value& _data,
                                             Scene* _scene) {
    RoundManagerEC* roundManagerEC = new RoundManagerEC();

    roundManagerEC->setFather(_father);
    roundManagerEC->setScene(_scene);
    _scene->getComponentsManager()->addEC(roundManagerEC);

    if (!_data["minAddEnemies"].isInt())
        throw std::exception("RoundManagerEC: minAddEnemies is not an Int");
    roundManagerEC->setMinAddEnemies(_data["minAddEnemies"].asInt());

    if (!_data["maxAddEnemies"].isInt())
        throw std::exception("RoundManagerEC: maxAddEnemies is not an Int");
    roundManagerEC->setMaxAddEnemies(_data["maxAddEnemies"].asInt());

    if (!_data["enemiesInRound"].isInt())
        throw std::exception("RoundManagerEC: enemiesInRound is not an Int");
    roundManagerEC->setEnemiesInRound(_data["enemiesInRound"].asInt());


    roundManagerEC->setActive(true);

    return roundManagerEC;
};

DEFINE_FACTORY(RoundManagerEC);