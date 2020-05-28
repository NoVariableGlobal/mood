#pragma once

#include "Component.h"
#include "Factory.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GameMusicC)

class GameMusicC final : public Component {
    std::string music_ = "";

  public:
    void destroy() override;

    void setMusic(const std::string& music);
    void stopCurrentMusic(const std::string& music);
};
