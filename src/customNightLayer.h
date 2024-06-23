#pragma once
#include <include.h>
#include "AnimatronicCell.h"

#include "AnimatronicCellContainer.h"
#include "MenuSideBar.h"
#include "officeLayer.h"
#include "PowerUpsLayer.h"
#include "challenges.h"
#include "creditsLayer.h"
#include "settingsLayer.h"

class customNightLayer : public cocos2d::CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* e);

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* e);

    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* e);

    virtual void ccTouchMoved(CCTouch* touch, CCEvent* e);

    virtual void onEnterTransitionDidFinish();

    CCSprite* CreateAnimatedSprite(float speed, int amoutOfFrames, std::string frames[]);

    virtual void update(float delta);
public:
    static customNightLayer* create();
    void EnterLayer(float);

    AnimatronicCellContainer* _AnimatronicCellContainer = nullptr;
    MenuSideBar* _MenuSideBar = nullptr;
    officeLayer* _officeLayer = nullptr;
    PowerUpsLayer* _PowerUpsLayer = nullptr;
    challenges* _challenges = nullptr;
    creditsLayer* _creditsLayer = nullptr;
    settingsLayer* _settingsLayer = nullptr;

    float doubleClickTimer;

    bool clicking = false;

    bool oneTimeClick = false;

    int OfficeSelected = 0;

    AudioSource* bgMusic = nullptr;

    CCSprite* faceScreen;
    float fadeScreenOpacity = 255;;
    bool isTransitionReady;
    bool FadeActive;
    float FadeSpeed = 200;
};