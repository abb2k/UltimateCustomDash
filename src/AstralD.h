#pragma once
#include <include.h>
#include "CNGameLayer.h"

class AstralD : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static AstralD* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    float maskTime = 2.5f;

    bool InOffice;

    CCSprite* AstralS;

    AudioSource* stare = nullptr;

    void OnOpportunity();

    void miniflicker();

    void Flicker();

    void KillPlayer();
};