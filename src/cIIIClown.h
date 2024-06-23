#pragma once
#include <include.h>
#include "CNGameLayer.h"

class cIIIClown : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static cIIIClown* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    CNGameLayer::ventPosition Position;

    float _opportunity;

    bool killplayer;

    float opportunityTimer;

    int _AILevel;
    float jumptimer = 4;
    float avoidTimer = 0.5f;
    bool playsound;

    void OnOpportunity();

    AudioSource* indicateor;
};