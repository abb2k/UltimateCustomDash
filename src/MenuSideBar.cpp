
#include <MenuSideBar.h>
#include "customNightLayer.h"
#include "officeLayer.h"
#include "PowerUpsLayer.h"
#include "challenges.h"
#include "CNGameLayer.h"
#include "creditsLayer.h"

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

    pointValue = CCLabelBMFont::create("0", "clickteamBig.fnt"_spr, 300, CCTextAlignment::kCCTextAlignmentRight);
    pointValue->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    pointValue->setScale(0.85f);
    pointValue->setPosition({42,-25});

    this->addChild(pointValue);

    std::string highScoreTextString = std::to_string(highScore);
    highScoreText = CCLabelBMFont::create(highScoreTextString.c_str(), "clickteamBig.fnt"_spr, 300, CCTextAlignment::kCCTextAlignmentRight);
    highScoreText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    highScoreText->setScale(0.575f);
    highScoreText->setPosition({39,-54});

    this->addChild(highScoreText);

    UsingcharInfo = Mod::get()->getSavedValue<bool>("Show_Character_Descriptions", true);
    UsingVisualeffects = Mod::get()->getSavedValue<bool>("Visual_Effects", true);

    Best5020timetext = CCLabelBMFont::create("0:00.0", "clickteamMedium.fnt"_spr, 300, CCTextAlignment::kCCTextAlignmentRight);
    Best5020timetext->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    Best5020timetext->setScale(0.5f);
    Best5020timetext->setPosition({32,-77});

    this->addChild(Best5020timetext);

    setAll0 = CCSprite::create("setall0Off.png"_spr);
    setAll0->setPosition({0, 149});
    setAll0->setScale(1.15f);

    setAll0On = CCSprite::create("setall0On.png"_spr);
    setAll0On->setPosition({0, 149});
    setAll0On->setScale(1.15f);
    setAll0On->setVisible(false);

    addAll1 = CCSprite::create("addall1Off.png"_spr);
    addAll1->setPosition({0, 127});
    addAll1->setScale(1.15f);

    addAll1On = CCSprite::create("addall1On.png"_spr);
    addAll1On->setPosition({0, 127});
    addAll1On->setScale(1.15f);
    addAll1On->setVisible(false);

    setAll5 = CCSprite::create("setall5Off.png"_spr);
    setAll5->setPosition({0, 105});
    setAll5->setScale(1.15f);

    setAll5On = CCSprite::create("setall5On.png"_spr);
    setAll5On->setPosition({0, 105});
    setAll5On->setScale(1.15f);
    setAll5On->setVisible(false);

    setAll10 = CCSprite::create("setall10Off.png"_spr);
    setAll10->setPosition({0, 83});
    setAll10->setScale(1.15f);

    setAll10On = CCSprite::create("setall10On.png"_spr);
    setAll10On->setPosition({0, 83});
    setAll10On->setScale(1.15f);
    setAll10On->setVisible(false);

    setAll20 = CCSprite::create("setall20Off.png"_spr);
    setAll20->setPosition({0, 61});
    setAll20->setScale(1.15f);

    setAll20On = CCSprite::create("setall20On.png"_spr);
    setAll20On->setPosition({0, 61});
    setAll20On->setScale(1.15f);
    setAll20On->setVisible(false);

    setAllRandom = CCSprite::create("setallRandomOff.png"_spr);
    setAllRandom->setPosition({0, 43});
    setAllRandom->setScale(1.15f);

    setAllRandomOn = CCSprite::create("setallRandomOn.png"_spr);
    setAllRandomOn->setPosition({0, 43});
    setAllRandomOn->setScale(1.15f);
    setAllRandomOn->setVisible(false);

    settingsButton = CCSprite::create("settingButtOff.png"_spr);
    settingsButton->setScale(0.6f);
    settingsButton->setPosition({21, -95});

    settingsButtonOn = CCSprite::create("settingButtOn.png"_spr);
    settingsButtonOn->setScale(0.6f);
    settingsButtonOn->setPosition({21, -95});
    settingsButtonOn->setVisible(false);

    creditsButton = CCSprite::create("creditsButtOff.png"_spr);
    creditsButton->setScaleX(1.075f);
    creditsButton->setScaleY(1.275f);
    creditsButton->setPosition({-13, -99.5f});

    creditsButtonOn = CCSprite::create("creditsButtOn.png"_spr);
    creditsButtonOn->setScaleX(1.075f);
    creditsButtonOn->setScaleY(1.275f);
    creditsButtonOn->setPosition({-13, -99.5f});
    creditsButtonOn->setVisible(false);

    office = CCSprite::create("Office.png"_spr);
    office->setPosition({0, 27});

    powerUps = CCSprite::create("powerUps.png"_spr);
    powerUps->setPosition({0, 15});

    challengesS = CCSprite::create("Challanges.png"_spr);
    challengesS->setPosition({0, 3});

    pointValueText = CCSprite::create("pointVal.png"_spr);
    pointValueText->setPosition({-4, -9});

    HighScore = CCSprite::create("highS.png"_spr);
    HighScore->setPosition({-4, -42});

    bestTimeText = CCSprite::create("btt.png"_spr);
    bestTimeText->setPosition({-2, -68});
    bestTimeText->setScale(1.1f);
    
    GO = CCSprite::create("goMediumOff.png"_spr);
    GO->setPosition({0, -130});
    GO->setScale(1.1f);

    GOOn = CCSprite::create("goMediumOn.png"_spr);
    GOOn->setPosition({0, -130});
    GOOn->setScale(1.1f);
    GOOn->setVisible(false);

    this->addChild(setAll0);
    this->addChild(addAll1);
    this->addChild(setAll5);
    this->addChild(setAll10);
    this->addChild(setAll20);
    this->addChild(setAllRandom);
    this->addChild(settingsButton);
    this->addChild(creditsButton);
    this->addChild(setAll0On);
    this->addChild(addAll1On);
    this->addChild(setAll5On);
    this->addChild(setAll10On);
    this->addChild(setAll20On);
    this->addChild(setAllRandomOn);
    this->addChild(settingsButtonOn);
    this->addChild(creditsButtonOn);

    this->addChild(office);
    this->addChild(powerUps);
    this->addChild(challengesS);
    this->addChild(pointValueText);
    this->addChild(HighScore);
    this->addChild(bestTimeText);
    this->addChild(GO);
    this->addChild(GOOn);

    this->setZOrder(-5);

    this->scheduleUpdate();

    return true;
}

