#include "clubstepMonster.h"

clubstepMonster* clubstepMonster::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new clubstepMonster();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool clubstepMonster::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    monsterTop = CCSprite::create("topMonster.png"_spr);
    monsterTop->setScale(3.9f);
    monsterTop->setPosition({0, 685});
    mainLayer->Canvas->addChild(monsterTop);

    monsterBottom = CCSprite::create("bottomMonster.png"_spr);
    monsterBottom->setScale(3.9f);
    monsterBottom->setPosition({32, -695});
    mainLayer->Canvas->addChild(monsterBottom);

    scheduleUpdate();

    return true;
}

void clubstepMonster::update(float delta){
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
        if (startp){
            if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::Heater){
                if (currentProgression > 0){
                    currentProgression -= delta * 30;
                    monsterBottom->setPositionY((-695 + currentProgression));
                    monsterTop->setPositionY((685 - (currentProgression * 1.9066666666666666666666666666667f)));

                    if (currentProgression <= 0){
                        currentProgression = 0;
                        monsterBottom->setPositionY((-695 + currentProgression));
                        monsterTop->setPositionY((685 - (currentProgression * 1.9066666666666666666666666666667f)));
                        startp = false;
                    }
                }
            }
            else {
                if (currentProgression < 255){
                    currentProgression += delta * 20;
                    monsterBottom->setPositionY((-695 + currentProgression));
                    monsterTop->setPositionY((685 - (currentProgression * 1.9066666666666666666666666666667f)));

                    if (currentProgression >= 255){
                        currentProgression = 255;
                        monsterBottom->setVisible(false);
                        monsterTop->setVisible(false);
                        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                            0.035f, 17, new std::string[]{
                                "clubMJ0001.png"_spr,
                                "clubMJ0002.png"_spr,
                                "clubMJ0003.png"_spr,
                                "clubMJ0004.png"_spr,
                                "clubMJ0005.png"_spr,
                                "clubMJ0006.png"_spr,
                                "clubMJ0007.png"_spr,
                                "clubMJ0008.png"_spr,
                                "clubMJ0009.png"_spr,
                                "clubMJ0010.png"_spr,
                                "clubMJ0011.png"_spr,
                                "clubMJ0012.png"_spr,
                                "clubMJ0013.png"_spr,
                                "clubMJ0014.png"_spr,
                                "clubMJ0015.png"_spr,
                                "clubMJ0016.png"_spr,
                                "clubMJ0017.png"_spr,
                            }, 2
                        ), "explode_11.mp3"_spr, false, false, false);
                    }
                }
            }
            
        }
    }
}

void clubstepMonster::OnOpportunity(){
    startp = true;
}