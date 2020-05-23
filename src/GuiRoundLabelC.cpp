#include "GuiRoundLabelC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "GuiContext.h"
#include "GuiLabelC.h"
#include "RoundManagerEC.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

GuiRoundLabelC::GuiRoundLabelC() {}

void GuiRoundLabelC::createText() {

    int round =
        reinterpret_cast<RoundManagerEC*>(scene_->getEntityById("GameManager")
                                              ->getComponent("RoundManagerEC"))
            ->getRoundNumber();

    setText(std::to_string(round));
}

// FACTORY INFRASTRUCTURE DEFINITION

GuiRoundLabelCFactory::GuiRoundLabelCFactory() = default;

Component* GuiRoundLabelCFactory::create(Entity* _father, Json::Value& _data,
                                         Scene* _scene) {
    GuiRoundLabelC* guiRoundLabelC = new GuiRoundLabelC();
    _scene->getComponentsManager()->addDC(guiRoundLabelC);

    guiRoundLabelC->setFather(_father);
    guiRoundLabelC->setScene(_scene);

    guiRoundLabelC->createText();

    if (!_data["position"].isArray())
        throw std::exception("guiRoundLabelC: position is not an array");
    guiRoundLabelC->setPosition(glm::vec2(_data["position"][0].asFloat(),
                                          _data["position"][1].asFloat()));

    if (!_data["size"].isArray())
        throw std::exception("guiRoundLabelC: size is not an array");
    guiRoundLabelC->setSize(
        glm::vec2(_data["size"][0].asFloat(), _data["size"][1].asFloat()));

    if (!_data["name"].isString())
        throw std::exception("guiRoundLabelC: name is not a string");
    guiRoundLabelC->setName(_data["name"].asString());

    guiRoundLabelC->create();

    return guiRoundLabelC;
}

DEFINE_FACTORY(GuiRoundLabelC);
