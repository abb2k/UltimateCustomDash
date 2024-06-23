#include "viprin.h"

viprin* viprin::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new viprin();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool viprin::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("viprin.png"_spr);
    icon->setZOrder(1);
    icon->setScale(0.8f);
    mainLayer->ventUI->addChild(icon);

    Position = mainLayer->resetVentPos();

    scheduleUpdate();

    return true;
}

void viprin::update(float delta){
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
    if (mainLayer->hasReachedEndOfVent(Position) && !killplayer){
        killplayer = true;
        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
            1, 2, new std::string[]{
                "viprin.png"_spr,
                "viprin.png"_spr,
            }
        ), "explode_11.ogg"_spr, false, false, false, 7);
    }
    if (_AILevel == 0){
        icon->setVisible(false);
    }
    else{
        icon->setVisible(true);
    }
}

void viprin::OnOpportunity(){
    if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::SilentVentelation){
        Position.progressAmount += 8;
    }
    else{
        Position.progressAmount += 10;
    }
    

    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
}