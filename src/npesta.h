#pragma once
#include <include.h>
#include "CNGameLayer.h"

class npesta : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static npesta* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    float jumpscareTime;

    bool inOffice;

    bool killp;

    CCSprite* officeIcon;
};