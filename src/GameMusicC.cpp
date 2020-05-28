#include "GameMusicC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SoundComponent.h"

#include <json.h>

void GameMusicC::destroy() {
    stopCurrentMusic(music_);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void GameMusicC::setMusic(const std::string& music) {
    if (music != music_) {
        auto* sound = reinterpret_cast<SoundComponent*>(
            father_->getComponent("SoundComponent"));
        sound->stopSound(music_);
        music_ = music;
        sound->playSound(music_);
    }
}

void GameMusicC::stopCurrentMusic(const std::string& music) {
    reinterpret_cast<SoundComponent*>(father_->getComponent("SoundComponent"))
        ->stopSound(music);
}

// FACTORY INFRASTRUCTURE DEFINITION

GameMusicCFactory::GameMusicCFactory() = default;

Component* GameMusicCFactory::create(Entity* _father, Json::Value& _data,
                                     Scene* _scene) {
    GameMusicC* gameMusic = new GameMusicC();

    _scene->getComponentsManager()->addDC(gameMusic);

    gameMusic->setFather(_father);
    gameMusic->setScene(_scene);

    if (!_data["sound"].isString())
        throw std::exception("GameMusicC: sound is not string");
    gameMusic->setMusic(_data["sound"].asString());

    return gameMusic;
}

DEFINE_FACTORY(GameMusicC);
