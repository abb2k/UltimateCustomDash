#include "AstralD.h"

AstralD* AstralD::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new AstralD();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool AstralD::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    float tMoveBy = 4;
    float tMoveSpeed = 0.1f;

    AstralS = CCSprite::create("ADFACE.png"_spr);
    AstralS->setZOrder(22);
    AstralS->setScale(0.8f);
    AstralS->setPosition({915, mainLayer->office->getPositionY()});
    mainLayer->World->addChild(AstralS);

    mainLayer->PreloadImages(std::vector<std::string>{
        "ADJump0001.png"_spr,
        "ADJump0002.png"_spr,
        "ADJump0003.png"_spr,
        "ADJump0004.png"_spr,
        "ADJump0005.png"_spr,
        "ADJump0006.png"_spr,
        "ADJump0007.png"_spr,
        "ADJump0008.png"_spr,
        "ADJump0009.png"_spr,
        "ADJump0010.png"_spr,
        "ADJump0011.png"_spr,
        "ADJump0012.png"_spr,
        "ADJump0013.png"_spr,
        "ADJump0014.png"_spr,
        "ADJump0015.png"_spr,
        "ADJump0016.png"_spr,
    });

    auto anim = CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(tMoveSpeed, {tMoveBy, 0}), 2), CCEaseInOut::create(CCMoveBy::create(tMoveSpeed, {-tMoveBy, 0}), 2), nullptr));
    AstralS->runAction(anim);

    scheduleUpdate();

    return true;
}

void AstralD::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        AstralS->setVisible(true);
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
                    maskTime = 2.5f;
                    AstralS->stopAllActions();
                    CCPoint pos = {915, mainLayer->office->getPositionY()};
                    AstralS->runAction(CCMoveTo::create(1.5f, pos));
                    stare->RemoveMeAndCleanUpSound();
                    stare = nullptr;
                }
            }
        }
    }
    else {
        AstralS->setVisible(false);
        if (stare != nullptr){
            stare->RemoveMeAndCleanUpSound();
            stare = nullptr;
        }
    }
}

void AstralD::OnOpportunity(){
    InOffice = true;

    AstralS->stopAllActions();
    auto a = CCSequence::create(CCMoveTo::create(5, mainLayer->office->getPosition()), CCCallFunc::create(this, callfunc_selector(AstralD::Flicker)), CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(AstralD::KillPlayer)), nullptr);
    auto f = CCRepeatForever::create(CCSequence::create(CCCallFunc::create(this, callfunc_selector(AstralD::miniflicker)), CCDelayTime::create(0.1f), nullptr));
    f->setTag(82134);

    stare = AudioSource::create("stare.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
    this->addChild(stare);

    AstralS->runAction(a);
    AstralS->runAction(f);
}

void AstralD::miniflicker(){
    mainLayer->effectBlackscreenOpacity = 160;
}

void AstralD::Flicker(){
    CCDirector::sharedDirector()->getActionManager()->pauseTarget(AstralS->getActionByTag(82134));
    mainLayer->FlashEffects(1);
}

void AstralD::KillPlayer(){
    if (mainLayer->NIGHTSTARTED){
        stare->RemoveMeAndCleanUpSound();
        stare = nullptr;
        AstralS->stopAllActions();
        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
            0.02f, 16, new std::string[]{
                "ADJump0001.png"_spr,
                "ADJump0002.png"_spr,
                "ADJump0003.png"_spr,
                "ADJump0004.png"_spr,
                "ADJump0005.png"_spr,
                "ADJump0006.png"_spr,
                "ADJump0007.png"_spr,
                "ADJump0008.png"_spr,
                "ADJump0009.png"_spr,
                "ADJump0010.png"_spr,
                "ADJump0011.png"_spr,
                "ADJump0012.png"_spr,
                "ADJump0013.png"_spr,
                "ADJump0014.png"_spr,
                "ADJump0015.png"_spr,
                "ADJump0016.png"_spr,
            }, 3
        ), "asdv.mp3"_spr, false, false, false);
    }
}