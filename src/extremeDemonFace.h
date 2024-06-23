#pragma once
#include <include.h>
#include "CNGameLayer.h"

class extremeDemonFace : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static extremeDemonFace* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    AudioSource* warning;

    bool blockOrKill = true;

    float killTimer = 1.4f;
};