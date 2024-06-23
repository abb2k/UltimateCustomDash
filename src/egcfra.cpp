#include "egcfra.h"

egcfra* egcfra::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new egcfra();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool egcfra::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("animMonster.png"_spr);
    icon->setZOrder(1);
    icon->setScale(0.8f);
    mainLayer->ventUI->addChild(icon);

    Position = mainLayer->resetVentPos();

    scheduleUpdate();

    return true;
}

void egcfra::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (opportunityTimer > 0){
            opportunityTimer -= delta;
        }
        else{
            opportunityTimer = _opportunity;
            int oppCalc = 1 + (rand() % 22);
            if (_AILevel != 0 && _AILevel >= oppCalc){
                OnOpportunity();
            }
        }
    }

    if (mainLayer->isTouchingVentSnare(Position)){
        Position = mainLayer->resetVentPos();
        icon->setPosition(mainLayer->getVentPointFromPosition(Position));
        mainLayer->CharacterBlock();
    }
    if (mainLayer->hasReachedEndOfVent(Position)){
        if (mainLayer->doorUpClosed){
            Position = mainLayer->resetVentPos();
            icon->setPosition(mainLayer->getVentPointFromPosition(Position));
            mainLayer->CharacterBlock();
        }
        else if (!killplayer){
            killplayer = true;
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                1, 2, new std::string[]{
                    "animMonster.png"_spr,
                    "animMonster.png"_spr,
                }
            ), "explode_11.ogg"_spr, false, false, false, 7);
        }
    }
    if (_AILevel == 0){
        icon->setVisible(false);
    }
    else{
        icon->setVisible(true);
    }
}

void egcfra::OnOpportunity(){
    Position.progressAmount += 10;
    
    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
}