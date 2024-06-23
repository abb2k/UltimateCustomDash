#include "SHSnowman.h"

SHSnowman* SHSnowman::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new SHSnowman();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SHSnowman::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    snowman = CCSprite::create("SHSnowman.png"_spr);
    snowman->setScale(4);
    mainLayer->cameraOverallUI->addChild(snowman);

    scheduleUpdate();

    return true;
}

void SHSnowman::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (prevcamera != mainLayer->currentCamSelected){
            prevcamera = mainLayer->currentCamSelected;
            if (!canAppear){
                int oppCalc = 1 + (rand() % 21);
                if (_AILevel != 0 && _AILevel >= oppCalc){
                    canAppear = true;
                    snowman->setVisible(true);
                    snowman->setZOrder(-5);

                    looktimer = 3 - (0.1f * _AILevel);

                    int randomPos = rand() % 3;

                    if (randomPos == 0){
                        snowman->setPosition({-146, -21});
                        snowman->setRotationX(32);
                        snowman->setRotationY(45);
                    }
                    else if (randomPos == 1){
                        snowman->setPosition({109, 81});
                        snowman->setRotationX(202);
                        snowman->setRotationY(202);
                    }
                    else if (randomPos == 2){
                        snowman->setPosition({125, -74});
                        snowman->setRotationX(370);
                        snowman->setRotationY(377);
                    }
                }
            }
        }
        if (!mainLayer->LookingAtCams){
            if (!rollForCloseCams){
                int oppCalc = 1 + (rand() % 22);
                if (_AILevel != 0 && _AILevel >= oppCalc){
                    canAppear = true;
                    snowman->setVisible(true);
                    snowman->setZOrder(-5);
                    
                    looktimer = 3 - (0.1f * _AILevel);

                    int randomPos = rand() % 3;

                    if (randomPos == 0){
                        snowman->setPosition({-146, -21});
                        snowman->setRotationX(32);
                        snowman->setRotationY(45);
                    }
                    else if (randomPos == 1){
                        snowman->setPosition({109, 81});
                        snowman->setRotationX(202);
                        snowman->setRotationY(202);
                    }
                    else if (randomPos == 2){
                        snowman->setPosition({125, -74});
                        snowman->setRotationX(370);
                        snowman->setRotationY(377);
                    }
                }
                else {
                    canAppear = false;
                    snowman->setVisible(false);
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
                            0.8f, 2, new std::string[]{
                                "SHSnowman.png"_spr,
                                "SHSnowman.png"_spr,
                            }
                        ), "boom2.mp3"_spr, true, true, false, 7.3f);

                        jumpscare->setRotation(45);
                    }
                }
            }
            rollForCloseCams = false;
        }
        if (!mainLayer->inCamSys){
            canAppear = false;
            snowman->setVisible(false);
        }
    }
    else {
        canAppear = false;
        snowman->setVisible(false);
    }
}