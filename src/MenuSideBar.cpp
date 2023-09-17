
#include <MenuSideBar.h>
#include "customNightLayer.h"
#include "officeLayer.h"
#include "PowerUpsLayer.h"
#include "challenges.h"

MenuSideBar* MenuSideBar::create() {
    auto ret = new MenuSideBar();

    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool MenuSideBar::init() { 

    pointValue = CCLabelBMFont::create("0", "abb2k.UltimateCustomDash/clickteamBig.fnt", 300, CCTextAlignment::kCCTextAlignmentRight);
    pointValue->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    pointValue->setScale(0.9f);
    pointValue->setPosition({42,-16});

    this->addChild(pointValue);

    std::string highScoreTextString = std::to_string(highScore);
    highScoreText = CCLabelBMFont::create(highScoreTextString.c_str(), "abb2k.UltimateCustomDash/clickteamBig.fnt", 300, CCTextAlignment::kCCTextAlignmentRight);
    highScoreText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    highScoreText->setScale(0.8f);
    highScoreText->setPosition({39,-49});

    this->addChild(highScoreText);

    Best5020timetext = CCLabelBMFont::create("00:00.00", "abb2k.UltimateCustomDash/clickteamMedium.fnt", 300, CCTextAlignment::kCCTextAlignmentRight);
    Best5020timetext->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    Best5020timetext->setScale(0.5f);
    Best5020timetext->setPosition({32,-77});

    this->addChild(Best5020timetext);

    setAll0 = CCSprite::create("abb2k.UltimateCustomDash/setall0Off.png");
    setAll0->setPosition({0, 149});
    setAll0->setScale(1.15f);

    setAll0On = CCSprite::create("abb2k.UltimateCustomDash/setall0On.png");
    setAll0On->setPosition({0, 149});
    setAll0On->setScale(1.15f);
    setAll0On->setVisible(false);

    addAll1 = CCSprite::create("abb2k.UltimateCustomDash/addall1Off.png");
    addAll1->setPosition({0, 127});
    addAll1->setScale(1.15f);

    addAll1On = CCSprite::create("abb2k.UltimateCustomDash/addall1On.png");
    addAll1On->setPosition({0, 127});
    addAll1On->setScale(1.15f);
    addAll1On->setVisible(false);

    setAll5 = CCSprite::create("abb2k.UltimateCustomDash/setall5Off.png");
    setAll5->setPosition({0, 105});
    setAll5->setScale(1.15f);

    setAll5On = CCSprite::create("abb2k.UltimateCustomDash/setall5On.png");
    setAll5On->setPosition({0, 105});
    setAll5On->setScale(1.15f);
    setAll5On->setVisible(false);

    setAll10 = CCSprite::create("abb2k.UltimateCustomDash/setall10Off.png");
    setAll10->setPosition({0, 83});
    setAll10->setScale(1.15f);

    setAll10On = CCSprite::create("abb2k.UltimateCustomDash/setall10On.png");
    setAll10On->setPosition({0, 83});
    setAll10On->setScale(1.15f);
    setAll10On->setVisible(false);

    setAll20 = CCSprite::create("abb2k.UltimateCustomDash/setall20Off.png");
    setAll20->setPosition({0, 61});
    setAll20->setScale(1.15f);

    setAll20On = CCSprite::create("abb2k.UltimateCustomDash/setall20On.png");
    setAll20On->setPosition({0, 61});
    setAll20On->setScale(1.15f);
    setAll20On->setVisible(false);

    office = CCSprite::create("abb2k.UltimateCustomDash/Office.png");
    office->setPosition({0, 42});

    powerUps = CCSprite::create("abb2k.UltimateCustomDash/powerUps.png");
    powerUps->setPosition({0, 31});

    challengesS = CCSprite::create("abb2k.UltimateCustomDash/Challanges.png");
    challengesS->setPosition({0, 15});

    pointValueText = CCSprite::create("abb2k.UltimateCustomDash/pointVal.png");
    pointValueText->setPosition({-4, 1});

    HighScore = CCSprite::create("abb2k.UltimateCustomDash/highS.png");
    HighScore->setPosition({-4, -33});

    bestTimeText = CCSprite::create("abb2k.UltimateCustomDash/btt.png");
    bestTimeText->setPosition({-2, -66});
    bestTimeText->setScale(1.1f);

    showCharInfoText = CCSprite::create("abb2k.UltimateCustomDash/charInfo.png");
    showCharInfoText->setPosition({-24, -90});
    showCharInfoText->setScale(1.1f);

    showCharInfo = CCSprite::create("abb2k.UltimateCustomDash/togglesOff.png");
    showCharInfo->setPosition({-7, -91});
    showCharInfo->setVisible(!UsingcharInfo);

    showCharInfoOn = CCSprite::create("abb2k.UltimateCustomDash/togglesOnV.png");
    showCharInfoOn->setPosition({-7, -91});
    showCharInfoOn->setVisible(UsingcharInfo);

    visualEffectsText = CCSprite::create("abb2k.UltimateCustomDash/visualEffects.png");
    visualEffectsText->setPosition({12, -90});
    visualEffectsText->setScale(1.1f);

    visualEffects = CCSprite::create("abb2k.UltimateCustomDash/togglesOff.png");
    visualEffects->setPosition({26, -91});
    visualEffects->setVisible(!UsingVisualeffects);

    visualEffectsOn = CCSprite::create("abb2k.UltimateCustomDash/togglesOnV.png");
    visualEffectsOn->setPosition({26, -91});
    visualEffectsOn->setVisible(UsingVisualeffects);

    holdDelToErace = CCSprite::create("abb2k.UltimateCustomDash/del.png");
    holdDelToErace->setPosition({0, -102});
    holdDelToErace->setScale(1.15f);

    GO = CCSprite::create("abb2k.UltimateCustomDash/goMediumOff.png");
    GO->setPosition({0, -130});
    GO->setScale(1.1f);

    GOOn = CCSprite::create("abb2k.UltimateCustomDash/goMediumOn.png");
    GOOn->setPosition({0, -130});
    GOOn->setScale(1.1f);
    GOOn->setVisible(false);

    this->addChild(setAll0);
    this->addChild(addAll1);
    this->addChild(setAll5);
    this->addChild(setAll10);
    this->addChild(setAll20);
    this->addChild(setAll0On);
    this->addChild(addAll1On);
    this->addChild(setAll5On);
    this->addChild(setAll10On);
    this->addChild(setAll20On);

    this->addChild(office);
    this->addChild(powerUps);
    this->addChild(challengesS);
    this->addChild(pointValueText);
    this->addChild(HighScore);
    this->addChild(bestTimeText);
    this->addChild(showCharInfoText);
    this->addChild(showCharInfo);
    this->addChild(showCharInfoOn);
    this->addChild(visualEffectsText);
    this->addChild(visualEffects);
    this->addChild(visualEffectsOn);
    this->addChild(holdDelToErace);
    this->addChild(GO);
    this->addChild(GOOn);

    this->setZOrder(-5);

    this->scheduleUpdate();

    return true;
}

void MenuSideBar::update(float delta){
    if (getHover(GO)){
        GO->setVisible(false);
        GOOn->setVisible(true);
    }
    else {
        GO->setVisible(true);
        GOOn->setVisible(false);
    }

    if (getTouchOn(setAll0)){
        setAll0->setVisible(false);
        setAll0On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(0);
        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        setToFalse = 0.1f;
    }

    if (getTouchOn(addAll1)){
        addAll1->setVisible(false);
        addAll1On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->AddAll(1);

        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAll5)){
        setAll5->setVisible(false);
        setAll5On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(5);

        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAll10)){
        setAll10->setVisible(false);
        setAll10On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(10);

        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAll20)){
        setAll20->setVisible(false);
        setAll20On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(20);

        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        setToFalse = 0.1f;
    }

    if (setToFalse > 0){
        setToFalse -= delta;
    }
    else {
        setAll0->setVisible(true);
        setAll0On->setVisible(false);

        addAll1->setVisible(true);
        addAll1On->setVisible(false);

        setAll5->setVisible(true);
        setAll5On->setVisible(false);

        setAll10->setVisible(true);
        setAll10On->setVisible(false);

        setAll20->setVisible(true);
        setAll20On->setVisible(false);
    }

    if (getTouchOn(showCharInfo)){
        if (UsingcharInfo){
            UsingcharInfo = false;
            showCharInfo->setVisible(true);
            showCharInfoOn->setVisible(false);
        }
        else{
            UsingcharInfo = true;
            showCharInfo->setVisible(false);
            showCharInfoOn->setVisible(true);
        }
    }

    if (getTouchOn(visualEffects)){
        if (UsingVisualeffects){
            UsingVisualeffects = false;
            visualEffects->setVisible(true);
            visualEffectsOn->setVisible(false);
        }
        else{
            UsingVisualeffects = true;
            visualEffects->setVisible(false);
            visualEffectsOn->setVisible(true);
        }
    }

    if (getTouchOn(office)){
        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        officeLayer* office = officeLayer::create(dad);
        dad->getParent()->addChild(office);
        office->setZOrder(10);
        customNightLayer* mainLayer = (customNightLayer*)dad;
        mainLayer->_officeLayer = office;
    }

    if (getTouchOn(powerUps)){
        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        PowerUpsLayer* PowerUps = PowerUpsLayer::create(dad);
        dad->getParent()->addChild(PowerUps);
        PowerUps->setZOrder(10);
        customNightLayer* mainLayer = (customNightLayer*)dad;
        mainLayer->_PowerUpsLayer = PowerUps;
    }

    if (getTouchOn(challengesS)){
        GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
        challenges* chal = challenges::create(dad);
        dad->getParent()->addChild(chal);
        chal->setZOrder(10);
        customNightLayer* mainLayer = (customNightLayer*)dad;
        mainLayer->_challenges = chal;
    }

    std::string message = std::to_string(OverallPoints);

    pointValue->setString(message.c_str());
}

