#include "GuiRankingLabelC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiContext.h"
#include "GuiLabelC.h"
#include "RankingManagerC.h"
#include "Scene.h"
#include <json.h>

GuiRankingLabelC::GuiRankingLabelC() {}

void GuiRankingLabelC::createText(bool roundNumber, int rankingPosition) {

    RankingPosition* rank = reinterpret_cast<RankingManagerC*>(
                                scene_->getEntityById("GameManager")
                                    ->getComponent("RankingManagerC"))
                                ->getRankingPosition(rankingPosition);

    if (roundNumber)
        setText("Round " + std::to_string(rank->round));
    else
        setText(rank->name);
}

// FACTORY INFRASTRUCTURE DEFINITION

GuiRankingLabelCFactory::GuiRankingLabelCFactory() = default;

Component* GuiRankingLabelCFactory::create(Entity* _father, Json::Value& _data,
                                           Scene* _scene) {
    GuiRankingLabelC* guiRankingLabelC = new GuiRankingLabelC();
    _scene->getComponentsManager()->addDC(guiRankingLabelC);

    guiRankingLabelC->setFather(_father);
    guiRankingLabelC->setScene(_scene);

    if (!_data["rankingPosition"].isInt())
        throw std::exception("GuiRankingLabelC: rankingPosition is not an int");

    if (!_data["roundNumber"].isBool())
        throw std::exception("GuiRankingLabelC: roundNumber is not an int");
    guiRankingLabelC->createText(_data["roundNumber"].asBool(),
                                 _data["rankingPosition"].asInt());

    if (!_data["position"].isArray())
        throw std::exception("GuiRankingLabelC: position is not an array");
    guiRankingLabelC->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                            _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("GuiRankingLabelC: size is not an array");
    guiRankingLabelC->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("GuiRankingLabelC: name is not a string");
    guiRankingLabelC->setName(_data["name"].asString());

    guiRankingLabelC->create();

    return guiRankingLabelC;
}

DEFINE_FACTORY(GuiRankingLabelC);
