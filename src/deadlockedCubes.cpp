#include "deadlockedCubes.h"

deadlockedCubes* deadlockedCubes::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new deadlockedCubes();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool deadlockedCubes::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    cube1 = CCSprite::create("deadlockedCubee.png"_spr);
    cube1->setZOrder(40);
    cube1->setPosition({175, 80});
    cube1->setScale(0.7f);
    mainLayer->Canvas->addChild(cube1);

    cube2 = CCSprite::create("deadlockedCubee.png"_spr);
    cube2->setZOrder(40);
    cube2->setPosition({0, -80});
    cube2->setScale(0.7f);
    mainLayer->Canvas->addChild(cube2);

    cube3 = CCSprite::create("deadlockedCubee.png"_spr);
    cube3->setZOrder(40);
    cube3->setPosition({-175, 80});
    cube3->setScale(0.7f);
    mainLayer->Canvas->addChild(cube3);

    float movementTime = 0.6f;
    float easeTime = 2.5f;

    auto cube1moveUp = CCMoveTo::create(movementTime, {175, 80});
    auto cube1moveDown = CCMoveTo::create(movementTime, {175, -80});
    auto cube1Anim = CCSequence::create(CCEaseInOut::create(cube1moveDown, easeTime), CCEaseInOut::create(cube1moveUp, easeTime), nullptr);
    auto cube1Action = CCRepeatForever::create(cube1Anim);
    cube1->runAction(cube1Action);

    auto cube2moveUp = CCMoveTo::create(movementTime, {0, 80});
    auto cube2moveDown = CCMoveTo::create(movementTime, {0, -80});
    auto cube2Anim = CCSequence::create(CCEaseInOut::create(cube2moveUp, easeTime), CCEaseInOut::create(cube2moveDown, easeTime), nullptr);
    auto cube2Action = CCRepeatForever::create(cube2Anim);
    cube2->runAction(cube2Action);

    auto cube3moveUp = CCMoveTo::create(movementTime, {-175, 80});
    auto cube3moveDown = CCMoveTo::create(movementTime, {-175, -80});
    auto cube3Anim = CCSequence::create(CCEaseInOut::create(cube3moveDown, easeTime), CCEaseInOut::create(cube3moveUp, easeTime), nullptr);
    auto cube3Action = CCRepeatForever::create(cube3Anim);
    cube3->runAction(cube3Action);

    cube1->setVisible(false);
    cube2->setVisible(false);
    cube3->setVisible(false);
    cube1->setOpacity(0);
    cube2->setOpacity(0);
    cube3->setOpacity(0);

    scheduleUpdate();

    return true;
}

void deadlockedCubes::update(float delta){
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
        cube1->setVisible(true);
        cube2->setVisible(true);
        cube3->setVisible(true);
    }
    else{
        cube1->setVisible(false);
        cube2->setVisible(false);
        cube3->setVisible(false);

        if (jumpSound != nullptr){
            jumpSound->RemoveMeAndCleanUpSound();
            jumpSound = nullptr;
        }
    }
}

void deadlockedCubes::OnOpportunity(){

    cube1->setOpacity(255);
    cube2->setOpacity(255);
    cube3->setOpacity(255);

    if (jumpSound != nullptr){
        jumpSound->RemoveMeAndCleanUpSound();
    }

    jumpSound = AudioSource::create("Deadlocked.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
    this->addChild(jumpSound);

    auto cube1fadeout = CCSequence::create(CCDelayTime::create(3.5f), CCFadeOut::create(0.5f), nullptr);
    auto cube2fadeout = CCSequence::create(CCDelayTime::create(3.5f), CCFadeOut::create(0.5f), nullptr);
    auto cube3fadeout = CCSequence::create(CCDelayTime::create(3.5f), CCFadeOut::create(0.5f), nullptr);

    cube1->runAction(cube1fadeout);
    cube2->runAction(cube2fadeout);
    cube3->runAction(cube3fadeout);
}