#include "bloodlust.h"

bloodlust* bloodlust::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new bloodlust();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool bloodlust::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("bloodlust.png"_spr);
    icon->setScale(0.7f);
    mainLayer->ductUI->addChild(icon);

    location = mainLayer->resetDuctPosition();
    icon->setPosition(mainLayer->getLocationFromDuctPos(location));

    if (_AILevel == 0){
        icon->setVisible(false);
    }

    scheduleUpdate();

    return true;
}

void bloodlust::update(float delta){
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

void bloodlust::OnOpportunity(){
    int didListenToLure = 3;
    if (!mainLayer->isInAudioLure(location)){
        didListenToLure = 3;
    }
    else{
        didListenToLure = rand() % 8;
    }
    if (!mainLayer->hasReachedEndofDucts(location)){
        if (didListenToLure == 3){
            location = mainLayer->moveDuctPos(location);
        }
        else{
            location = mainLayer->audioLoreLocation;
        }
        icon->setPosition(mainLayer->getLocationFromDuctPos(location));
    }
    else{
        if (didListenToLure == 3){
            location = mainLayer->moveDuctPos(location);
        }
        else{
            location = mainLayer->audioLoreLocation;
        }
        icon->setPosition(mainLayer->getLocationFromDuctPos(location));

        if (!mainLayer->isOnClosedDuct(location) && mainLayer->hasReachedEndofDucts(location)){
            icon->setVisible(false);
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                0.7f, 2, new std::string[]{
                    "bloodlust.png"_spr,
                    "bloodlust.png"_spr
                }
            ), "", false, false, false, 7);
        }
    }
}