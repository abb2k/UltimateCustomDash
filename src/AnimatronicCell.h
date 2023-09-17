#pragma once
#include <include.h>
#include <discriptionBox.h>

class AnimatronicCell : public cocos2d::CCLayer {
protected:
    virtual bool init(std::string, std::string, std::string);
    void UpButton();
    void DownButton();
    virtual void update(float delta);
    void getHoverEnter();
    void getHoverExit();
    bool getHover(CCNode*);
    bool getTouchOn(CCNode*);
    bool getTouchOn(CCNode*, CCTouch*);

    void OnTouchended();
public:
    static AnimatronicCell* create(std::string, std::string, std::string);

    bool OnTouchDown = false;

    bool SpeedUpLevelsUp = false;
    bool SpeedUpLevelsDown = false;
    float startingButtonSpeedup = 0.25f;
    float buttonHoldTimeDelay;

    CCLabelBMFont* AILevelText;
    CCSprite* AnimatronicSprite;
    CCSprite* CellOutline;
    CCSprite* CellOutlineSelected;

    CCSprite* buttonUpspr;
    CCSprite* buttonDownspr;

    CCLayer* parent;

    discriptionBox* discripBox;

    bool isHovering = false;

    bool lastInRow = false;

    std::string Discription;
    std::string Name;

    CCLabelTTF* debugText;

    int AILevel;
};