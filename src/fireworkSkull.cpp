#include "fireworkSkull.h"

fireworkSkull* fireworkSkull::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new fireworkSkull();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool fireworkSkull::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    _opportunityDefault = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("fireworkSkull.png"_spr);
    mainLayer->ductUI->addChild(icon);

    location = mainLayer->resetDuctPosition();
    icon->setPosition(mainLayer->getLocationFromDuctPos(location));

    if (_AILevel == 0){
        icon->setVisible(false);
    }

    scheduleUpdate();

    return true;
}

void fireworkSkull::update(float delta){
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

        if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::GMB && _AILevel != 0){
            _opportunity = _opportunityDefault - 0.3f;
        }
        else{
            _opportunity = _opportunityDefault;
        }
    }
}

void fireworkSkull::OnOpportunity(){
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
                0.7f, 2, new std::string[]{
                    "fireworkSkull.png"_spr,
                    "fireworkSkull.png"_spr
                }
            ), "", false, false, false, 7);
        }
    }
}