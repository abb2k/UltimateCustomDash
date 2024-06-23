#pragma once
#include <include.h>
#include "CNGameLayer.h"

class timeMachineDinosaur : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static timeMachineDinosaur* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    CNGameLayer::Cameras cam;

    CCSprite* Dinosaur;

    bool appeared = false;

    void OnOpportunity();
};