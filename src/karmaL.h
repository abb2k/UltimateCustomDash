#pragma once
#include <include.h>
#include "CNGameLayer.h"

class karmaL : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static karmaL* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    int _AILevel;

    bool canKill;
    bool awake;
    bool rollWakeChance;
    bool oneFlashLock;

    CCSprite* Awake;
    CCSprite* asleep;

    void OnOpportunity();
};