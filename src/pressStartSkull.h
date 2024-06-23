#pragma once
#include <include.h>
#include "CNGameLayer.h"

class pressStartSkull : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static pressStartSkull* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* upperSkull;
    CCSprite* lowerSkull;

    CCNode* skullCont;

    AudioSource* music;

    bool alreadyIn;

    float insideTimer;
    bool killp;
    float maskForTime;
};