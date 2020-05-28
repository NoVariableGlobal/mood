#include "SpawnerEnemiesEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreVector3.h"
#include "RigidbodyPC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <json.h>

void SpawnerEnemiesEC::checkEvent() {

    if (firstTime_) {
        firstTime_ = false;
        lastTimeSpawned_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    // Spawnea un enemigo cada cierto tiempo en la posicion del spawn
    if (enemies_ > 0 && timeToSpawn()) {
        Entity* newEntity = spawnPrefab();

        TransformComponent* spawnTransform =
            reinterpret_cast<TransformComponent*>(
                newEntity->getComponent("TransformComponent"));

        RigidbodyPC* rigid = reinterpret_cast<RigidbodyPC*>(
            newEntity->getComponent("RigidbodyPC"));

        AnimationLC* animations = reinterpret_cast<AnimationLC*>(
            newEntity->getComponent("AnimationLC"));
        animations->startAnimation("Walk");

        rigid->setPosition(transform_->getPosition());
        spawnTransform->setPosition(transform_->getPosition());
        enemies_--;
    }
}

void SpawnerEnemiesEC::setTransform(TransformComponent* trans) {
    transform_ = trans;
}

void SpawnerEnemiesEC::setEnemies(int _enemies) { enemies_ = _enemies; }

void SpawnerEnemiesEC::registerInRoundManager() {
    reinterpret_cast<RoundManagerEC*>(
        scene_->getEntityById("GameManager")->getComponent("RoundManagerEC"))
        ->registerEnemySpawner(this);
}

void SpawnerEnemiesEC::changePosition(Ogre::Vector3 newPos) {
    transform_->setPosition(newPos);
}

// FACTORY INFRASTRUCTURE
SpawnerEnemiesECFactory::SpawnerEnemiesECFactory() = default;

Component* SpawnerEnemiesECFactory::create(Entity* _father, Json::Value& _data,
                                           Scene* scene) {
    SpawnerEnemiesEC* spawnerEnemies = new SpawnerEnemiesEC();

    spawnerEnemies->setFather(_father);
    spawnerEnemies->setScene(scene);
    spawnerEnemies->registerInRoundManager();

    spawnerEnemies->setTransform(reinterpret_cast<TransformComponent*>(
        _father->getComponent("TransformComponent")));
    scene->getComponentsManager()->addEC(spawnerEnemies);

    if (!_data["spawnCooldown"].isDouble())
        throw std::exception("Spawner: spawnCooldown is not a double");
    spawnerEnemies->setSpawnCooldown(_data["spawnCooldown"].asDouble());

    if (!_data["spawnID"].isArray())
        throw std::exception("Spawner: spawnID is not an array");
    else if (!_data["spawnID"][0].isString())
        throw std::exception("Spawner: spawnID is not an array of strings");

    if (!_data["spawnTag"].isString())
        throw std::exception("Spawner: spawnTag is not a string");
    std::string tag = _data["spawnTag"].asString();

    if (!_data["spawnChances"].isArray())
        throw std::exception("Spawner: spawnChances is not an array");
    else if (!_data["spawnChances"][0].isDouble())
        throw std::exception(
            "Spawner: spawnChances is not an array of doubles");

    if (!_data["EnemiesLimit"].isInt())
        throw std::exception("Spawner: EnemiesLimit is not a int");
    spawnerEnemies->setEnemies(_data["EnemiesLimit"].asInt());

    for (int i = 0; i < _data["spawnID"].size(); ++i) {
        if (!spawnerEnemies->addSpawn(_data["spawnID"][i].asString(),
                                      _data["spawnChances"][i].asDouble(),
                                      tag)) {
            printf(("No se pudo aniadir " + _data["spawnID"][i].asString() +
                    ": Ya se llego al 100% de probabilidad./n")
                       .c_str());
            break;
        }
    }

    spawnerEnemies->setActive(true);

    return spawnerEnemies;
};

DEFINE_FACTORY(SpawnerEnemiesEC);
