#include "deadlockedMonsters.h"

deadlockedMonsters* deadlockedMonsters::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new deadlockedMonsters();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool deadlockedMonsters::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    OverallCont = CCNode::create();
    OverallCont->setZOrder(42);
    OverallCont->setPosition({-149, 70});
    OverallCont->setVisible(false);
    mainLayer->Canvas->addChild(OverallCont);

    CCSprite* bg = CCSprite::create("monstersMinigame.png"_spr);
    bg->setScaleX(1.2f);
    OverallCont->addChild(bg);

    PlusHitbox = CCNode::create();
    PlusHitbox->setPosition({-2, -25});
    PlusHitbox->setContentSize({6, 5});
    OverallCont->addChild(PlusHitbox);

    Monster1 = createMonster(true);
    Monster1->setScale(0.25f);
    OverallCont->addChild(Monster1);

    Monster2 = createMonster(true);
    Monster2->setScale(0.25f);
    OverallCont->addChild(Monster2);

    Monster3 = createMonster(true);
    Monster3->setScale(0.25f);
    OverallCont->addChild(Monster3);

    Mcont1 = createMonster(false);
    Mcont1->setPosition(Monster1->getContentSize() / 2);
    Monster1->addChild(Mcont1);

    Mcont2 = createMonster(false);
    Mcont2->setPosition(Monster2->getContentSize() / 2);
    Monster2->addChild(Mcont2);

    Mcont3 = createMonster(false);
    Mcont3->setPosition(Monster3->getContentSize() / 2);
    Monster3->addChild(Mcont3);

    scheduleUpdate();

    return true;
}

void deadlockedMonsters::update(float delta){
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
        if (mainLayer->clickingC){
            if (!CClickLock){
                CClickLock = true;
                if (appeared){
                    if (mainLayer->getHoverOnOther(PlusHitbox, Monster1) && Mcont1->isVisible()){
                        Mcont1->setVisible(false);
                        FMODAudioEngine::sharedEngine()->playEffect("fish4.mp3"_spr, 1.0f,1.0f,1.0f);
                        wins++;
                    }
                    else if (mainLayer->getHoverOnOther(PlusHitbox, Monster2) && Mcont2->isVisible()){
                        Mcont2->setVisible(false);
                        FMODAudioEngine::sharedEngine()->playEffect("fish4.mp3"_spr, 1.0f,1.0f,1.0f);
                        wins++;
                    }
                    else if (mainLayer->getHoverOnOther(PlusHitbox, Monster3) && Mcont3->isVisible()){
                        Mcont3->setVisible(false);
                        FMODAudioEngine::sharedEngine()->playEffect("fish4.mp3"_spr, 1.0f,1.0f,1.0f);
                        wins++;
                    }
                    else {
                        fails++;
                        FMODAudioEngine::sharedEngine()->playEffect("chomp.mp3"_spr, 1.0f,1.0f,1.0f);
                    }
                }
            }
        }
        else{
            CClickLock = false;
        }
        if (appeared && fails >= 3){
            // fail game (fail too much)
            fails = 0;
            wins = 0;
            appeared = false;
            failCool = true;
            mainLayer->blockDoorUsage = true;
            OverallCont->setVisible(false);
            Monster1->stopAllActions();
            Monster2->stopAllActions();
            Monster3->stopAllActions();
            OverallCont->runAction(CCRepeat::create(CCSequence::create(CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::playFailSound)), CCDelayTime::create(0.2f), nullptr), 2));
        }
        if (appeared && wins >= 3){
            //win game (catch all fish)
            appeared = false;
            fails = 0;
            wins = 0;
            OverallCont->setVisible(false);
            Monster1->stopAllActions();
            Monster2->stopAllActions();
            Monster3->stopAllActions();
        }
        if (failCool){
            if (FailPanishmentCool > 0){
                FailPanishmentCool -= delta;
            }
            else {
                FailPanishmentCool = 7;
                failCool = false;
                mainLayer->blockDoorUsage = false;
            }
        }
    }
}

