#pragma once
#include <include.h>
#include "animatronic.h"
#include "challengeCell.h"
class challenges : public cocos2d::CCLayer {
protected:
    virtual bool init(CCNode* _mainlayer);
    virtual void keyBackClicked();

    virtual void update(float delta);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* e);

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* e);

    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* e);

    virtual void ccTouchMoved(CCTouch* touch, CCEvent* e);

public:
    bool getHover(CCNode*);
    bool getTouchOn(CCNode*);
    bool getTouchOn(CCNode*, CCTouch*);

    static challenges* create(CCNode* _mainlayer);

    void setChallenge(animatronic[]);

    //the menu layer
    CCNode* dad;

    bool clicking = false;

    bool oneTimeClick = false;

    CCSprite* Cancel;
    CCSprite* smallGo;

    challengeCell* BearsAttack1;
    challengeCell* BearsAttack2;
    challengeCell* BearsAttack3;
    challengeCell* PayAttention1;
    challengeCell* PayAttention2;
    challengeCell* LadiesNight1;
    challengeCell* LadiesNight2;
    challengeCell* LadiesNight3;
    challengeCell* CreepyCrawlies1;
    challengeCell* CreepyCrawlies2;
    challengeCell* NightmaresAttack;
    challengeCell* Springtrapped;
    challengeCell* OldFriends;
    challengeCell* Chaos1;
    challengeCell* Chaos2;
    challengeCell* Chaos3;
};