#include "RoundManagerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SpawnerEnemiesEC.h"

#include <iostream>
#include <time.h>
#include <value.h>

void RoundManagerEC::checkEvent() {
    if (enemiesDead == enemiesInRound && !roundEnd) // Ronda Terminada
    {
        roundEnd = true;

        deactivateSpawnerEnemies();
        deactivateOtherSpawners();

        std::cout << "ROUND OVER"
                  << "\n";

        roundNumber++;
        timer = clock() / static_cast<float>(CLOCKS_PER_SEC);

    } else if (roundEnd) {
        float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
        if (seconds - timer >= timeBetweenRounds) {

            if (roundNumber % 5 == 0)
                changeMap();
            int randNum =
                rand() % (maxAddEnemies - minAddEnemies + 1) + minAddEnemies;
            enemiesInRound += randNum;

            int i = 0, size = enemiesSpawners.size();
            int toAdd = enemiesInRound / size;

            std::cout << "ROUND START"
                      << "\n";
            std::cout << "NUMBER OF ENEMIES " << enemiesInRound << "\n";

            while (i < size - 1) {
                enemiesSpawners[i]->setActive(true);
                enemiesSpawners[i]->setEnemies(toAdd);
                i++;
            }
            enemiesSpawners[i]->setActive(true);
            enemiesSpawners[i]->setEnemies(enemiesInRound - (toAdd * i));

            for (auto it : otherSpawners)
                it->setActive(true);

            roundEnd = false;
            enemiesDead = 0;
        }
    }
}

void RoundManagerEC::changeMap() {
    int randNum = (rand() % 3) + 1;

    if (lastMap == randNum) {
        if (randNum == 4)
            randNum--;
        else
            randNum++;
    }

    if (randNum == 1)
        scene->changeScene("map1");
    else if (randNum == 2)
        scene->changeScene("map2");
    else if (randNum == 3)
        scene->changeScene("map3");
    else if (randNum == 4)
        scene->changeScene("map4");
}

void RoundManagerEC::deactivateSpawnerEnemies() {
    for (auto it : enemiesSpawners)
        it->setActive(false);
}

void RoundManagerEC::deactivateOtherSpawners() {
    for (auto it : otherSpawners)
        it->setActive(false);
}

void RoundManagerEC::setMinAddEnemies(int n) { minAddEnemies = n; }

void RoundManagerEC::setMaxAddEnemies(int n) { maxAddEnemies = n; }

void RoundManagerEC::setEnemiesInRound(int n) { enemiesInRound = n; }

void RoundManagerEC::setTimeBetweenRounds(int n) { timeBetweenRounds = n; }

void RoundManagerEC::registerEnemySpawner(SpawnerEnemiesEC* spawn) {
    enemiesSpawners.push_back(spawn);
}

void RoundManagerEC::registerOtherSpawner(SpawnerEC* spawn) {
    otherSpawners.push_back(spawn);
}

int RoundManagerEC::getRoundNumber() { return roundNumber; }

void RoundManagerEC::enemyDied() {
    enemiesDead++;
    std::cout << "ENEMIES LEFT " << enemiesInRound - enemiesDead << "\n";
}

// FACTORY INFRASTRUCTURE
RoundManagerECFactory::RoundManagerECFactory() = default;

Component* RoundManagerECFactory::create(Entity* _father, Json::Value& _data,
                                         Scene* _scene) {
    RoundManagerEC* roundManagerEC = new RoundManagerEC();

    roundManagerEC->setFather(_father);
    roundManagerEC->setScene(_scene);
    _scene->getComponentsManager()->addEC(roundManagerEC);

    roundManagerEC->changeMap();

    if (!_data["minAddEnemies"].isInt())
        throw std::exception("RoundManagerEC: minAddEnemies is not an Int");
    roundManagerEC->setMinAddEnemies(_data["minAddEnemies"].asInt());

    if (!_data["maxAddEnemies"].isInt())
        throw std::exception("RoundManagerEC: maxAddEnemies is not an Int");
    roundManagerEC->setMaxAddEnemies(_data["maxAddEnemies"].asInt());

    if (!_data["enemiesInRound"].isInt())
        throw std::exception("RoundManagerEC: enemiesInRound is not an Int");
    roundManagerEC->setEnemiesInRound(_data["enemiesInRound"].asInt());

    if (!_data["timeBetweenRounds"].isInt())
        throw std::exception("RoundManagerEC: timeBetweenRounds is not an Int");
    roundManagerEC->setTimeBetweenRounds(_data["timeBetweenRounds"].asInt());

    roundManagerEC->setActive(true);

    return roundManagerEC;
};

DEFINE_FACTORY(RoundManagerEC);