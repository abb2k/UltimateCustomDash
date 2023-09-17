#pragma once
#include <include.h>
#include "AnimatronicCell.h"

#include "AnimatronicCellContainer.h"
#include "MenuSideBar.h"
#include "officeLayer.h"
#include "PowerUpsLayer.h"
#include "challenges.h"

class customNightLayer : public cocos2d::CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* e);

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* e);

    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* e);

    virtual void ccTouchMoved(CCTouch* touch, CCEvent* e);

    CCSprite* CreateAnimatedSprite(float speed, int amoutOfFrames, std::string frames[]);
public:
    static customNightLayer* create();
    void EnterLayer();

    AnimatronicCellContainer* _AnimatronicCellContainer;
    MenuSideBar* _MenuSideBar;
    officeLayer* _officeLayer;
    PowerUpsLayer* _PowerUpsLayer;
    challenges* _challenges;

    bool clicking = false;

    bool oneTimeClick = false;

    int OfficeSelected = 0;
};