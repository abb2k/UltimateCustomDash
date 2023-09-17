#pragma once
#include <include.h>

class PowerUpsLayer : public cocos2d::CCLayer {
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

    CCSprite* CreateOutline();

public:
    static PowerUpsLayer* create(CCNode* _mainlayer);

    //the menu layer
    CCNode* dad;

    bool clicking = false;

    bool oneTimeClick = false;

    CCSprite* okButton;

    CCSprite* frigidS;
    CCSprite* frigidSOutline;
    CCLabelBMFont* frigidSText;

    CCSprite* threeCoinsS;
    CCSprite* threeCoinsSOutline;
    CCLabelBMFont* threeCoinsSText;

    CCSprite* batteryS;
    CCSprite* batterySOutline;
    CCLabelBMFont* batterySText;

    CCSprite* DDRepelS;
    CCSprite* DDRepelSOutline;
    CCLabelBMFont* DDRepelSText;
};