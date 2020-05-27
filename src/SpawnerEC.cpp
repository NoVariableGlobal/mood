#include "SpawnerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include <ctime>
#include <utility>
#include <value.h>

void SpawnerEC::setSpawnCooldown(const float spawnCooldown) {
    spawnCooldown_ = spawnCooldown;
}

bool SpawnerEC::addSpawn(std::string id, float chance, std::string tag) {
    float totalChance = 0;
    if (!spawns_.empty())
        totalChance = spawns_.back().additiveChance;
    if (totalChance > 99.999)
        return false;
    spawns_.push_back(
        {std::move(id), std::move(tag), chance, totalChance + chance});

    if (spawns_.back().additiveChance > 99.999)
        spawns_.back().additiveChance = 100;

    return true;
}

void SpawnerEC::editChance(const std::string& id, float newChance,
                           std::string tag) {
    size_t i = 0;
    bool found = false;
    float totalChance;
    for (; i < spawns_.size(); ++i) {
        if (!found)
            found = (id == spawns_[i].id);
        else {
            spawns_[i - 1].id.swap(spawns_[i].id);
            std::swap(spawns_[i - 1], spawns_[i]);
            totalChance = spawns_[i - 1].additiveChance -= spawns_[i].chance;
        }
    }

    if (!found) {
        addSpawn(id, newChance, std::move(tag));
        return;
    }

    spawns_.back().chance = newChance;

    spawns_.back().additiveChance = totalChance + newChance;

    if (spawns_.back().additiveChance > 99.999)
        spawns_.back().additiveChance = 100;
}

void SpawnerEC::checkEvent() {
    if (firstTime_) {
        firstTime_ = false;
        lastTimeSpawned_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    if (timeToSpawn()) {
        spawnPrefab();
    }
}

bool SpawnerEC::timeToSpawn() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - lastTimeSpawned_ >= spawnCooldown_) {
        lastTimeSpawned_ = seconds;
        return true;
    }

    return false;
}

Entity* SpawnerEC::spawnPrefab() {
    Spawn toInstantiate;

    while (toInstantiate.id == "") {
        float random =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        toInstantiate = binarySearch(0, spawns_.size() - 1, random);
    }
    return scene_->getInstanceOf(toInstantiate.id,
                                 toInstantiate.id + std::to_string(count_++) +
                                     father_->getId(),
                                 toInstantiate.tag);
}

Spawn SpawnerEC::binarySearch(int first, int last, float value) {
    if (last >= first) {
        int center = first + (last - first) / 2;

        if (spawns_[center].additiveChance >= value &&
            (center == 0 || spawns_[center - 1].additiveChance < value))
            return spawns_[center];

        if (spawns_[center].additiveChance < value)
            return binarySearch(center + 1, last, value);

        return binarySearch(first, center - 1, value);
    }

    return {"", 0, 0};
}

void SpawnerEC::resetLastTimeSpawned() {
    lastTimeSpawned_ = clock() / static_cast<float>(CLOCKS_PER_SEC);
}
