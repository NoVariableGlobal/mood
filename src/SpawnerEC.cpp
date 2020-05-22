#include "SpawnerEC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include <ctime>
#include <utility>
#include <value.h>

SpawnerEC::SpawnerEC() {}

bool SpawnerEC::addSpawn(std::string id, float chance, std::string tag) {
    float totalChance = 0;
    if (_spawns.size() != 0)
        totalChance = _spawns.back()._additiveChance;
    if (totalChance > 99.999)
        return false;
    _spawns.push_back({id, tag, chance, totalChance + chance});

    if (_spawns.back()._additiveChance > 99.999)
        _spawns.back()._additiveChance = 100;

    return true;
}

void SpawnerEC::editChance(std::string id, float newChance, std::string tag) {
    size_t i = 0;
    bool found = false;
    float totalChance;
    for (; i < _spawns.size(); ++i) {
        if (!found)
            found = (id == _spawns[i]._id);
        else {
            _spawns[i - 1]._id.swap(_spawns[i]._id);
            std::swap(_spawns[i - 1], _spawns[i]);
            totalChance = _spawns[i - 1]._additiveChance -= _spawns[i]._chance;
        }
    }

    if (!found) {
        addSpawn(id, newChance, tag);
        return;
    }

    _spawns.back()._chance = newChance;

    _spawns.back()._additiveChance = totalChance + newChance;

    if (_spawns.back()._additiveChance > 99.999)
        _spawns.back()._additiveChance = 100;
}

void SpawnerEC::checkEvent() {
    if (firstTime) {
        firstTime = false;
        _lastTimeSpawned = clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

    if (timeToSpawn()) {
        spawnPrefab();
    }
}

bool SpawnerEC::timeToSpawn() {
    float seconds = clock() / static_cast<float>(CLOCKS_PER_SEC);

    if (seconds - _lastTimeSpawned >= _spawnCooldown) {
        _lastTimeSpawned = seconds;
        return true;
    }

    return false;
}

Entity* SpawnerEC::spawnPrefab() {
    Spawn toInstantiate;

    while (toInstantiate._id == "") {
        float random =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100;
        toInstantiate = binarySearch(0, _spawns.size() - 1, random);
    }
    return scene_->getInstanceOf(toInstantiate._id,
                                 toInstantiate._id + std::to_string(_count++) +
                                     father_->getId(),
                                 toInstantiate._tag);
}

Spawn SpawnerEC::binarySearch(int first, int last, float value) {
    if (last >= first) {
        int center = first + (last - first) / 2;

        if (_spawns[center]._additiveChance >= value &&
            (center == 0 || _spawns[center - 1]._additiveChance < value))
            return _spawns[center];

        if (_spawns[center]._additiveChance < value)
            return binarySearch(center + 1, last, value);

        return binarySearch(first, center - 1, value);
    }

    return {"", 0, 0};
}

void SpawnerEC::resetLastTimeSpawned() {
    _lastTimeSpawned = clock() / static_cast<float>(CLOCKS_PER_SEC);
}
