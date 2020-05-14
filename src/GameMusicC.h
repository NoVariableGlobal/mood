#pragma once

#include "Component.h"
#include "Factory.h"

#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(GameMusicC);

class GameMusicC : public Component {
  private:
    std::string music = "";

  public:
    GameMusicC() = default;
    ~GameMusicC() = default;

    virtual void destroy();

    void setMusic(std::string music_);
    void stopCurrentMusic(std::string music_);
};
