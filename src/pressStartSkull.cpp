#include "pressStartSkull.h"

pressStartSkull* pressStartSkull::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new pressStartSkull();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool pressStartSkull::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    skullCont = CCNode::create();
    skullCont->setZOrder(14);
    mainLayer->World->addChild(skullCont);

    upperSkull = CCSprite::create("pressStartSkullTop.png"_spr);
    skullCont->addChild(upperSkull);

    lowerSkull = CCSprite::create("pressStartSkullBottom.png"_spr);
    skullCont->setVisible(false);
    skullCont->addChild(lowerSkull);

    auto PosOpen = CCMoveTo::create(0.75f, {2, -12});
    auto PosClosed = CCMoveTo::create(0.4f, {-11, 23});

    auto animation = CCRepeatForever::create(CCSequence::create(CCEaseOut::create(PosOpen, 2), CCEaseBounceOut::create(PosClosed), nullptr));
    lowerSkull->runAction(animation);

    scheduleUpdate();

    return true;
}

void pressStartSkull::update(float delta){
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
        skullCont->setPosition({mainLayer->desk->getPositionX(), mainLayer->desk->getPositionY() + 50});

        if (alreadyIn){
            if (mainLayer->InMask){
                if (maskForTime > 0){
                    maskForTime -= delta;
                }
                else{
                    alreadyIn = false;
                    music->RemoveMeAndCleanUpSound();
                    skullCont->setVisible(false);
                    mainLayer->removeFromFlashEffects(insideTimer);
                }
            }
            if (insideTimer > 0){
                insideTimer -= delta;
            }
            else{
                if (!killp){
                    killp = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "pressStartSkull.png"_spr,
                            "pressStartSkull.png"_spr,
                        }
                    ), "", false, false, false, 7);
                    skullCont->setVisible(false);
                }
            }
        }
    }
}

void pressStartSkull::OnOpportunity(){
    if (!alreadyIn){
        alreadyIn = true;
        skullCont->setVisible(true);
        music = AudioSource::create("pressStart.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
        this->addChild(music);
        insideTimer = 4;
        maskForTime = 0.1f * _AILevel;
        mainLayer->FlashEffects(4);
    }
}