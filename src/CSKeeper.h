#pragma once
#include <include.h>
#include "CNGameLayer.h"

class CSKeeper : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static CSKeeper* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    AudioSource* music = nullptr;

    bool attacking;

    float killtimer;

    bool kill;

    bool removemusic;
};