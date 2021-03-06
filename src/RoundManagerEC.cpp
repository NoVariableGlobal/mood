#include "RoundManagerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GameMusicC.h"
#include "GuiLabelC.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include "SoundComponent.h"
#include "SpawnerEnemiesEC.h"
#include "SpawnerFloorRandomEC.h"

#include <ctime>
#include <iostream>
#include <value.h>

void RoundManagerEC::checkEvent() {
    if (enemiesDead_ == enemiesInRound_ && !roundEnd_) // Ronda Terminada
    {
        roundEnd_ = true;

        deactivateSpawnerEnemies();
        deactivateOtherSpawners();

        roundNumber_++;

        timer_ = clock() / static_cast<float>(CLOCKS_PER_SEC);

    } else if (roundEnd_) {
        float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);
        if (seconds - timer_ >= timeBetweenRounds_) {

            if (roundNumber_ % 3 == 0)
                changeMap();

            int randNum =
                rand() % (maxAddEnemies_ - minAddEnemies_ + 1) + minAddEnemies_;
            enemiesInRound_ += randNum;

            int i = 0, size = enemiesSpawners_.size();

            int toAdd;
            if (enemiesInRound_ % 2 == 0)
                toAdd = enemiesInRound_ / size;
            else
                toAdd = (enemiesInRound_ / size) + 1;

            while (i < size - 1) {
                enemiesSpawners_[i]->setActive(true);
                enemiesSpawners_[i]->setEnemies(toAdd);
                i++;
            }
            enemiesSpawners_[i]->setActive(true);
            enemiesSpawners_[i]->setEnemies(enemiesInRound_ - (toAdd * i));

            for (auto it : otherSpawners_)
                it->setActive(true);

            reinterpret_cast<GuiLabelComponent*>(
                scene_->getEntityById("RoundHUD")
                    ->getComponent("GuiLabelComponent"))
                ->changeText("Round " + std::to_string(roundNumber_));

            reinterpret_cast<SoundComponent*>(
                scene_->getEntityById("GameManager")
                    ->getComponent("SoundComponent"))
                ->playSound("NextRound");

            reinterpret_cast<GameMusicC*>(scene_->getEntityById("GameManager")
                                              ->getComponent("GameMusicC"))
                ->setMusic("RoundBackgroundMusic");

            roundEnd_ = false;
            enemiesDead_ = 0;
        }
    }
}

void RoundManagerEC::changeMap() {

    int randNum = (rand() % 4) + 1;

    reinterpret_cast<RigidbodyPC*>(
        scene_->getEntityById("Player")->getComponent("RigidbodyPC"))
        ->setPosition(Ogre::Vector3(0, 10, 0));
    if (lastMap_ == randNum)
        while (randNum == lastMap_)
            randNum = (rand() % 4) + 1;

    if (randNum == 1) {

        for (int i = 0; i < 4; i++) {
            enemiesSpawners_[i]->changePosition(map1Spawners_[i]);
            enemiesSpawners_[i]->resetLastTimeSpawned();
        }
        for (int i = 0; i < 2; i++)
            otherSpawners_[i]->setFloorDimensions(otherSpawnersPos_[0]);

        scene_->changeScene("map1");
    } else if (randNum == 2) {

        for (int i = 0; i < 4; i++) {
            enemiesSpawners_[i]->changePosition(map2Spawners_[i]);
            enemiesSpawners_[i]->resetLastTimeSpawned();
        }
        for (int i = 0; i < 2; i++)
            otherSpawners_[i]->setFloorDimensions(otherSpawnersPos_[1]);

        scene_->changeScene("map2");
    } else if (randNum == 3) {

        for (int i = 0; i < 4; i++) {
            enemiesSpawners_[i]->changePosition(map3Spawners_[i]);
            enemiesSpawners_[i]->resetLastTimeSpawned();
        }
        for (int i = 0; i < 2; i++)
            otherSpawners_[i]->setFloorDimensions(otherSpawnersPos_[2]);

        scene_->changeScene("map3");
    } else if (randNum == 4) {

        for (int i = 0; i < 4; i++) {
            enemiesSpawners_[i]->changePosition(map4Spawners_[i]);
            enemiesSpawners_[i]->resetLastTimeSpawned();
        }
        for (int i = 0; i < 2; i++)
            otherSpawners_[i]->setFloorDimensions(otherSpawnersPos_[3]);

        scene_->changeScene("map4");
    }
    lastMap_ = randNum;
}

