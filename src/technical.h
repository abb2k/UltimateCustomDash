#pragma once
#include <include.h>
#include "CNGameLayer.h"

class technical : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static technical* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    float maskTime = 2;

    bool InOffice;

    CCNode* techS;

    AudioSource* stare = nullptr;

    void OnOpportunity();

    void miniflicker();

    void Flicker();

    void KillPlayer();
};