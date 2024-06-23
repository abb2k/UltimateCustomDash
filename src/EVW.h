#pragma once
#include <include.h>
#include "CNGameLayer.h"

class EVW : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static EVW* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    int _AILevel;

    float progress;

    bool killPlayer;

    CCSprite* wilderman;

    bool pulse;
};