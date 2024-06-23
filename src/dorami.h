#pragma once
#include <include.h>
#include "CNGameLayer.h"

class dorami : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static dorami* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    CNGameLayer::ventPosition Position;

    CCSprite* icon;

    float _opportunity;

    bool killplayer;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();
};