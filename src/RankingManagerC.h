#pragma once
#include "EventComponent.h"
#include "Factory.h"
#include <iostream>
#include <string>
#include <vector>

DECLARE_FACTORY(RankingManagerC)

struct RankingPosition {
    int round;
    std::string name;

    bool operator<(RankingPosition const& b) const { return round > b.round; }

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

class RankingManagerC final : public Component {
    std::vector<RankingPosition> ranking_;
    std::string playerName_ = "name";

  public:
    RankingManagerC();
    ~RankingManagerC();

    void destroy() override;

    void readRanking();
    void updateRanking();

    void playerDied();
    void setName();

    RankingPosition* getRankingPosition(int pos);
};