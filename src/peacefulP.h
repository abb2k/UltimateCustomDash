#pragma once
#include <include.h>
#include "CNGameLayer.h"

class peacefulP : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static peacefulP* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* frame1;
    CCSprite* frame2;
    CCSprite* frame3;

    bool displaying;

    AudioSource* music = nullptr;

    bool enterLock;
};