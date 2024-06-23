#pragma once
#include <include.h>
#include "CNGameLayer.h"

class riot : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static riot* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    bool pulse = false;
    bool killp;

    CCSprite* Cam06S1;
    CCSprite* Cam06Sbg;

    CCSprite* Cam06S2;

    CCSprite* Cam06S3;

    CCSprite* _riot;

    float progression = 0;

    CCSize originalCSize;
};