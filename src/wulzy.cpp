#include "wulzy.h"

wulzy* wulzy::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new wulzy();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool wulzy::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    woahSound = AudioSource::create("silence.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
    this->addChild(woahSound);

    scheduleUpdate();

    return true;
}

void wulzy::update(float delta){
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
        if (Attaking){
            if (onRight){
                if (mainLayer->doorRightClosed){
                    avoidTimer -= delta;
                }
            }
            else {
                if (mainLayer->doorLeftClosed){
                    avoidTimer -= delta;
                }
            }

            if (avoidTimer < 0){
                Attaking = false;
                shouldHaveKilled = false;
                mainLayer->CharacterBlock();
            }
        }

        if (shouldHaveKilled){
            if (onRight){
                if (!mainLayer->doorRightClosed){
                    if (!killplayer){
                    killplayer = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "wulzy.png"_spr,
                            "wulzy.png"_spr,
                        }
                    ), "", false, false, false, 7);
                    }
                }
            }
            else {
                if (!mainLayer->doorLeftClosed){
                    if (!killplayer){
                    killplayer = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "wulzy.png"_spr,
                            "wulzy.png"_spr,
                        }
                    ), "", false, false, false, 7);
                    }
                }
            }
        }
    }
}

void wulzy::OnOpportunity(){
    if (!Attaking){
        Attaking = true;
        avoidTimer = 1;

        int randomnum = rand() % 2;

        if (randomnum == 0){
            onRight = true;
            woahSound->changeSound("WOAHRight.mp3"_spr, FMOD_DEFAULT);
        }
        else {
            onRight = false;
            woahSound->changeSound("WOAHLeft.mp3"_spr, FMOD_DEFAULT);
        }
    }
    else {
        if (onRight){
            if (mainLayer->doorRightClosed){
                shouldHaveKilled = true;
            }
            else {
                if (!killplayer){
                    killplayer = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "wulzy.png"_spr,
                            "wulzy.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }
            }
        }
        else {
            if (mainLayer->doorLeftClosed){
                shouldHaveKilled = true;
            }
            else {
                if (!killplayer){
                    killplayer = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "wulzy.png"_spr,
                            "wulzy.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }
            }
        }
    }
}