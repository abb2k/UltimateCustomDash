#pragma once
#include <include.h>
#include "CNGameLayer.h"

class SpaceUK : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static SpaceUK* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _AILevel;

    void OnOpportunity();

    CCSprite* spaceUKIcon;

    CCNode* MaskPCLayer;

    CCLabelTTF* dtext;

    CCSprite* SmallCam01;
    CCSprite* SmallCam02;
    CCSprite* SmallCam03;

    enum SmallCams {SmallCam1, SmallCam2, SmallCam3};
    SmallCams currCamera = SmallCams::SmallCam1;

    CCSprite* SmallCam01ButtonOn;
    CCSprite* SmallCam01ButtonOff;
    CCSprite* SmallCam01ButtonText;
    CCSprite* SmallCam02ButtonOn;
    CCSprite* SmallCam02ButtonOff;
    CCSprite* SmallCam02ButtonText;
    CCSprite* SmallCam03ButtonOn;
    CCSprite* SmallCam03ButtonOff;
    CCSprite* SmallCam03ButtonText;
    CCNode* SmallCam01ButtonCont;
    CCNode* SmallCam02ButtonCont;
    CCNode* SmallCam03ButtonCont;

    void updateMiniCams(SmallCams cam);

    SmallCams currZBotPos;

    CCSprite* ZBotS;

    void changeZBotPosition();

    SmallCams RandomPosition();

    enum blockPoses {None, blockCam1, blockCam2, blockCam3};
    blockPoses currBlockPos = blockPoses::None;

    CCSprite* CblockCam1;
    CCSprite* OblockCam1;

    CCSprite* CblockCam2;
    CCSprite* OblockCam2;

    CCSprite* CblockCam3;
    CCSprite* OblockCam3;

    void CloseSmallDoor(blockPoses pos);

    void kill();
};