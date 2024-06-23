#pragma once
#include <include.h>
#include "CNGameLayer.h"

class robtop : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static robtop* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    float wind = 100;

    bool Escaped;

    bool holding;

    float jumpscareTimer;

    AudioSource* music = nullptr;
};