void MenuSideBar::update(float delta){
    if (getHover(GO)){
        customNightLayer* mainLayer = (customNightLayer*)dad;
        if (mainLayer->_creditsLayer == nullptr){
            if (mainLayer->_settingsLayer == nullptr){
                GO->setVisible(false);
                GOOn->setVisible(true);
            }
        }
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
        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(addAll1)){
        addAll1->setVisible(false);
        addAll1On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->AddAll(1);

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAll5)){
        setAll5->setVisible(false);
        setAll5On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(5);

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAll10)){
        setAll10->setVisible(false);
        setAll10On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(10);

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAll20)){
        setAll20->setVisible(false);
        setAll20On->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(20);

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(setAllRandom)){
        setAllRandom->setVisible(false);
        setAllRandomOn->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        mainLayer->_AnimatronicCellContainer->SetAll(-1);

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(settingsButton)){
        settingsButton->setVisible(false);
        settingsButtonOn->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        settingsLayer* sLayer = settingsLayer::create(dad, this);
        dad->getParent()->addChild(sLayer);
        sLayer->setZOrder(10);
        mainLayer->_settingsLayer = sLayer;

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        setToFalse = 0.1f;
    }

    if (getTouchOn(creditsButton)){
        creditsButton->setVisible(false);
        creditsButtonOn->setVisible(true);

        customNightLayer* mainLayer = (customNightLayer*)dad;

        creditsLayer* cLayer = creditsLayer::create(dad);
        dad->getParent()->addChild(cLayer);
        cLayer->setZOrder(10);
        mainLayer->_creditsLayer = cLayer;

        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
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

        setAllRandom->setVisible(true);
        setAllRandomOn->setVisible(false);

        settingsButton->setVisible(true);
        settingsButtonOn->setVisible(false);

        creditsButton->setVisible(true);
        creditsButtonOn->setVisible(false);
    }

    if (getTouchOn(office)){
        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        officeLayer* office = officeLayer::create(dad);
        dad->getParent()->addChild(office);
        office->setZOrder(10);
        customNightLayer* mainLayer = (customNightLayer*)dad;
        mainLayer->_officeLayer = office;
    }

    if (getTouchOn(powerUps)){
        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        PowerUpsLayer* PowerUps = PowerUpsLayer::create(dad);
        dad->getParent()->addChild(PowerUps);
        PowerUps->setZOrder(10);
        customNightLayer* mainLayer = (customNightLayer*)dad;
        mainLayer->_PowerUpsLayer = PowerUps;
    }

    if (getTouchOn(challengesS)){
        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        challenges* chal = challenges::create(dad);
        dad->getParent()->addChild(chal);
        chal->setZOrder(10);
        customNightLayer* mainLayer = (customNightLayer*)dad;
        mainLayer->_challenges = chal;
    }

    customNightLayer* mainLayer = (customNightLayer*)dad;
    if (getTouchOn(GO) && !goClicked){
        
        goClicked = true;
        mainLayer->FadeActive = false;
        mainLayer->clicking = false;
        mainLayer->oneTimeClick = false;
    }

    if (goClicked && mainLayer->isTransitionReady){
        goClicked = false;
        int currentSet = 0;
        mainLayer->_AnimatronicCellContainer->allAnimatronics.clear();
        for (int i = 0; i < (int)mainLayer->_AnimatronicCellContainer->getChildren()->count(); i++)
        {
            if (i != 0){
                if ((AnimatronicCell*)mainLayer->_AnimatronicCellContainer->getChildren()->objectAtIndex(i) != nullptr){
                    AnimatronicCell* thisone = (AnimatronicCell*)mainLayer->_AnimatronicCellContainer->getChildren()->objectAtIndex(i);

                    animatronic* currAnima = new animatronic(thisone->Name, thisone->AILevel);

                    mainLayer->_AnimatronicCellContainer->allAnimatronics.insert(mainLayer->_AnimatronicCellContainer->allAnimatronics.begin(), currAnima);

                    currentSet++;
                }
            }
        }

        if (mainLayer->bgMusic != nullptr){
            mainLayer->bgMusic->RemoveMeAndCleanUpSound();
            mainLayer->bgMusic = nullptr;
        }  

        CNGameLayer::create(mainLayer->_AnimatronicCellContainer->allAnimatronics, mainLayer->OfficeSelected, frigidActive, threeCoinsActive, batteryActive, DDRepelActive)->EnterLayer(mainLayer->_AnimatronicCellContainer->allAnimatronics, mainLayer->OfficeSelected, frigidActive, threeCoinsActive, batteryActive, DDRepelActive);
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