void RoundManagerEC::deactivateSpawnerEnemies() {
    for (auto it : enemiesSpawners_)
        it->setActive(false);
}

void RoundManagerEC::deactivateOtherSpawners() {
    for (auto it : otherSpawners_)
        it->setActive(false);
}

void RoundManagerEC::setMinAddEnemies(int n) { minAddEnemies_ = n; }

void RoundManagerEC::setMaxAddEnemies(int n) { maxAddEnemies_ = n; }

void RoundManagerEC::setEnemiesInRound(int n) { enemiesInRound_ = n; }

void RoundManagerEC::setTimeBetweenRounds(int n) { timeBetweenRounds_ = n; }

void RoundManagerEC::registerEnemySpawner(SpawnerEnemiesEC* spawn) {
    enemiesSpawners_.push_back(spawn);
}

void RoundManagerEC::registerOtherSpawner(SpawnerFloorRandomEC* spawn) {
    otherSpawners_.push_back(spawn);
}

int RoundManagerEC::getRoundNumber() { return roundNumber_; }

void RoundManagerEC::enemyDied() { enemiesDead_++; }

void RoundManagerEC::setEnemySpawnersPositions(Ogre::Vector3 pos, int map) {

    if (map == 0)
        map1Spawners_.push_back(pos);
    else if (map == 1)
        map2Spawners_.push_back(pos);
    else if (map == 2)
        map3Spawners_.push_back(pos);
    else
        map4Spawners_.push_back(pos);
}

void RoundManagerEC::setOtherSpawnersPositions(Ogre::Vector4f pos) {
    otherSpawnersPos_.push_back(pos);
}

// FACTORY INFRASTRUCTURE
RoundManagerECFactory::RoundManagerECFactory() = default;

Component* RoundManagerECFactory::create(Entity* _father, Json::Value& _data,
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

    if (!_data["timeBetweenRounds"].isInt())
        throw std::exception("RoundManagerEC: timeBetweenRounds is not an Int");
    roundManagerEC->setTimeBetweenRounds(_data["timeBetweenRounds"].asInt());

    if (!_data["map1Spawners"][0][0].isInt())
        throw std::exception(
            "RoundManagerEC: map1Spawners[0][0] is not an Int");
    if (!_data["map2Spawners"][0][0].isInt())
        throw std::exception(
            "RoundManagerEC: map2Spawners[0][0] is not an Int");
    if (!_data["map3Spawners"][0][0].isInt())
        throw std::exception(
            "RoundManagerEC: map3Spawners[0][0] is not an Int");
    if (!_data["map4Spawners"][0][0].isInt())
        throw std::exception(
            "RoundManagerEC: map4Spawners[0][0] is not an Int");
    // Read enemiesSpawners Positions
    int map = 0;
    std::vector<std::string> names{"map1Spawners", "map2Spawners",
                                   "map3Spawners", "map4Spawners"};
    int it = 0;

    for (int i = 1; i <= 16; i++) {

        Ogre::Vector3 pos;
        pos.x = _data[names[it]][map][0].asInt();
        pos.y = _data[names[it]][map][1].asInt();
        pos.z = _data[names[it]][map][2].asInt();

        roundManagerEC->setEnemySpawnersPositions(pos, it);

        map++;
        if (i % 4 == 0) {
            map = 0;
            it++;
        }
    }

    std::vector<std::string> names2{"map1others", "map2others", "map3others",
                                    "map4others"};

    for (int i = 0; i < 4; i++) {
        Ogre::Vector4f pos;
        pos.x = _data[names2[i]][0].asInt();
        pos.y = _data[names2[i]][1].asInt();
        pos.z = _data[names2[i]][2].asInt();
        pos.w = _data[names2[i]][3].asInt();

        roundManagerEC->setOtherSpawnersPositions(pos);
    }

    roundManagerEC->setActive(true);

    return roundManagerEC;
};

DEFINE_FACTORY(RoundManagerEC);
