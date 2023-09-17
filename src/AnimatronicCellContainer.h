#pragma once
#include <include.h>
#include <AnimatronicCell.h>

class AnimatronicCellContainer : public cocos2d::CCLayer {
protected:
    virtual bool init(AnimatronicCell* [], int CellArrayLength, int, int);
    virtual void update(float delta);

public:
    static AnimatronicCellContainer* create(AnimatronicCell* [], int CellArrayLength, int, int);

    void AddAll(int);
    void SetAll(int);
    void SetSpecific(std::string Name, int AILevel);

    int OpacityFlash = 150;

    CCLabelTTF* debugText;

    int lengthofThings;

    CCNode* dad;
};