#pragma once
#include <include.h>
#include "CNGameLayer.h"

class SFSun : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static SFSun* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    int _AILevel;

    void OnOpportunity();

    float progress;

    CCSprite* sun;

    bool kill;
};