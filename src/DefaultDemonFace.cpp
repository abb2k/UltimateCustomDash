#include "DefaultDemonFace.h"

DefaultDemonFace* DefaultDemonFace::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new DefaultDemonFace();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool DefaultDemonFace::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    ventFace = CCSprite::create("defaultDemonFaceS.png"_spr);
    ventFace->setZOrder(1);
    ventFace->setPosition({645, 36});
    ventFace->setScale(1.525f);
    ventFace->setVisible(false);
    mainLayer->World->addChild(ventFace);

    officeFace = CCSprite::create("defaultDemonFaceS.png"_spr);
    officeFace->setZOrder(1);
    officeFace->setPosition({221, 91});
    officeFace->setScale(2.375);
    officeFace->setVisible(false);
    mainLayer->World->addChild(officeFace);

    scheduleUpdate();

    return true;
}

void DefaultDemonFace::update(float delta){
    if (mainLayer->NIGHTSTARTED){

        if (mainLayer->LookingAtCams && !inTheRoom && !gottem && !actOnce){
            if (!openCamsLock){
                openCamsLock = true;
                int oppCalc = 1 + (rand() % 22);
                if (_AILevel != 0 && _AILevel >= oppCalc){
                    OnOpportunity();
                }
            }
        }
        else {
            openCamsLock = false;
        }

        if (mainLayer->LookingAtCams){
            actOnce = true;
        }
        else {
            actOnce = false;
        }

        if (inTheRoom){
            if (mainLayer->doorBottomRightClosed){
                if (avoidTimer > 0){
                    avoidTimer -= delta;

                    if (avoidTimer <= 0){
                        avoidTimer = 1;
                        inTheRoom = false;
                        mainLayer->CharacterBlock();
                        ventFace->setVisible(false);
                    }
                }
            }
            else{
                if (killTimer > 0){
                    killTimer -= delta;
                }
                else {
                    inTheRoom = false;
                    gottem = true;
                    ventFace->setVisible(false);
                    officeFace->setVisible(true);
                    mainLayer->effectBlackscreenOpacity = 255;
                    mainLayer->disableFlashlight();
                    mainLayer->canUseFlashlight = false;
                    ventFace->runAction(CCSequence::create(CCDelayTime::create(6), CCCallFunc::create(this, callfunc_selector(DefaultDemonFace::endAttack)), nullptr));
                }
            }
        }
    }
}

void DefaultDemonFace::OnOpportunity(){
    inTheRoom = true;
    killTimer = 5;
    avoidTimer = 1;
    ventFace->setVisible(true);
}

void DefaultDemonFace::endAttack(){
    gottem = false;
    mainLayer->canUseFlashlight = true;
    CCSprite* poof = mainLayer->CreatePoof();
    officeFace->setVisible(false);
    poof->setPosition(officeFace->getPosition());
    poof->setZOrder(poof->getZOrder());
    mainLayer->World->addChild(poof);
    FMODAudioEngine::sharedEngine()->playEffect("pop.mp3"_spr, 1.0f,1.0f,1.0f);
}