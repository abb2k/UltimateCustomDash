#pragma once
#include <include.h>
#include "CNGameLayer.h"

class wulzy : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static wulzy* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    bool onRight;

    bool Attaking;

    bool killplayer;

    float avoidTimer = 1;

    bool shouldHaveKilled;

    AudioSource* woahSound;
};