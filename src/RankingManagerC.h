#pragma once
#include "EventComponent.h"
#include "Factory.h"

#include <string>
#include <vector>

DECLARE_FACTORY(RankingManagerC);

class SpawnerEnemiesEC;
class SpawnerEC;

struct RankingPosition {
    int round;
    std::string name;

    bool operator<(RankingPosition const& b) { return round > b.round; }
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