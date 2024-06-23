#pragma once
#include <include.h>
#include "CNGameLayer.h"

class grandpaDemon : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static grandpaDemon* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float pauseTime;
    bool Onleft;

    float opportunityTimer;

    int _AILevel;

    CCSprite* faceLeft;
    CCSprite* faceRight;

    bool killplayer;

    void OnOpportunity();

    void block();
    void kill();
    void move(bool toLeft);
};