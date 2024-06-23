#pragma once
#include <include.h>
#include "CNGameLayer.h"

class bloodlust : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static bloodlust* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* icon;

    CNGameLayer::ductLocations location;

    float escapeTimer;
};