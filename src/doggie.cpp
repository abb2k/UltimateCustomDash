#include "doggie.h"

doggie* doggie::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new doggie();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool doggie::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    Cam05S1 = CCSprite::create("curtensstage2.png"_spr);
    Cam05S1->setScale(2.275f);
    Cam05S1->setZOrder(3);
    Cam05S1->setVisible(false);
    mainLayer->Cam05->addChild(Cam05S1);

    Cam05S1bg = CCSprite::create("curtensstage2bg.png"_spr);
    Cam05S1bg->setScale(2.5f);
    Cam05S1bg->setZOrder(1);
    Cam05S1bg->setVisible(false);
    mainLayer->Cam05->addChild(Cam05S1bg);

    Cam05S2 = CCSprite::create("curtensstage3.png"_spr);
    Cam05S2->setScale(2.275f);
    Cam05S2->setZOrder(6);
    Cam05S2->setVisible(false);
    mainLayer->Cam05->addChild(Cam05S2);

    Cam05S2bg = CCSprite::create("curtensstage3bg.png"_spr);
    Cam05S2bg->setScale(2.5f);
    Cam05S2bg->setZOrder(4);
    Cam05S2bg->setVisible(false);
    mainLayer->Cam05->addChild(Cam05S2bg);

    _doggie = CCSprite::create("doggie.png"_spr);
    _doggie->setScale(2);
    _doggie->setVisible(false);
    mainLayer->Cam05->addChild(_doggie);

    scheduleUpdate();

    return true;
}

void doggie::update(float delta){
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
    if (mainLayer->NIGHTSTARTED){
        if (progression < 100){
            if (!pulse){
                pulse = true;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera05){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam05S1->setVisible(false);
            Cam05S1bg->setVisible(false);
            Cam05S2->setVisible(false);
            Cam05S2bg->setVisible(false);
            _doggie->setVisible(false);
        }
        else if (progression >= 100 && progression < 200){
            if (pulse){
                pulse = false;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera05){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam05S1->setVisible(true);
            Cam05S1bg->setVisible(true);
            _doggie->setVisible(true);
            _doggie->setZOrder(2);
            _doggie->setPosition({-95, -22});
        }
        else if (progression >= 200 && progression < 300){
            if (!pulse){
                pulse = true;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera05){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam05S2->setVisible(true);
            Cam05S2bg->setVisible(true);
            _doggie->setZOrder(5);
            _doggie->setPosition({-66, -45});
        }
        else if (progression >= 300 && progression < 400){
            if (pulse){
                pulse = false;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera05){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            _doggie->setZOrder(7);
            _doggie->setPosition({-150, -120});
            _doggie->setRotationY(-180);
        }
        else if (progression >= 400){
            if (!pulse){
                pulse = true;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera05){
                    mainLayer->CamStaticOpacity = 255;
                }
                FMODAudioEngine::sharedEngine()->playEffect("Runing.mp3"_spr, 1.0f,1.0f,1.0f);
            }
            _doggie->setVisible(false);
            if (reachDoor > 0){
                reachDoor -= delta;
            }
            else{
                if (!knock){
                    knock = true;
                    cnocksound = AudioSource::create("DoorPoundingMe.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
                    this->addChild(cnocksound);
                }
                if (doorWaitTime > 0){
                    doorWaitTime -= delta;
                    if (!mainLayer->doorLeftClosed){
                        if (!killp){
                            killp = true;
                            cnocksound->RemoveMeAndCleanUpSound();
                            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                                0.7f, 2, new std::string[]{
                                    "doggie.png"_spr,
                                    "doggie.png"_spr,
                                }
                            ), "", false, false, false, 7);
                        }
                    }
                }
                else{
                    progression = 0;
                    doorWaitTime = 3;
                    pulse = false;
                    cnocksound->RemoveMeAndCleanUpSound();
                    knock = false;
                    _doggie->setRotationY(0);
                    reachDoor = 1;
                    mainLayer->CharacterBlock();
                }
            }
        }
    }
}

void doggie::OnOpportunity(){
    if (mainLayer->currentCamSelected != CNGameLayer::Cameras::Camera05){
        progression++;
    }
    else{
        if (!mainLayer->LookingAtCams){
            progression++;
        }
    }
}