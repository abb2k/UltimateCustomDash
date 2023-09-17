#include <challengeCell.h>

#include "challenges.h"
#include "customNightLayer.h"

challengeCell* challengeCell::create(std::string challengeName, std::vector<animatronic*> cha) {
    auto ret = new challengeCell();
    if (ret && ret->init(challengeName, cha)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}


bool challengeCell::init(std::string challengeName, std::vector<animatronic*> cha){

    chaSave = cha;

    button = CCSprite::create("abb2k.UltimateCustomDash/emptybut.png");
    buttonG = CCSprite::create("abb2k.UltimateCustomDash/emptybutOn.png");
    buttonG->setVisible(false);

    CCLabelTTF* name = CCTextFieldTTF::create(challengeName.c_str(), "chatFont.fnt", 6);
    //name->setScale(0.15f);
    name->setZOrder(1);
    this->addChild(name);
    this->addChild(button);
    this->addChild(buttonG);

    scheduleUpdate();

    return true;
}

void challengeCell::update(float delta){
    challenges* parentNode = (challenges*)dad;

    if (parentNode->getTouchOn(button)){
        customNightLayer* mainLayer = (customNightLayer*)parentNode->dad;
        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        selected = true;
        mainLayer->_AnimatronicCellContainer->SetAll(0);
        for (size_t i = 0; i < chaSave.size(); i++)
        {
            mainLayer->_AnimatronicCellContainer->SetSpecific(chaSave[i]->name,chaSave[i]->difficulty);
        }
    }
    if (!parentNode->getHover(button)){
        if (parentNode->clicking){
            selected = false;
        }
    }

    button->setVisible(!selected);
    buttonG->setVisible(selected);
}