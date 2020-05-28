#include "SpawnerFloorRandomEC.h"
#include "AnimationLC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "OgreVector4.h"
#include "RigidbodyPC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "TransformComponent.h"
#include <json.h>

void SpawnerFloorRandomEC::setFloorDimensions(Ogre::Vector4f floorDimensions) {
    *floorDimensions_ = floorDimensions;
}

SpawnerFloorRandomEC::SpawnerFloorRandomEC() {
    floorDimensions_ = new Ogre::Vector4f();
}

SpawnerFloorRandomEC::~SpawnerFloorRandomEC() { delete floorDimensions_; }

void SpawnerFloorRandomEC::checkEvent() {
    if (firstTime_) {
        firstTime_ = false;
        lastTimeSpawned_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    // Spawnea un prefab en una posicion random del mapa cada cierto tiempo
    if (timeToSpawn()) {
        Entity* newEntity = spawnPrefab();

        TransformComponent* spawnTransform = static_cast<TransformComponent*>(
            newEntity->getComponent("TransformComponent"));
        RigidbodyPC* rigidbody =
            static_cast<RigidbodyPC*>(newEntity->getComponent("RigidbodyPC"));

        float x = floorDimensions_->x + static_cast<float>(rand()) /
                                            static_cast<float>(RAND_MAX) *
                                            floorDimensions_->z;
        float z = floorDimensions_->y + static_cast<float>(rand()) /
                                            static_cast<float>(RAND_MAX) *
                                            floorDimensions_->w;
        spawnTransform->setPosition(Ogre::Vector3(x, 10, z));
        rigidbody->setPosition(Ogre::Vector3(x, 10, z));

        AnimationLC* animations = reinterpret_cast<AnimationLC*>(
            newEntity->getComponent("AnimationLC"));
        animations->startAnimation("Idle");
    }
}

void SpawnerFloorRandomEC::registerInRoundManager() {
    reinterpret_cast<RoundManagerEC*>(
        scene_->getEntityById("GameManager")->getComponent("RoundManagerEC"))
        ->registerOtherSpawner(this);
}
// FACTORY INFRASTRUCTURE
SpawnerFloorRandomECFactory::SpawnerFloorRandomECFactory() = default;

Component* SpawnerFloorRandomECFactory::create(Entity* _father,
                                               Json::Value& _data,
                                               Scene* scene) {
    SpawnerFloorRandomEC* spawnerFloorRandomEC = new SpawnerFloorRandomEC();
    scene->getComponentsManager()->addEC(spawnerFloorRandomEC);

    spawnerFloorRandomEC->setFather(_father);
    spawnerFloorRandomEC->setScene(scene);

    spawnerFloorRandomEC->registerInRoundManager();

    // X and Y are the starting position and Z and W are the maximum that
    // position can be modified
    if (!_data["floorDimensions[x,y,z,w]"].isArray())
        throw std::exception("random[x,y,z,w]: position is not an array");
    spawnerFloorRandomEC->setFloorDimensions(
        Ogre::Vector4f(_data["floorDimensions[x,y,z,w]"][0].asFloat(),
                       _data["floorDimensions[x,y,z,w]"][1].asFloat(),
                       _data["floorDimensions[x,y,z,w]"][2].asFloat(),
                       _data["floorDimensions[x,y,z,w]"][3].asFloat()));

    if (!_data["spawnCooldown"].isDouble())
        throw std::exception("Spawner: spawnCooldown is not a double");
    spawnerFloorRandomEC->setSpawnCooldown(_data["spawnCooldown"].asDouble());

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

    for (int i = 0; i < _data["spawnID"].size(); ++i) {
        if (!spawnerFloorRandomEC->addSpawn(_data["spawnID"][i].asString(),
                                            _data["spawnChances"][i].asDouble(),
                                            tag)) {
            printf(("No se pudo aniadir " + _data["spawnID"][i].asString() +
                    ": Ya se llego al 100% de probabilidad./n")
                       .c_str());
            break;
        }
    }

    spawnerFloorRandomEC->setActive(true);

    return spawnerFloorRandomEC;
};

DEFINE_FACTORY(SpawnerFloorRandomEC);
