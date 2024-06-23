#pragma once
#include <include.h>
#include "CNGameLayer.h"

class doggie : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static doggie* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    float progression = 0;

    float reachDoor = 1;

    float doorWaitTime = 3;

    AudioSource* cnocksound;

    bool pulse = false;
    bool knock = false;
    bool killp;

    CCSprite* Cam05S1;
    CCSprite* Cam05S1bg;

    CCSprite* Cam05S2;
    CCSprite* Cam05S2bg;

    CCSprite* _doggie;
};