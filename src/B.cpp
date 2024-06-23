#include "B.h"

B* B::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new B();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool B::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    B1 = CCSprite::create("SmallB.png"_spr);
    B1->setPosition({224, 160});
    B1->setRotationX(3);
    B1->setRotationY(6);
    B1->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.05f, {0, 3}), 1), CCEaseInOut::create(CCMoveBy::create(0.05f, {0, -3}), 1), nullptr)));
    mainLayer->World->addChild(B1);

    B2 = CCSprite::create("SmallB.png"_spr);
    B2->setPosition({140, 71});
    B2->setRotation(-6);
    B2->setScaleX(-1);
    B2->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.05f, {0, 3}), 1), CCEaseInOut::create(CCMoveBy::create(0.05f, {0, -3}), 1), nullptr)));
    mainLayer->World->addChild(B2);

    B3 = CCSprite::create("SmallB.png"_spr);
    B3->setPosition({511, 41});
    B3->setRotationX(6);
    B3->setRotationY(18);
    B3->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.05f, {0, 3}), 1), CCEaseInOut::create(CCMoveBy::create(0.05f, {0, -3}), 1), nullptr)));
    mainLayer->World->addChild(B3);
    
    B4 = CCSprite::create("SmallB.png"_spr);
    B4->setPosition({366, 221});
    B4->setRotationX(13);
    B4->setRotationY(22);
    B4->setScaleX(-1);
    B4->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.05f, {0, 3}), 1), CCEaseInOut::create(CCMoveBy::create(0.05f, {0, -3}), 1), nullptr)));
    mainLayer->World->addChild(B4);

    B5 = CCSprite::create("SmallB.png"_spr);
    B5->setPosition({237, 81});
    B5->setRotationX(24);
    B5->setRotationY(30);
    B5->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.05f, {0, 3}), 1), CCEaseInOut::create(CCMoveBy::create(0.05f, {0, -3}), 1), nullptr)));
    mainLayer->World->addChild(B5);

    B1->setZOrder(2);
    B2->setZOrder(2);
    B3->setZOrder(2);
    B4->setZOrder(2);
    B5->setZOrder(2);

    B1->setVisible(false);
    B2->setVisible(false);
    B3->setVisible(false);
    B4->setVisible(false);
    B5->setVisible(false);

    scheduleUpdate();

    return true;
}

void B::update(float delta){
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

        if (mainLayer->FlashlightOn){
            float previPLevel = progresslevel;
            progresslevel -= delta * 40;

            if (previPLevel > 100 && progresslevel <= 100){
                B1->setVisible(false);
                CCSprite* poof = mainLayer->CreatePoof();
                poof->setPosition(B1->getPosition());
                poof->setZOrder(B1->getZOrder());
                mainLayer->World->addChild(poof);
            }
            if (previPLevel > 200 && progresslevel <= 200){
                B2->setVisible(false);
                CCSprite* poof = mainLayer->CreatePoof();
                poof->setPosition(B2->getPosition());
                poof->setZOrder(B2->getZOrder());
                mainLayer->World->addChild(poof);
            }
            if (previPLevel > 300 && progresslevel <= 300){
                B3->setVisible(false);
                CCSprite* poof = mainLayer->CreatePoof();
                poof->setPosition(B3->getPosition());
                poof->setZOrder(B3->getZOrder());
                mainLayer->World->addChild(poof);
            }
            if (previPLevel > 400 && progresslevel <= 400){
                B4->setVisible(false);
                CCSprite* poof = mainLayer->CreatePoof();
                poof->setPosition(B4->getPosition());
                poof->setZOrder(B4->getZOrder());
                mainLayer->World->addChild(poof);
            }
            if (previPLevel > 500 && progresslevel <= 500){
                B5->setVisible(false);
                CCSprite* poof = mainLayer->CreatePoof();
                poof->setPosition(B5->getPosition());
                poof->setZOrder(B5->getZOrder());
                mainLayer->World->addChild(poof);
            }
        }

        if (progresslevel > 100){
            B1->setVisible(true);
        }
        if (progresslevel > 200){
            B2->setVisible(true);
        }
        if (progresslevel > 300){
            B3->setVisible(true);
        }
        if (progresslevel > 400){
            B4->setVisible(true);
        }
        if (progresslevel > 500){
            B5->setVisible(true);
        }
        if (progresslevel > 600){
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                0.7f, 2, new std::string[]{
                    "BigB.png"_spr,
                    "BigB.png"_spr,
                }
            ), "", false, false, false, 1.5f);
        }
    }
}

void B::OnOpportunity(){
    if (mainLayer->LookingAtCams){
        progresslevel += 1.5f;
    }
}