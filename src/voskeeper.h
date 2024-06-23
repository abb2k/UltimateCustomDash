#pragma once
#include <include.h>
#include "CNGameLayer.h"

class voskeeper : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static voskeeper* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCNode* Cont;

    CCSprite* LockGuy;

    CCSprite* Lock;

    int clickAmount;
    
    int totalClick = 1;
};