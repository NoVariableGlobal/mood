#include "RankingManagerC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "SpawnerEnemiesEC.h"

#include <time.h>
#include <value.h>

RankingManagerC::RankingManagerC() { readRanking(); }

RankingManagerC::~RankingManagerC() { updateRanking(); }

void RankingManagerC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
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

            ranking.push_back(rank);
        }

        std::cin.rdbuf(cinbuf);
    } else {
        for (int i = 0; i < 5; i++) {
            RankingPosition rank;

            rank.name = "-";
            rank.round = 0;
            ranking.push_back(rank);
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

            RankingPosition rank = ranking[i];

            std::cout << i + 1 << " ";
            std::cout << rank;
        }

        std::cout.rdbuf(coutbuf);
    }
    myfile.close();
}

void RankingManagerC::playerDied() {

    RankingPosition rank;

    rank.name = "name";
    rank.round = reinterpret_cast<RoundManagerEC*>(
                     father->getComponent("RoundManagerEC"))
                     ->getRoundNumber();

    ranking.push_back(rank);

    std::sort(ranking.begin(), ranking.end());

    ranking.pop_back();
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

    return rankingManagerC;
};

DEFINE_FACTORY(RankingManagerC);