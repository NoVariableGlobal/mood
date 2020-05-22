#include "GameMusicC.h"

#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Scene.h"
#include "SoundComponent.h"

#include <json.h>

void GameMusicC::destroy() {
    stopCurrentMusic(music);
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void GameMusicC::setMusic(std::string music_) {
    if (music != music_) {
        dynamic_cast<SoundComponent*>(father_->getComponent("SoundComponent"))
            ->stopSound(music);
        music = music_;
        dynamic_cast<SoundComponent*>(father_->getComponent("SoundComponent"))
            ->playSound(music);
    }
}

void GameMusicC::stopCurrentMusic(std::string music_) {
    dynamic_cast<SoundComponent*>(father_->getComponent("SoundComponent"))
        ->stopSound(music_);
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
