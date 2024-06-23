#pragma once
#include <include.h>
#include "CNGameLayer.h"

class loochi : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static loochi* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    int _AILevel;

    CNGameLayer::Cameras prevcamera;

    bool canAppear;
    float looktimer;

    bool rollForCloseCams;

    bool jumps;

    bool inJumpscare;

    CCSprite* looch;

    void FinishedJumpscare();
};