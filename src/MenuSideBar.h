#pragma once
#include <include.h>

class MenuSideBar : public cocos2d::CCLayer {
protected:
    virtual bool init();

    virtual void update(float delta);

    bool getHover(CCNode*);
    bool getTouchOn(CCNode*);
    bool getTouchOn(CCNode*, CCTouch*);
public:
    static MenuSideBar* create();

    CCNode* dad;

    int OverallPoints = 0;

    float setToFalse = 0;
    int highScore = 8000;

    bool UsingVisualeffects = true;
    bool UsingcharInfo = true;

    bool frigidActive = false;

    bool threeCoinsActive = false;

    bool batteryActive = false;

    bool DDRepelActive = false;

    int frigids = 3;

    int threeCoins = 9;

    int batterys = 0;

    int DDRepels = 2;

    CCLabelBMFont* pointValue;

    CCLabelBMFont* highScoreText;

    CCLabelBMFont* Best5020timetext;

    CCSprite* setAll0;
    CCSprite* setAll0On;

    CCSprite* addAll1;
    CCSprite* addAll1On;

    CCSprite* setAll5;
    CCSprite* setAll5On;

    CCSprite* setAll10;
    CCSprite* setAll10On;

    CCSprite* setAll20;
    CCSprite* setAll20On;

    CCSprite* office;

    CCSprite* powerUps;

    CCSprite* challengesS;

    CCSprite* pointValueText;

    CCSprite* HighScore;

    CCSprite* bestTimeText;

    CCSprite* showCharInfoText;
    CCSprite* showCharInfo;
    CCSprite* showCharInfoOn;

    CCSprite* visualEffectsText;
    CCSprite* visualEffects;
    CCSprite* visualEffectsOn;

    CCSprite* holdDelToErace;

    CCSprite* GO;
    CCSprite* GOOn;
};