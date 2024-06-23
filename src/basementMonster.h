#pragma once
#include <include.h>
#include "CNGameLayer.h"

class basementMonster : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static basementMonster* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    enum eyeColor {blue, green, orange};

    eyeColor eyesColors[2];

    CCSprite* monster;
    CCSprite* eyeLeft;
    CCSprite* eyeRight;
    CCNode* eyesContainer;

    CCSprite* KeyBlue;
    CCSprite* KeyGreen;
    CCSprite* KeyOrange;

    CCRenderTexture* keyBlueTex;
    CCRenderTexture* keyGreenTex;
    CCRenderTexture* keyOrangeTex;

    int keysFound = 0;

    bool InOffice;

    void kill();

    bool killp;
};