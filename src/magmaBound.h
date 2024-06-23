#pragma once
#include <include.h>
#include "CNGameLayer.h"

class magmaBound : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static magmaBound* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    CNGameLayer::ventPosition Position;

    CCSprite* icon;

    CCSprite* ventFace;

    float _opportunity;

    bool killplayer;

    float opportunityTimer;

    bool enteredFVent;

    float PreventTime = 1;

    float killtimer = 4;

    int _AILevel;

    void OnOpportunity();
};