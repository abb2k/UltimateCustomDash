#pragma once
#include <include.h>
#include "CNGameLayer.h"

class deadlockedCubes : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static deadlockedCubes* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* cube1;
    CCSprite* cube2;
    CCSprite* cube3;

    AudioSource* jumpSound = nullptr;
};