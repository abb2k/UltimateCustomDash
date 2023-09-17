#pragma once
#include <include.h>

class officeLayer : public cocos2d::CCLayer {
protected:
    virtual bool init(CCNode*);
    virtual void keyBackClicked();

    virtual void update(float delta);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* e);

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* e);

    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* e);

    virtual void ccTouchMoved(CCTouch* touch, CCEvent* e);

    bool getHover(CCNode*);
    bool getTouchOn(CCNode*);
    bool getTouchOn(CCNode*, CCTouch*);

public:
    static officeLayer* create(CCNode*);

    //the menu layer
    CCNode* dad;

    bool clicking = false;

    bool oneTimeClick = false;

    CCSprite* defaultOffice;

    CCSprite* fnafSisLocOffice;

    CCSprite* fnaf3Office;

    CCSprite* fnaf4Office;

    CCSprite* p2000;

    CCSprite* p5000;

    CCSprite* p8000;

    CCSprite* outline;

    CCSprite* okButton;
};