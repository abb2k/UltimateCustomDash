#include "toe2Monster.h"

toe2Monster* toe2Monster::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new toe2Monster();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool toe2Monster::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("TOE2MIcon.png"_spr);
    icon->setScale(0.25f);
    mainLayer->ductUI->addChild(icon);

    location = mainLayer->resetDuctPosition();
    icon->setPosition(mainLayer->getLocationFromDuctPos(location));

    if (_AILevel == 0){
        icon->setVisible(false);
    }

    mainLayer->PreloadImages(std::vector<std::string>{
        "toe2MJ0001.png"_spr,
        "toe2MJ0002.png"_spr,
        "toe2MJ0003.png"_spr,
        "toe2MJ0004.png"_spr,
        "toe2MJ0005.png"_spr,
        "toe2MJ0006.png"_spr,
        "toe2MJ0007.png"_spr,
        "toe2MJ0008.png"_spr,
        "toe2MJ0009.png"_spr,
        "toe2MJ0010.png"_spr,
        "toe2MJ0011.png"_spr,
        "toe2MJ0012.png"_spr,
        "toe2MJ0013.png"_spr,
        "toe2MJ0014.png"_spr,
        "toe2MJ0015.png"_spr,
        "toe2MJ0016.png"_spr,
        "toe2MJ0017.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void toe2Monster::update(float delta){
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

void toe2Monster::OnOpportunity(){
    int didListenToLure = 3;
    if (!mainLayer->isInAudioLure(location)){
        didListenToLure = 3;
    }
    else{
        didListenToLure = rand() % 4;
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
                0.03f, 17, new std::string[]{
                    "toe2MJ0001.png"_spr,
                    "toe2MJ0002.png"_spr,
                    "toe2MJ0003.png"_spr,
                    "toe2MJ0004.png"_spr,
                    "toe2MJ0005.png"_spr,
                    "toe2MJ0006.png"_spr,
                    "toe2MJ0007.png"_spr,
                    "toe2MJ0008.png"_spr,
                    "toe2MJ0009.png"_spr,
                    "toe2MJ0010.png"_spr,
                    "toe2MJ0011.png"_spr,
                    "toe2MJ0012.png"_spr,
                    "toe2MJ0013.png"_spr,
                    "toe2MJ0014.png"_spr,
                    "toe2MJ0015.png"_spr,
                    "toe2MJ0016.png"_spr,
                    "toe2MJ0017.png"_spr,
                }, 2
            ), "explode_11.mp3"_spr, false, false, false);
        }
    }
}