bool MenuSideBar::getHover(CCNode* node){
    //size
    auto contentSize = node->getContentSize();

    //get all parents (to multiply width and height with scale of them)
    bool HasreachedEndOfParentCheck = false;

    CCNode* LastParent = node->getParent();

    CCNode* Scene = nullptr;

    float multiplyX = node->getScaleX();

    float multiplyY = node->getScaleY();

    while(!HasreachedEndOfParentCheck){

        if (LastParent != nullptr){
            multiplyX = multiplyX * LastParent->getScaleX();
            multiplyY = multiplyY * LastParent->getScaleY();

            Scene = LastParent;
            LastParent = LastParent->getParent();
        }
        else {
            HasreachedEndOfParentCheck = true;
        }
    }

    //pos
    auto pos = node->convertToWorldSpace({0,0});

    auto mousePos = getMousePos();

    CCRect* rect = new CCRect(pos.x, pos.y, contentSize.width * multiplyX, contentSize.height * multiplyY);

    //check
    if (rect->containsPoint(mousePos)){
        return true;
    }

    return false;
}

bool MenuSideBar::getTouchOn(CCNode* node, CCTouch* touch){
    //size
    auto contentSize = node->getContentSize();

    //get all parents (to multiply width and height with scale of them)
    bool HasreachedEndOfParentCheck = false;

    CCNode* LastParent = node->getParent();

    CCNode* Scene = nullptr;

    float multiplyX = node->getScaleX();

    float multiplyY = node->getScaleY();

    while(!HasreachedEndOfParentCheck){

        if (LastParent != nullptr){
            multiplyX = multiplyX * LastParent->getScaleX();
            multiplyY = multiplyY * LastParent->getScaleY();

            Scene = LastParent;
            LastParent = LastParent->getParent();
        }
        else {
            HasreachedEndOfParentCheck = true;
        }
    }

    //pos
    auto pos = node->convertToWorldSpace({0,0});

    auto mousePos = touch;

    CCRect* rect = new CCRect(pos.x, pos.y, contentSize.width * multiplyX, contentSize.height * multiplyY);

    //check
    if (rect->containsPoint(mousePos->m_point)){
        return true;
    }

    return false;
}

bool MenuSideBar::getTouchOn(CCNode* node){

    customNightLayer* mainLayer = (customNightLayer*)dad;

    if (mainLayer->clicking && !mainLayer->oneTimeClick){
        if (getHover(node)){
            mainLayer->oneTimeClick = true;
            return true;
        }
    }
    return false;
}