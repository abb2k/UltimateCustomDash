#pragma once
#include <include.h>
#include "CNGameLayer.h"

class DefaultDemonFace : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, int AILevel);

    virtual void update(float delta);
public:
    static DefaultDemonFace* create(CNGameLayer* gameLayer, int AILevel);

    CNGameLayer* mainLayer;

    bool openCamsLock;

    int _AILevel;

    void OnOpportunity();

    bool inTheRoom;

    float killTimer;
    float avoidTimer;

    CCSprite* ventFace;
    CCSprite* officeFace;

    bool gottem;

    bool actOnce;

    void endAttack();
};