void deadlockedMonsters::OnOpportunity(){
    if (!appeared){
        if (!failCool){
            appeared = true;
            OverallCont->setVisible(true);
            Mcont1->setVisible(true);
            Mcont2->setVisible(true);
            Mcont3->setVisible(true);

            float speed1 = 0.8f + mainLayer->randomFloat(0, 1);
            float speed2 = 0.8f + mainLayer->randomFloat(0, 1);
            float speed3 = 0.8f + mainLayer->randomFloat(0, 1);

            Monster1->setPosition({58, -20});
            Mcont1->setScaleX(1);
            Monster2->setPosition({-58, -20});
            Mcont2->setScaleX(-1);
            Monster3->setPosition({58, -20});
            Mcont3->setScaleX(1);

            auto m1A = CCRepeatForever::create(CCSequence::create(CCMoveTo::create(speed1, {-58, -20}), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::flipM1Right)), CCMoveTo::create(speed1, {58, -20}), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::flipM1Left)), nullptr));
            m1A->setTag(132421);
            auto m2A = CCRepeatForever::create(CCSequence::create(CCMoveTo::create(speed2, {58, -20}), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::flipM2Left)), CCMoveTo::create(speed2, {-58, -20}), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::flipM2Right)), nullptr));
            m2A->setTag(132421);
            auto m3A = CCRepeatForever::create(CCSequence::create(CCMoveTo::create(speed3, {-58, -20}), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::flipM3Right)), CCMoveTo::create(speed3, {58, -20}), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::flipM3Left)), nullptr));
            m3A->setTag(132421);

            auto Sound = CCRepeatForever::create(CCSequence::create(CCDelayTime::create(0.3f), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::playBGSound)), nullptr));
            Sound->setTag(132421);

            Monster1->runAction(m1A);
            Monster1->runAction(Sound);
            Monster2->runAction(m2A);
            Monster3->runAction(m3A);
        }
    }
    else{
        // fail game (take too long)
        appeared = false;
        failCool = true;
        OverallCont->setVisible(false);
        fails = 0;
        mainLayer->blockDoorUsage = true;
        wins = 0;
        Monster1->stopAllActions();
        Monster2->stopAllActions();
        Monster3->stopAllActions();
        playFailSound();
        OverallCont->runAction(CCRepeat::create(CCSequence::create(CCDelayTime::create(0.2f), CCCallFunc::create(this, callfunc_selector(deadlockedMonsters::playFailSound)), nullptr), 2));
    }
}

CCNode* deadlockedMonsters::createMonster(bool invis){
    CCNode* mainN = CCNode::create();
    mainN->setAnchorPoint({0.5f,0.5f});

    float moveTime = 0.25f;
    float easeTime = 2;

    CCNode* BottomPvot = CCNode::create();
    BottomPvot->setPosition({60, 33});
    mainN->addChild(BottomPvot);

    BottomPvot->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCRotateTo::create(moveTime, -20), easeTime), CCEaseInOut::create(CCRotateTo::create(moveTime, 0), easeTime), nullptr)));

    CCSprite* bottom = CCSprite::create("dMonstBottom.png"_spr);
    bottom->setPosition({-26, -16});
    BottomPvot->addChild(bottom);

    CCNode* TopPvot = CCNode::create();
    TopPvot->setPosition({60, 33});
    mainN->addChild(TopPvot);

    TopPvot->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCRotateTo::create(moveTime, 20), easeTime), CCEaseInOut::create(CCRotateTo::create(moveTime, 0), easeTime), nullptr)));

    CCSprite* top = CCSprite::create("dMonstTop.png"_spr);
    top->setPosition({-25, 4});
    TopPvot->addChild(top);

    if (invis){
        top->setOpacity(0);
        bottom->setOpacity(0);
    }

    mainN->setContentSize({70, 55});

    return mainN;
}

void deadlockedMonsters::flipM1Right(){
    Mcont1->setScaleX(-1);
}
void deadlockedMonsters::flipM1Left(){
    Mcont1->setScaleX(1);
}

void deadlockedMonsters::flipM2Right(){
    Mcont2->setScaleX(-1);
}
void deadlockedMonsters::flipM2Left(){
    Mcont2->setScaleX(1);
}

void deadlockedMonsters::flipM3Right(){
    Mcont3->setScaleX(-1);
}
void deadlockedMonsters::flipM3Left(){
    Mcont3->setScaleX(1);
}
void deadlockedMonsters::playBGSound(){
    FMODAudioEngine::sharedEngine()->playEffect("fish3.mp3"_spr, 1.0f,1.0f,1.0f);
}

void deadlockedMonsters::playFailSound(){
    FMODAudioEngine::sharedEngine()->playEffect("chomp.mp3"_spr, 1.0f,1.0f,1.0f);
}