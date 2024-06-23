#pragma once
#include <include.h>
#include "CNGameLayer.h"

class plushAnimatronics : public cocos2d::CCLayer {
protected:
    virtual bool init(CNGameLayer* gameLayer, float opportunity, int CotAILevel, int MindcapAILevel, int MichiAILevel);

    virtual void update(float delta);
public:
    static plushAnimatronics* create(CNGameLayer* gameLayer, float opportunity, int CotAILevel, int MindcapAILevel, int MichiAILevel);

    CNGameLayer* mainLayer;

    float _opportunity;

    float opportunityTimer;

    int _CotAILevel;
    int _MindcapAILevel;
    int _MichiAILevel;

    bool michiAppeared;
    bool mindcapAppeard;
    bool cotAppeared;

    bool boughtElderE;
    bool boughtMindcapPlush;
    bool boughtTriple;

    float saftyTimer;
    bool saftyLock;

    CCSprite* mindcap;
    CCSprite* michi;
    CCSprite* cot;

    CCLabelBMFont* mindcapPlushText;
    CCSprite* mindcapPlushTextBuyButtton;

    CCLabelBMFont* boughtElderEText;
    CCSprite* boughtElderETextBuyButtton;

    CCLabelBMFont* boughtTripleText;
    CCSprite* boughtTripleTextBuyButtton;

    int ElderECost;
    int MindcapPlushCost;
    int TripleCost;

    enum plushes {cot_, mindcap_, michi_};
    std::vector<plushes> order;

    void OnOpportunity();
};