#pragma once
#include <include.h>
#include "CNGameLayer.h"

class yata : public cocos2d::CCNode {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static yata* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* yataS;

    bool flyToRight;

    bool clickedGreen;

    CCRenderTexture* renderTexture;

    void reahcedEnd();

    float posMoved = 50;
};