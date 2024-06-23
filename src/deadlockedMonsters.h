#pragma once
#include <include.h>
#include "CNGameLayer.h"

class deadlockedMonsters : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static deadlockedMonsters* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCNode* OverallCont;

    CCNode* PlusHitbox;

    bool CClickLock;

    CCNode* Monster1;
    CCNode* Monster2;
    CCNode* Monster3;

    CCNode* Mcont1;
    CCNode* Mcont2;
    CCNode* Mcont3;

    CCNode* createMonster(bool invis);

    bool appeared;
    bool failCool;

    float FailPanishmentCool = 7;

    int fails;
    int wins;

    void flipM1Right();
    void flipM1Left();
    void flipM2Right();
    void flipM2Left();
    void flipM3Right();
    void flipM3Left();

    void playBGSound();
    void playFailSound();
};