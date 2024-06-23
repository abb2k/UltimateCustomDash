#pragma once
#include <include.h>
#include "CNGameLayer.h"
#include "AttemptAtReversingDialogObject.h"

class shopkeeper : public cocos2d::CCLayer, public DialogDelegate {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int AILevel);

    virtual void update(float delta);
public:
    static shopkeeper* create(CNGameLayer* gameLayer, float opportunity, int AILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    virtual void dialogClosed(DialogLayer* d);

    int _AILevel;

    bool awake;

    CCSprite* asleep;
    CCSprite* Wake;

    CCSprite* pay;

    float stopTimer = 4;

    float glitchTimer;

    bool currGSprite;

    float killTimer = 15;

    void OnOpportunity();

    DialogLayer* Dialog = nullptr;

    bool dialogtest;

    enum SKface {calm, pissed};
    void createKeeperDialog(std::string text, SKface emotion);

    bool heaterDialogeLock;

    void removeDialog();
};