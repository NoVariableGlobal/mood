#include "RankingManagerC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GameMusicC.h"
#include "ReadNameIC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include <value.h>

RankingManagerC::RankingManagerC() { readRanking(); }

RankingManagerC::~RankingManagerC() { updateRanking(); }

void RankingManagerC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseDC(this);
}

void RankingManagerC::readRanking() {
    std::ifstream myfile;
    myfile.open("Files/ranking.txt");
    if (myfile.is_open()) {

        auto cinbuf = std::cin.rdbuf(myfile.rdbuf());

        for (int i = 0; i < 5; i++) {

            RankingPosition rank;
            int aux;
            std::cin >> aux;

            std::cin >> rank;

            ranking_.push_back(rank);
        }

        std::cin.rdbuf(cinbuf);
    } else {
        for (int i = 0; i < 5; i++) {
            RankingPosition rank;

            rank.name = "-";
            rank.round = 0;
            ranking_.push_back(rank);
        }
    }
    myfile.close();
}

void RankingManagerC::updateRanking() {

    remove("files/ranking.txt");

    std::ofstream myfile;
    myfile.open("files/ranking.txt", std::ios::out);
    if (myfile.is_open()) {

        auto coutbuf = std::cout.rdbuf(myfile.rdbuf());

        for (int i = 0; i < 5; i++) {

            RankingPosition rank = ranking_[i];

            std::cout << i + 1 << " ";
            std::cout << rank;
        }

        std::cout.rdbuf(coutbuf);
    }
    myfile.close();
}

void RankingManagerC::playerDied() {

    RankingPosition rank;

    rank.name = playerName_;
    rank.round = reinterpret_cast<RoundManagerEC*>(
                     father_->getComponent("RoundManagerEC"))
                     ->getRoundNumber();

    ranking_.push_back(rank);

    std::sort(ranking_.begin(), ranking_.end());

    ranking_.pop_back();

    reinterpret_cast<GameMusicC*>(
        scene_->getEntityById("GameManager")->getComponent("GameMusicC"))
        ->setMusic("RankingBackgroundMusic");
}

void RankingManagerC::setName() {

    Entity* nameCapturer = scene_->getEntityById("NameCapturer");
    playerName_ =
        reinterpret_cast<ReadNameIC*>(nameCapturer->getComponent("ReadNameIC"))
            ->gatName();

    scene_->deleteEntity(nameCapturer);
}

RankingPosition* RankingManagerC::getRankingPosition(int pos) {
    return &ranking_[pos - 1];
}

// FACTORY INFRASTRUCTURE
RankingManagerCFactory::RankingManagerCFactory() = default;

Component* RankingManagerCFactory::create(Entity* _father, Json::Value& _data,
                                          Scene* _scene) {
    RankingManagerC* rankingManagerC = new RankingManagerC();

    rankingManagerC->setFather(_father);
    rankingManagerC->setScene(_scene);
    _scene->getComponentsManager()->addDC(rankingManagerC);

    rankingManagerC->setActive(true);

    if (_data["game"].isBool())
        rankingManagerC->setName();

    return rankingManagerC;
};

DEFINE_FACTORY(RankingManagerC);