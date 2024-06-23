#include "technical.h"

technical* technical::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new technical();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool technical::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    float bMoveBy = 6;
    float bMoveSpeed = 0.06f;

    float tMoveBy = 4;
    float tMoveSpeed = 0.1f;

    techS = CCNode::create();
    techS->setZOrder(22);
    techS->setScale(0.8f);
    techS->setPosition({-260, mainLayer->office->getPositionY()});
    mainLayer->World->addChild(techS);

    CCSprite* faceTop = CCSprite::create("technicalFaceTop.png"_spr);
    faceTop->setPositionX(faceTop->getPositionX() - (tMoveBy / 2));
    techS->addChild(faceTop);

    CCSprite* faceBottom = CCSprite::create("technicalFaceBottom.png"_spr);
    faceBottom->setPositionY(faceBottom->getPositionY() - (bMoveBy / 2));
    techS->addChild(faceBottom);

    auto bottomAnim = CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(bMoveSpeed, {0, bMoveBy}), 2), CCEaseInOut::create(CCMoveBy::create(bMoveSpeed, {0, -bMoveBy}), 2), nullptr));
    auto topAnim = CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(tMoveSpeed, {tMoveBy, 0}), 2), CCEaseInOut::create(CCMoveBy::create(tMoveSpeed, {-tMoveBy, 0}), 2), nullptr));

    faceBottom->runAction(bottomAnim);
    faceBottom->runAction(topAnim);
    faceTop->runAction(topAnim);

    mainLayer->PreloadImages(std::vector<std::string>{
        "techJ0001.png"_spr,
        "techJ0002.png"_spr,
        "techJ0003.png"_spr,
        "techJ0004.png"_spr,
        "techJ0005.png"_spr,
        "techJ0006.png"_spr,
        "techJ0007.png"_spr,
        "techJ0008.png"_spr,
        "techJ0009.png"_spr,
        "techJ0010.png"_spr,
        "techJ0011.png"_spr,
        "techJ0012.png"_spr,
        "techJ0013.png"_spr,
        "techJ0014.png"_spr,
        "techJ0015.png"_spr,
        "techJ0016.png"_spr,
        "techJ0017.png"_spr,
        "techJ0018.png"_spr,
        "techJ0019.png"_spr,
        "techJ0020.png"_spr,
        "techJ0021.png"_spr,
        "techJ0022.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void technical::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        techS->setVisible(true);
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
        if (InOffice){
            if (mainLayer->InMask){
                if (maskTime > 0){
                    maskTime -= delta;
                }
                else {
                    InOffice = false;
                    maskTime = 2;
                    techS->stopAllActions();
                    CCPoint pos = {-260, mainLayer->office->getPositionY()};
                    techS->runAction(CCMoveTo::create(1.5f, pos));
                    stare->RemoveMeAndCleanUpSound();
                    stare = nullptr;
                }
            }
        }
    }
    else {
        techS->setVisible(false);
        if (stare != nullptr){
            stare->RemoveMeAndCleanUpSound();
            stare = nullptr;
        }
    }
}

void technical::OnOpportunity(){
    InOffice = true;

    techS->stopAllActions();
    auto a = CCSequence::create(CCMoveTo::create(5, mainLayer->office->getPosition()), CCCallFunc::create(this, callfunc_selector(technical::Flicker)), CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(technical::KillPlayer)), nullptr);
    auto f = CCRepeatForever::create(CCSequence::create(CCCallFunc::create(this, callfunc_selector(technical::miniflicker)), CCDelayTime::create(0.1f), nullptr));
    f->setTag(82134);

    stare = AudioSource::create("stare.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
    this->addChild(stare);

    techS->runAction(a);
    techS->runAction(f);
}

void technical::miniflicker(){
    mainLayer->effectBlackscreenOpacity = 160;
}

void technical::Flicker(){
    CCDirector::sharedDirector()->getActionManager()->pauseTarget(techS->getActionByTag(82134));
    mainLayer->FlashEffects(1);
}

void technical::KillPlayer(){
    if (mainLayer->NIGHTSTARTED){
        stare->RemoveMeAndCleanUpSound();
        techS->stopAllActions();
        stare = nullptr;
        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
            0.03f, 27, new std::string[]{
                "techJ0001.png"_spr,
                "techJ0002.png"_spr,
                "techJ0003.png"_spr,
                "techJ0004.png"_spr,
                "techJ0005.png"_spr,
                "techJ0006.png"_spr,
                "techJ0007.png"_spr,
                "techJ0008.png"_spr,
                "techJ0009.png"_spr,
                "techJ0010.png"_spr,
                "techJ0011.png"_spr,
                "techJ0012.png"_spr,
                "techJ0013.png"_spr,
                "techJ0014.png"_spr,
                "techJ0014.png"_spr,
                "techJ0015.png"_spr,
                "techJ0016.png"_spr,
                "techJ0017.png"_spr,
                "techJ0018.png"_spr,
                "techJ0019.png"_spr,
                "techJ0020.png"_spr,
                "techJ0020.png"_spr,
                "techJ0021.png"_spr,
                "techJ0022.png"_spr,
                "techJ0021.png"_spr,
                "techJ0020.png"_spr,
                "techJ0019.png"_spr,
            }
        ), "techLESGO.mp3"_spr, false, false, false);
    }
}