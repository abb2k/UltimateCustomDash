#include "spike.h"

spike* spike::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new spike();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool spike::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("spikeIcon.png"_spr);
    icon->setScale(0.6f);
    mainLayer->ductUI->addChild(icon);

    location = mainLayer->resetDuctPosition();
    icon->setPosition(mainLayer->getLocationFromDuctPos(location));

    if (_AILevel == 0){
        icon->setVisible(false);
    }

    mainLayer->PreloadImages(std::vector<std::string>{
        "spikeJ0001.png"_spr,
        "spikeJ0002.png"_spr,
        "spikeJ0003.png"_spr,
        "spikeJ0004.png"_spr,
        "spikeJ0005.png"_spr,
        "spikeJ0006.png"_spr,
        "spikeJ0007.png"_spr,
        "spikeJ0008.png"_spr,
        "spikeJ0009.png"_spr,
        "spikeJ0010.png"_spr,
        "spikeJ0011.png"_spr,
        "spikeJ0012.png"_spr,
        "spikeJ0013.png"_spr,
        "spikeJ0014.png"_spr,
        "spikeJ0015.png"_spr,
        "spikeJ0016.png"_spr,
        "spikeJ0017.png"_spr,
        "spikeJ0018.png"_spr,
        "spikeJ0019.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void spike::update(float delta){
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

void spike::OnOpportunity(){
    int didListenToLure = 0;
    if (!mainLayer->isInAudioLure(location)){
        didListenToLure = 0;
    }
    else{
        didListenToLure = rand() % 2;
    }
    if (!mainLayer->hasReachedEndofDucts(location)){
        if (didListenToLure == 0){
            location = mainLayer->moveDuctPos(location);
        }
        else{
            location = mainLayer->audioLoreLocation;
        }
        icon->setPosition(mainLayer->getLocationFromDuctPos(location));
    }
    else{
        if (didListenToLure == 0){
            location = mainLayer->moveDuctPos(location);
        }
        else{
            location = mainLayer->audioLoreLocation;
        }
        icon->setPosition(mainLayer->getLocationFromDuctPos(location));

        if (!mainLayer->isOnClosedDuct(location) && mainLayer->hasReachedEndofDucts(location)){
            icon->setVisible(false);
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                0.04f, 19, new std::string[]{
                    "spikeJ0001.png"_spr,
                    "spikeJ0002.png"_spr,
                    "spikeJ0003.png"_spr,
                    "spikeJ0004.png"_spr,
                    "spikeJ0005.png"_spr,
                    "spikeJ0006.png"_spr,
                    "spikeJ0007.png"_spr,
                    "spikeJ0008.png"_spr,
                    "spikeJ0009.png"_spr,
                    "spikeJ0010.png"_spr,
                    "spikeJ0011.png"_spr,
                    "spikeJ0012.png"_spr,
                    "spikeJ0013.png"_spr,
                    "spikeJ0014.png"_spr,
                    "spikeJ0015.png"_spr,
                    "spikeJ0016.png"_spr,
                    "spikeJ0017.png"_spr,
                    "spikeJ0018.png"_spr,
                    "spikeJ0019.png"_spr,
                }
            ), "explode_11.mp3"_spr, false, false, false);
        }
    }
}