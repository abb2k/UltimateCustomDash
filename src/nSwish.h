#pragma once
#include <include.h>
#include "CNGameLayer.h"

class nSwish : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static nSwish* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    int _AILevel;

    float anger;

    float clickTimer;
};