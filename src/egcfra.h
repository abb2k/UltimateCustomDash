#pragma once
#include <include.h>
#include "CNGameLayer.h"

class egcfra : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static egcfra* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    CNGameLayer::ventPosition Position;

    CCSprite* icon;

    float _opportunity;

    bool killplayer;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();
};