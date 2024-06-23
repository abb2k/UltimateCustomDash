#pragma once
#include <include.h>
#include "CNGameLayer.h"

class gdcube : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static gdcube* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    CNGameLayer::ventPosition Position;

    CCSprite* icon;

    float _opportunity;

    bool killplayer;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();
};