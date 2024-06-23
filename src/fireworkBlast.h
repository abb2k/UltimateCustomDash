#pragma once
#include <include.h>

class fireworkBlast : public cocos2d::CCLayer {
protected:
    virtual bool init(CCNode* dad);

    virtual void update(float delta);
public:
    static fireworkBlast* create(CCNode* dad);

    typedef struct Star{
        CCSprite* sprite;
        CCPoint direction;
    } Star;

    std::vector<Star*> stars;

    float speed = 215;

    float opaci = 255;

    CCSprite* yellowGlow;
    float yellowGlowOpaci = 255;
};