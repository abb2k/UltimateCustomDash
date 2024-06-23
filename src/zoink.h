#pragma once
#include <include.h>
#include "CNGameLayer.h"

class zoink : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static zoink* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    float spikeOpacity = 1;

    CCLabelTTF* dtext;

    bool jumped = false;

    float spikeX = 0;
    float spikeY = 0;

    CCSprite* spike;

    CCRenderTexture* renderTexture;

    enum positions { pos1, pos2, pos3, pos4, pos5, pos6};
    positions currentPos = pos1;

    void movePosition();

    void OnOpportunity();
};
