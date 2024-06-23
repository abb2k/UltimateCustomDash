#pragma once
#include <include.h>

class settingsLayer : public cocos2d::CCLayer {
protected:
    virtual bool init(CCNode* _mainlayer, CCNode* _sideMenuLayer);
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
    static settingsLayer* create(CCNode* _mainlayer, CCNode* _sideMenuLayer);

    //the menu layer
    CCNode* dad;

    CCNode* sideMenuLayer;

    bool clicking = false;

    bool oneTimeClick = false;

    CCSprite* exitButt;

    CCNode* centerP;

    CCSprite* showCharInfoText;
    CCSprite* showCharInfo;
    CCSprite* showCharInfoOn;

    CCSprite* visualEffectsText;
    CCSprite* visualEffects;
    CCSprite* visualEffectsOn;

    CCSprite* holdDelToErace;

    void OnVolumeChanged(CCObject* mobject);

    Slider* volumeSlider;

    CCLabelBMFont* numberVolumeInput;
    CCSprite* precentSign;

    CCLabelTTF* dtext;
};