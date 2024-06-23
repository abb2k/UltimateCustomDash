#include "karmaL.h"

karmaL* karmaL::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new karmaL();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool karmaL::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    Awake = CCSprite::create("karAwake.png"_spr);
    Awake->setZOrder(3);
    Awake->setVisible(false);
    Awake->setPosition({462, 77});
    Awake->setScale(2);
    Awake->setRotationX(1);
    Awake->setRotationX(7);
    mainLayer->World->addChild(Awake);

    asleep = CCSprite::create("karAsleep.png"_spr);
    asleep->setZOrder(3);
    asleep->setPosition({468, 58});
    asleep->setScale(2);
    asleep->setRotationX(57);
    asleep->setRotationX(18);
    mainLayer->World->addChild(asleep);

    if (_AILevel == 0){
        asleep->setVisible(false);
    }

    scheduleUpdate();

    return true;
}

void karmaL::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (_AILevel != 0){
            if (mainLayer->LookingAtCams){
                if (canKill){
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.7f, 2, new std::string[]{
                            "karAwake.png"_spr,
                            "karAwake.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }
                if (!rollWakeChance){
                    rollWakeChance = true;
                    int oppCalc = 1 + (rand() % 22);
                    if (_AILevel != 0 && _AILevel >= oppCalc){
                        OnOpportunity();
                    }
                }
            }
            else {
                rollWakeChance = false;
                if (awake){
                    canKill = true;
                }
            }
            if (awake){
                if (mainLayer->FlashlightOn && mainLayer->lookingTowardsRight){
                    awake = false;
                    Awake->setVisible(false);
                    asleep->setVisible(true);
                    canKill = false;
                    oneFlashLock = true;
                }
            }
            else if (!oneFlashLock){
                if (mainLayer->FlashlightOn && mainLayer->lookingTowardsRight){
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.7f, 2, new std::string[]{
                            "karAwake.png"_spr,
                            "karAwake.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }
                
            }
            if (!mainLayer->FlashlightOn){
                oneFlashLock = false;
            }
        }
    }
}

void karmaL::OnOpportunity(){
    awake = true;
    Awake->setVisible(true);
    asleep->setVisible(false);
}