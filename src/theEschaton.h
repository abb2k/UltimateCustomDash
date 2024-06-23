#pragma once
#include <include.h>
#include "CNGameLayer.h"

class theEschaton : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static theEschaton* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* turnedOff;
    CCSprite* turnedOn;

    bool inOffice;

    bool avoiding;

    bool isTurnedOn;

    bool killplayer;

    CCRenderTexture* turnedOffTex;
    CCRenderTexture* turnedOnTex;

    void avoded();
};