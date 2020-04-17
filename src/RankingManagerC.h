#pragma once
#include "EventComponent.h"
#include "Factory.h"

#include <iostream>
#include <string>
#include <vector>

DECLARE_FACTORY(RankingManagerC);

class SpawnerEnemiesEC;
class SpawnerEC;

struct RankingPosition {
    int round;
    std::string name;

    bool operator<(RankingPosition const& b) { return round > b.round; }

    friend std::ostream& operator<<(std::ostream& out,
                                    const RankingPosition& rank) {
        out << rank.name << ' ' << rank.round << '\n';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, RankingPosition& rank) {
        in >> rank.name >> rank.round;
        return in;
    }
};

class RankingManagerC : public Component {
  private:
    std::vector<RankingPosition> ranking;

  public:
    RankingManagerC();
    ~RankingManagerC();

    virtual void destroy();

    void readRanking();
    void updateRanking();

    void playerDied();
};