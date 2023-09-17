#pragma once
#include <include.h>
#include "animatronic.h"

class challengeCell : public cocos2d::CCLayer {
protected:
    virtual bool init(std::string challengeName, std::vector<animatronic*> cha);

    virtual void update(float delta);

public:

    static challengeCell* create(std::string challengeName, std::vector<animatronic*> cha);

    CCNode* dad;

    CCSprite* button;
    CCSprite* buttonG;

    std::vector<animatronic*> chaSave;

    bool selected = false;
};