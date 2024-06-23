#include "robtop.h"

robtop* robtop::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new robtop();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool robtop::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    opportunityTimer = 0.5f;
    _AILevel = AILevel;

    jumpscareTimer = 2 + (rand() % 6);

    mainLayer->PreloadImages(std::vector<std::string>{
        "robJ0001.png"_spr,
        "robJ0002.png"_spr,
        "robJ0003.png"_spr,
        "robJ0004.png"_spr,
        "robJ0005.png"_spr,
        "robJ0006.png"_spr,
        "robJ0007.png"_spr,
        "robJ0008.png"_spr,
        "robJ0009.png"_spr,
        "robJ0010.png"_spr,
        "robJ0011.png"_spr,
        "robJ0012.png"_spr,
        "robJ0013.png"_spr,
        "robJ0014.png"_spr,
        "robJ0015.png"_spr,
        "robJ0016.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void robtop::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (opportunityTimer > 0){
            opportunityTimer -= delta;
        }
        else{
            opportunityTimer = 0.5f;
            OnOpportunity();
        }
        mainLayer->boxWindBar->setScaleX(wind / 100);

        if (mainLayer->musicBoxCont->isVisible()){
            if (mainLayer->musicBoxCont->getChildrenCount() <= 4){
                if (mainLayer->getHoldOn(mainLayer->windBoxOff)){
                    mainLayer->windBoxOff->setVisible(false);
                    mainLayer->windBoxOn->setVisible(true);
                    if (mainLayer->boxChargeMinitimer > 0){
                        mainLayer->boxChargeMinitimer -= delta;
                    }
                    else {
                        mainLayer->boxChargeMinitimer = 0.35f;
                        FMODAudioEngine::sharedEngine()->playEffect("windup.mp3"_spr, 1.0f,1.0f,1.0f);
                        if (wind < 100){
                            wind += 10;

                            if (wind >= 100){
                                wind = 100;
                            }
                        }
                    }
                    holding = true;
                }
                else {
                    mainLayer->windBoxOff->setVisible(true);
                    mainLayer->windBoxOn->setVisible(false);
                    holding = false;
                }
            }
            else {
                mainLayer->windBoxOff->setVisible(true);
                mainLayer->windBoxOn->setVisible(false);
                holding = false;
            }
        }
        if (Escaped){
            if (jumpscareTimer > 0){
                jumpscareTimer -= delta;
            }
            else{
                Escaped = false;
                jumpscareTimer = 1000;
                music->removeMeAndCleanup();
                music = nullptr;
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    0.032f, 16, new std::string[]{
                        "robJ0001.png"_spr,
                        "robJ0002.png"_spr,
                        "robJ0003.png"_spr,
                        "robJ0004.png"_spr,
                        "robJ0005.png"_spr,
                        "robJ0006.png"_spr,
                        "robJ0007.png"_spr,
                        "robJ0008.png"_spr,
                        "robJ0009.png"_spr,
                        "robJ0010.png"_spr,
                        "robJ0011.png"_spr,
                        "robJ0012.png"_spr,
                        "robJ0013.png"_spr,
                        "robJ0014.png"_spr,
                        "robJ0015.png"_spr,
                        "robJ0016.png"_spr,
                    }, 2
                ), "explode_11.mp3"_spr, false, false, false);
            }
        } 
    }
    if (mainLayer->DEATHSCREEN || mainLayer->inJumpscare || mainLayer->nightComplete){
        if (music != nullptr){
            music->removeMeAndCleanup();
            music = nullptr;
        }
    }
}

void robtop::OnOpportunity(){
    if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::GMB){
        if (wind < 100){
            wind += 4;

            if (wind >= 100){
                wind = 100;
            }
        }
    }
    else if (!holding) {
        if (wind > 0){
            wind -= 0.2f * _AILevel;

            if (wind <= 0 && !Escaped){
                wind = 0;
                Escaped = true;
                mainLayer->fastVentelation = true;
                if (music == nullptr){
                    music = AudioSource::create("jackinthebox.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::VolumeChannel::Music);
                    this->addChild(music);
                }
            }
        }
        else if (!Escaped){
            if (music == nullptr){
                music = AudioSource::create("jackinthebox.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::VolumeChannel::Music);
                this->addChild(music);
            }
            mainLayer->fastVentelation = true;
            wind = 0;
            Escaped = true;
        }
    }
}