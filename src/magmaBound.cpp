#include "magmaBound.h"

magmaBound* magmaBound::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new magmaBound();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool magmaBound::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("magmaBound.png"_spr);
    icon->setZOrder(1);
    icon->setScale(0.8f);
    mainLayer->ventUI->addChild(icon);

    ventFace = CCSprite::create("magmaBound.png"_spr);
    ventFace->setZOrder(-1);
    ventFace->setOpacity(0);
    ventFace->setPosition(mainLayer->doorUp->getPosition());
    mainLayer->World->addChild(ventFace);

    Position = mainLayer->resetVentPos();

    if (_AILevel == 0){
        icon->setVisible(false);
    }
    else{
        icon->setVisible(true);
    }

    scheduleUpdate();

    return true;
}

void magmaBound::update(float delta){
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
    if (mainLayer->hasReachedEndOfVent(Position)){
        if (!enteredFVent){
            enteredFVent = true;
            icon->setVisible(false);
            ventFace->runAction(CCFadeIn::create(0.4f));
        }

        if (killtimer > 0){
            killtimer -= delta;
            if (mainLayer->doorUpClosed){
                if (PreventTime > 0){
                    PreventTime -= delta;
                }
                else{
                    killtimer = 4;
                    PreventTime = 1;
                    icon->setVisible(true);
                    Position = mainLayer->resetVentPos();
                    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
                    mainLayer->CharacterBlock();
                    ventFace->setOpacity(0);
                    enteredFVent = false;
                }
            }
        }
        else {
            if (mainLayer->doorUpClosed){
                if (PreventTime > 0){
                    PreventTime -= delta;
                }
                else{
                    killtimer = 4;
                    PreventTime = 1;
                    icon->setVisible(true);
                    Position = mainLayer->resetVentPos();
                    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
                    mainLayer->CharacterBlock();
                    ventFace->setOpacity(0);
                    enteredFVent = false;
                }
            }
            else if (!killplayer){
                killplayer = true;
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    1, 2, new std::string[]{
                        "magmaBound.png"_spr,
                        "magmaBound.png"_spr,
                    }
                ), "explode_11.ogg"_spr, false, false, false, 7);
                ventFace->setVisible(false);
            }
        }
        
    }
}

void magmaBound::OnOpportunity(){
    int addedAmount = 10;
    if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::SilentVentelation){
        addedAmount -= 2;
    }
    
    addedAmount += mainLayer->tempreture / 100;

    Position.progressAmount += addedAmount;

    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
}