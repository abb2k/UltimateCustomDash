#pragma once
#include <include.h>
#include "CNGameLayer.h"

class B : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static B* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* B1;
    CCSprite* B2;
    CCSprite* B3;
    CCSprite* B4;
    CCSprite* B5;

    float progresslevel = 0;
};