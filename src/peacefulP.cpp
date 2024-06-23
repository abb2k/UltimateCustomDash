#include "peacefulP.h"

peacefulP* peacefulP::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new peacefulP();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool peacefulP::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    frame1 = CCSprite::create("pf1.png"_spr);
    frame1->setZOrder(43);
    frame1->setVisible(false);
    frame1->setScale(1.2f);
    mainLayer->Canvas->addChild(frame1);

    frame2 = CCSprite::create("pf2.png"_spr);
    frame2->setZOrder(43);
    frame2->setVisible(false);
    frame2->setScale(1.2f);
    mainLayer->Canvas->addChild(frame2);

    frame3 = CCSprite::create("pf3.png"_spr);
    frame3->setZOrder(43);
    frame3->setVisible(false);
    frame3->setScale(1.2f);
    mainLayer->Canvas->addChild(frame3);

    mainLayer->PreloadImages(std::vector<std::string>{
        "pf1.png"_spr,
        "pf2.png"_spr,
        "pf3.png"_spr
    });

    scheduleUpdate();

    return true;
}

void peacefulP::update(float delta){
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

        if (mainLayer->enterClicked){
            if (!enterLock){
                enterLock = true;
                if (displaying){
                    displaying = false;
                    frame1->setVisible(false);
                    frame2->setVisible(false);
                    frame3->setVisible(false);
                    FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr, 1.0f,1.0f,1.0f);
                    music->RemoveMeAndCleanUpSound();
                    music = nullptr;
                }
            }
        }
        else {
            enterLock = false;
        }
    }
    if (mainLayer->DEATHSCREEN || mainLayer->inJumpscare || mainLayer->nightComplete){
        if (music != nullptr){
            music->removeMeAndCleanup();
            music = nullptr;
        }
    }
}

void peacefulP::OnOpportunity(){
    if (!displaying){
        displaying = true;

        int randomF = rand() % 3;
        switch (randomF)
        {
        case 0:
            frame1->setVisible(true);
            break;

        case 1:
            frame2->setVisible(true);
            break;

        case 2:
            frame3->setVisible(true);
            break;
        }

        music = AudioSource::create("Peaceful.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::VolumeChannel::SFX);
        this->addChild(music);
    }
    else {
        displaying = false;
        frame1->setVisible(false);
        frame2->setVisible(false);
        frame3->setVisible(false);
        FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr, 1.0f,1.0f,1.0f);
        music->RemoveMeAndCleanUpSound();
        music = nullptr;
    }
}