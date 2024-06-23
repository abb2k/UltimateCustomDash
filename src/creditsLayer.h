#pragma once
#include <include.h>

class creditsLayer : public cocos2d::CCLayer {
protected:
    virtual bool init(CCNode* _mainlayer);
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
    static creditsLayer* create(CCNode* _mainlayer);

    //the menu layer
    CCNode* dad;

    bool clicking = false;

    bool oneTimeClick = false;

    CCSprite* exitButt;

    CCNode* centerP;
};