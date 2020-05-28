#pragma once
#include "Component.h"
#include "Factory.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(SpawnerBulletsC)

class Entity;
class SpawnerBulletsC final : public Component {
    int count_ = 0;

  public:
    void destroy() override;
    Entity* getBullet(const std::string& type, const std::string& tag);
};
