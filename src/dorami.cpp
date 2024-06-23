#include "dorami.h"

dorami* dorami::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new dorami();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool dorami::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("doraIcon.png"_spr);
    icon->setZOrder(1);
    icon->setScale(0.6f);
    mainLayer->ventUI->addChild(icon);

    Position = mainLayer->resetVentPos();

    mainLayer->PreloadImages(std::vector<std::string>{
        "doraJ0001.png"_spr,
        "doraJ0002.png"_spr,
        "doraJ0003.png"_spr,
        "doraJ0004.png"_spr,
        "doraJ0005.png"_spr,
        "doraJ0006.png"_spr,
        "doraJ0007.png"_spr,
        "doraJ0008.png"_spr,
        "doraJ0009.png"_spr,
        "doraJ0010.png"_spr,
        "doraJ0011.png"_spr,
        "doraJ0012.png"_spr,
        "doraJ0013.png"_spr,
        "doraJ0014.png"_spr,
        "doraJ0015.png"_spr,
        "doraJ0016.png"_spr,
        "doraJ0017.png"_spr,
        "doraJ0018.png"_spr,
        "doraJ0019.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void dorami::update(float delta){
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

        if (mainLayer->doorUpClosed){
            Position = mainLayer->resetVentPos();
            icon->setPosition(mainLayer->getVentPointFromPosition(Position));
            mainLayer->CharacterBlock();
        }
        else if (!killplayer){
            killplayer = true;
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                0.032f, 19, new std::string[]{
                    "doraJ0001.png"_spr,
                    "doraJ0002.png"_spr,
                    "doraJ0003.png"_spr,
                    "doraJ0004.png"_spr,
                    "doraJ0005.png"_spr,
                    "doraJ0006.png"_spr,
                    "doraJ0007.png"_spr,
                    "doraJ0008.png"_spr,
                    "doraJ0009.png"_spr,
                    "doraJ0010.png"_spr,
                    "doraJ0011.png"_spr,
                    "doraJ0012.png"_spr,
                    "doraJ0013.png"_spr,
                    "doraJ0014.png"_spr,
                    "doraJ0015.png"_spr,
                    "doraJ0016.png"_spr,
                    "doraJ0017.png"_spr,
                    "doraJ0018.png"_spr,
                    "doraJ0019.png"_spr,
                }, 2
            ), "doramiAA.mp3"_spr, false, false, false);
        }
    }
    if (_AILevel == 0){
        icon->setVisible(false);
    }
    else{
        icon->setVisible(true);
    }
}

void dorami::OnOpportunity(){
    if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::SilentVentelation){
        Position.progressAmount += 8;
    }
    else{
        Position.progressAmount += 10;
    }
    

    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
}