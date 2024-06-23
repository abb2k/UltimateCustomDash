#include "Spooky.h"

Spooky* Spooky::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new Spooky();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool Spooky::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("TVKIcon.png"_spr);
    icon->setScale(0.45f);
    mainLayer->ductUI->addChild(icon);

    location = mainLayer->resetDuctPosition();
    icon->setPosition(mainLayer->getLocationFromDuctPos(location));

    if (_AILevel == 0){
        icon->setVisible(false);
    }

    scheduleUpdate();

    return true;
}

void Spooky::update(float delta){
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

        if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::Heater && _AILevel != 0){
            if (escapeTimer > 0){
                escapeTimer -= delta;
            }
            else {
                location = mainLayer->resetDuctPosition();
                icon->setPosition(mainLayer->getLocationFromDuctPos(location));
                FMODAudioEngine::sharedEngine()->playEffect("metal4.mp3"_spr, 1.0f,1.0f,1.0f);
                escapeTimer = mainLayer->randomFloat(0, 3);
            }
        }
        else{
            escapeTimer = mainLayer->randomFloat(0, 3);
        }
    }
}

void Spooky::OnOpportunity(){
    if (!mainLayer->hasReachedEndofDucts(location)){
        location = mainLayer->moveDuctPos(location);
        icon->setPosition(mainLayer->getLocationFromDuctPos(location));
    }
    else{
        location = mainLayer->moveDuctPos(location);
        icon->setPosition(mainLayer->getLocationFromDuctPos(location));

        if (!mainLayer->isOnClosedDuct(location) && mainLayer->hasReachedEndofDucts(location)){
            icon->setVisible(false);
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                0.03f, 15, new std::string[]{
                    "TVKJu0001.png"_spr,
                    "TVKJu0002.png"_spr,
                    "TVKJu0003.png"_spr,
                    "TVKJu0004.png"_spr,
                    "TVKJu0005.png"_spr,
                    "TVKJu0006.png"_spr,
                    "TVKJu0007.png"_spr,
                    "TVKJu0008.png"_spr,
                    "TVKJu0009.png"_spr,
                    "TVKJu0010.png"_spr,
                    "TVKJu0011.png"_spr,
                    "TVKJu0012.png"_spr,
                    "TVKJu0013.png"_spr,
                    "TVKJu0014.png"_spr,
                    "TVKJu0015.png"_spr,
                }, 3
            ), "explode_11.mp3"_spr, false, false, false);
        }
    }
}