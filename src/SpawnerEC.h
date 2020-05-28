#pragma once
#include "EventComponent.h"
#include <string>
#include <vector>

class Entity;

struct Spawn {
    std::string id;
    std::string tag;
    float chance;
    float additiveChance;
};

class SpawnerEC : public EventComponent {
    int count_ = 0;

  protected:
    Spawn mySpawn_ = {"", "", 0.0f, 0.0f};

    std::vector<Spawn> spawns_;
    float spawnCooldown_ = 0;
    float lastTimeSpawned_ = 0;
    bool firstTime_ = true;

  public:
    void setSpawnCooldown(float spawnCooldown);

    /**
     * \brief Adds a prefab's id and its individual chance for spawning. If the
     * total chance after adding this spawn is greater than 100%, the last spawn
     * will only have the minimal chance to reach a total of 100%.
     *
     * \param id The prefab's id.
     * \param chance The individual chance of the spawn, in percentage.
     * \param tag The tag to be set to the spawner.
     * \return Whether or not the spawner could be added.
     */
    bool addSpawn(std::string id, float chance, std::string tag = "Default");

    /**
     * \brief Changes the individual chance of an already added spawn. If the id
     * was not originally in the spawner, it will be added instead. \param id:
     * prefab's Id. \param newChance: new individual chance of the spawn, in
     * percentage.
     */
    void editChance(const std::string& id, float newChance,
                    std::string tag = "Default");

    void checkEvent() override;

    bool timeToSpawn();

    Entity* spawnPrefab();

    Spawn binarySearch(int first, int last, float value);

    virtual void registerInRoundManager() = 0;

    void resetLastTimeSpawned();
};
