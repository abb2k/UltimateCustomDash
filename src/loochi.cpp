#include "loochi.h"

loochi* loochi::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new loochi();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool loochi::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    looch = CCSprite::create("loochiFrontHappy.png"_spr);
    mainLayer->cameraOverallUI->addChild(looch);

    scheduleUpdate();

    return true;
}

void loochi::update(float delta){
    if (!inJumpscare && mainLayer->NIGHTSTARTED){
        if (prevcamera != mainLayer->currentCamSelected){
            prevcamera = mainLayer->currentCamSelected;
            if (canAppear){
                canAppear = false;
                looch->setVisible(false);
            }
            else{
                int oppCalc = 1 + (rand() % 22);
                if (_AILevel != 0 && _AILevel >= oppCalc){
                    canAppear = true;
                    looch->setVisible(true);
                    looch->setZOrder(-5);

                    looktimer = 3 - (0.1f * _AILevel);

                    int randomPos = rand() % 3;

                    if (randomPos == 0){
                        looch->setPosition({-146, -21});
                        looch->setRotationX(32);
                        looch->setRotationY(45);
                    }
                    else if (randomPos == 1){
                        looch->setPosition({109, 81});
                        looch->setRotationX(202);
                        looch->setRotationY(202);
                    }
                    else if (randomPos == 2){
                        looch->setPosition({125, -74});
                        looch->setRotationX(370);
                        looch->setRotationY(377);
                    }
                }
            }
        }
        if (!mainLayer->LookingAtCams && !inJumpscare){
            if (!rollForCloseCams){
                int oppCalc = 1 + (rand() % 22);
                if (_AILevel != 0 && _AILevel >= oppCalc){
                    canAppear = true;
                    looch->setVisible(true);
                    looch->setZOrder(-5);
                    
                    looktimer = 3 - (0.1f * _AILevel);

                    int randomPos = rand() % 3;

                    if (randomPos == 0){
                        looch->setPosition({-146, -21});
                        looch->setRotationX(32);
                        looch->setRotationY(45);
                    }
                    else if (randomPos == 1){
                        looch->setPosition({109, 81});
                        looch->setRotationX(202);
                        looch->setRotationY(202);
                    }
                    else if (randomPos == 2){
                        looch->setPosition({125, -74});
                        looch->setRotationX(370);
                        looch->setRotationY(377);
                    }
                }
                else {
                    canAppear = false;
                    looch->setVisible(false);
                }
                rollForCloseCams = true;
            }
            jumps = false;
        }
        else{
            if (canAppear){
                if (looktimer > 0){
                    looktimer -= delta;
                }
                else{
                    if (!jumps){
                        jumps = true;
                        CCSprite* jumpscare = mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                            0.2f, 36, new std::string[]{
                                "loochiFrontAngry.png"_spr,
                                "loochiLeft.png"_spr,
                                "loochiBack.png"_spr,
                                "loochiRight.png"_spr,
                                "loochiFrontAngry.png"_spr,
                                "loochiFrontHappy.png"_spr,
                                "loochiFrontAngry.png"_spr,
                                "loochiLeft.png"_spr,
                                "loochiBack.png"_spr,
                                "loochiRight.png"_spr,
                                "loochiFrontHappy.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiFrontHappy.png"_spr,
                                "loochiFrontCloseup.png"_spr,
                                "loochiFrontAngry.png"_spr,
                                "loochiFrontCloseup.png"_spr,
                                "loochiFrontHappy.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiLeft.png"_spr,
                                "loochiBack.png"_spr,
                                "loochiRight.png"_spr,
                                "loochiFrontAngry.png"_spr,
                                "loochiFrontHappy.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiScream.png"_spr,
                                "loochiFrontHappy.png"_spr,
                                "loochiFrontAngry.png"_spr,
                                "loochiLeft.png"_spr,
                                "loochiBack.png"_spr,
                                "loochiRight.png"_spr,
                                "loochiFrontAngry.png"_spr,
                            }
                        ), "looch.mp3"_spr, true, true, false, 0.5f, 255, callfunc_selector(loochi::FinishedJumpscare), this, false);
                        inJumpscare = true;
                        
                        mainLayer->World->addChild(jumpscare);
                        jumpscare->setPosition({42, 73});
                        jumpscare->setZOrder(20);

                        mainLayer->noiseAmount++;
                    }
                }
            }
            rollForCloseCams = false;
        }
        if (!mainLayer->inCamSys){
            canAppear = false;
            looch->setVisible(false);
        }
    }
    else {
        canAppear = false;
        looch->setVisible(false);
    }
}

void loochi::FinishedJumpscare(){
    inJumpscare = false;
    jumps = false;
    mainLayer->noiseAmount--;
    rollForCloseCams = false;
    if (mainLayer->LookingAtCams){
        canAppear = false;
    }
    prevcamera = mainLayer->currentCamSelected;
}