#include "SSKeeper.h"

SSKeeper* SSKeeper::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new SSKeeper();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SSKeeper::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("secretShopkeeperIcon.png"_spr);
    icon->setScale(0.8f);
    mainLayer->ductUI->addChild(icon);

    location = mainLayer->resetDuctPosition();
    icon->setPosition(mainLayer->getLocationFromDuctPos(location));

    if (_AILevel == 0){
        icon->setVisible(false);
    }

    mainLayer->PreloadImages(std::vector<std::string>{
        "SSKJ0001.png"_spr,
        "SSKJ0002.png"_spr,
        "SSKJ0003.png"_spr,
        "SSKJ0004.png"_spr,
        "SSKJ0005.png"_spr,
        "SSKJ0006.png"_spr,
        "SSKJ0007.png"_spr,
        "SSKJ0008.png"_spr,
        "SSKJ0009.png"_spr,
        "SSKJ0010.png"_spr,
        "SSKJ0011.png"_spr,
        "SSKJ0012.png"_spr,
        "SSKJ0013.png"_spr,
        "SSKJ0014.png"_spr,
        "SSKJ0015.png"_spr,
        "SSKJ0016.png"_spr,
        "SSKJ0017.png"_spr,
        "SSKJ0018.png"_spr,
        "SSKJ0019.png"_spr,
        "SSKJ0020.png"_spr,
        "SSKJ0021.png"_spr,
        "SSKJ0022.png"_spr,
        "SSKJ0023.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void SSKeeper::update(float delta){
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

void SSKeeper::OnOpportunity(){
    int didListenToLure = 0;
    if (mainLayer->isInAudioLure(location)){
        didListenToLure = 1;
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
                0.03f, 23, new std::string[]{
                    "SSKJ0001.png"_spr,
                    "SSKJ0002.png"_spr,
                    "SSKJ0003.png"_spr,
                    "SSKJ0004.png"_spr,
                    "SSKJ0005.png"_spr,
                    "SSKJ0006.png"_spr,
                    "SSKJ0007.png"_spr,
                    "SSKJ0008.png"_spr,
                    "SSKJ0009.png"_spr,
                    "SSKJ0010.png"_spr,
                    "SSKJ0011.png"_spr,
                    "SSKJ0012.png"_spr,
                    "SSKJ0013.png"_spr,
                    "SSKJ0014.png"_spr,
                    "SSKJ0015.png"_spr,
                    "SSKJ0016.png"_spr,
                    "SSKJ0017.png"_spr,
                    "SSKJ0018.png"_spr,
                    "SSKJ0019.png"_spr,
                    "SSKJ0020.png"_spr,
                    "SSKJ0021.png"_spr,
                    "SSKJ0022.png"_spr,
                    "SSKJ0023.png"_spr,
                }, 2
            ), "magicEx.mp3"_spr, false, false, false);
        }
    }
}