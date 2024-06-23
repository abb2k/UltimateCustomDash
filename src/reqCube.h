#pragma once
#include <include.h>
#include "CNGameLayer.h"

class reqCube : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static reqCube* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    int _AILevel;

    bool inRoom;
    bool rollWakeChance;
    bool jumpscared;

    CCSprite* cube;

    CCRenderTexture* renderTexture;

    void OnOpportunity();

    void disableCams();
    void reEnableCams();
};