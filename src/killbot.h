
#pragma once
#include <include.h>
#include "CNGameLayer.h"


class killbot : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static killbot* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    bool doingThing;

    void jumpEnded();

    CCLabelTTF* dtext;

    CCNode* notifiCont;

    CCSprite* button;

    float jumpscareTimer = 3.5f;

    float delayTimer = 2;

    bool playJumpscare;

    bool rermoveNotiffi;

    AudioSource* source;

    CCLabelBMFont* loadingText;
};