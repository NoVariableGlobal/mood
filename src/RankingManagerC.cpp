#include "RankingManagerC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include "SpawnerEnemiesEC.h"
#include <iostream>
#include <time.h>
#include <value.h>

RankingManagerC::RankingManagerC() { readRanking(); }

RankingManagerC::~RankingManagerC() {
    updateRanking();
}

void RankingManagerC::destroy() {
    setActive(false);
    scene->getComponentsManager()->eraseDC(this);
}

void RankingManagerC::readRanking() {
    std::ifstream myfile;
    myfile.open("Files/ranking.txt");
    if (myfile.is_open()) {

        auto cinbuf = std::cin.rdbuf(myfile.rdbuf());

        for (int i = 0; i < 10; i++) {

            RankingPosition rank;
            int pru = 0;
            std::cin >> pru;

            std::string name;
            std::cin >> name;

            rank.name = name;

            if (name != "-") {

                int round;
                std::cin >> round;

                rank.round = round;
            } else
                rank.round = 0;

            ranking.push_back(rank);
        }

        std::cin.rdbuf(cinbuf);
    }
    myfile.close();
}

void RankingManagerC::updateRanking() {

    remove("files/ranking.txt");

    std::ofstream myfile;
    myfile.open("files/ranking.txt", std::ios::out);
    if (myfile.is_open()) {

        auto coutbuf = std::cout.rdbuf(myfile.rdbuf());

        for (int i = 0; i < 10; i++) {

            RankingPosition rank = ranking[i];

            std::cout << i+1 << " ";
            std::cout << rank.name << " ";

            if (rank.name == "-")
                std::cout << "\n";
            else
                std::cout << rank.round << "\n";
        }

        std::cout.rdbuf(coutbuf);
    }
    myfile.close();
}

void RankingManagerC::playerDied() {

    RankingPosition rank;

    rank.name = "name";
    rank.round =
        dynamic_cast<RoundManagerEC*>(father->getComponent("RoundManagerEC"))
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