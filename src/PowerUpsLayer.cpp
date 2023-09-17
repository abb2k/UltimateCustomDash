#include <PowerUpsLayer.h>

#include "customNightLayer.h"

PowerUpsLayer* PowerUpsLayer::create(CCNode* _mainlayer) {
    auto ret = new PowerUpsLayer();
    if (ret && ret->init(_mainlayer)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool PowerUpsLayer::init(CCNode* _mainlayer){

    dad = _mainlayer;

    customNightLayer* mainlayer = (customNightLayer*) dad;

    CCSprite* bg = CCSprite::create("abb2k.UltimateCustomDash/sidebarBG.png");
    bg->setPosition({526, 161});
    bg->setScaleX(1.175f);
    bg->setScaleY(1.21f);

    frigidS = CCSprite::create("abb2k.UltimateCustomDash/Frigid1.png");
    frigidS->setPosition({33,223});
    frigidSOutline = CreateOutline();
    frigidSOutline->setPosition({frigidS->getContentSize() / 2});
    frigidSOutline->setVisible(mainlayer->_MenuSideBar->frigidActive);

    std::string frigidSTextt = std::to_string(mainlayer->_MenuSideBar->frigids);
    frigidSText = CCLabelBMFont::create(frigidSTextt.c_str(), "abb2k.UltimateCustomDash/clickteamSmall.fnt",40, CCTextAlignment::kCCTextAlignmentRight);
    frigidSText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    frigidSText->setScale(0.85f);
    frigidSText->setPosition({50,46});
    frigidSText->setZOrder(1);

    if (mainlayer->_MenuSideBar->frigids <= 0){
        frigidS->setOpacity(150);
        frigidSText->setOpacity(150);
    }
    
    frigidS->addChild(frigidSText);
    frigidS->addChild(frigidSOutline);

    threeCoinsS = CCSprite::create("abb2k.UltimateCustomDash/3 coins1.png");
    threeCoinsS->setPosition({33,165});
    threeCoinsSOutline = CreateOutline();
    threeCoinsSOutline->setPosition({threeCoinsS->getContentSize() / 2});
    threeCoinsSOutline->setVisible(mainlayer->_MenuSideBar->threeCoinsActive);

    std::string threeCoinsSTextt = std::to_string(mainlayer->_MenuSideBar->threeCoins);
    threeCoinsSText = CCLabelBMFont::create(threeCoinsSTextt.c_str(), "abb2k.UltimateCustomDash/clickteamSmall.fnt",40, CCTextAlignment::kCCTextAlignmentRight);
    threeCoinsSText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    threeCoinsSText->setScale(0.85f);
    threeCoinsSText->setPosition({50,46});
    threeCoinsSText->setZOrder(1);

    if (mainlayer->_MenuSideBar->threeCoins <= 0){
        threeCoinsS->setOpacity(150);
        threeCoinsSText->setOpacity(150);
    }

    threeCoinsS->addChild(threeCoinsSText);
    threeCoinsS->addChild(threeCoinsSOutline);

    batteryS = CCSprite::create("abb2k.UltimateCustomDash/Battery1.png");
    batteryS->setPosition({33,107});
    batterySOutline = CreateOutline();
    batterySOutline->setPosition({batteryS->getContentSize() / 2});
    batterySOutline->setVisible(mainlayer->_MenuSideBar->batteryActive);

    std::string batterySTextt = std::to_string(mainlayer->_MenuSideBar->batterys);
    batterySText = CCLabelBMFont::create(batterySTextt.c_str(), "abb2k.UltimateCustomDash/clickteamSmall.fnt",40, CCTextAlignment::kCCTextAlignmentRight);
    batterySText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    batterySText->setScale(0.85f);
    batterySText->setPosition({50,46});
    batterySText->setZOrder(1);

    if (mainlayer->_MenuSideBar->batterys <= 0){
        batteryS->setOpacity(150);
        batterySText->setOpacity(150);
    }

    batteryS->addChild(batterySText);
    batteryS->addChild(batterySOutline);

    DDRepelS = CCSprite::create("abb2k.UltimateCustomDash/DD repel1.png");
    DDRepelS->setPosition({33,49});
    DDRepelSOutline = CreateOutline();
    DDRepelSOutline->setPosition({DDRepelS->getContentSize() / 2});
    DDRepelSOutline->setVisible(mainlayer->_MenuSideBar->DDRepelActive);

    std::string DDRepelSTextt = std::to_string(mainlayer->_MenuSideBar->DDRepels);
    DDRepelSText = CCLabelBMFont::create(DDRepelSTextt.c_str(), "abb2k.UltimateCustomDash/clickteamSmall.fnt",40, CCTextAlignment::kCCTextAlignmentRight);
    DDRepelSText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    DDRepelSText->setScale(0.85f);
    DDRepelSText->setPosition({50,46});
    DDRepelSText->setZOrder(1);

    if (mainlayer->_MenuSideBar->DDRepels <= 0){
        DDRepelS->setOpacity(150);
        DDRepelSText->setOpacity(150);
    }

    DDRepelS->addChild(DDRepelSText);
    DDRepelS->addChild(DDRepelSOutline);

    okButton = CCSprite::create("abb2k.UltimateCustomDash/Ok.png");
    okButton->setPosition({33, 9});

    bg->addChild(frigidS);
    bg->addChild(threeCoinsS);
    bg->addChild(batteryS);
    bg->addChild(DDRepelS);
    bg->addChild(okButton);
    this->addChild(bg);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->setTouchPriority(1);
    setKeypadEnabled(true);

    scheduleUpdate();

    return true;
}

void PowerUpsLayer::update(float delta){

    if (getTouchOn(okButton)){
        keyBackClicked();
    }

    customNightLayer* mainlayer = (customNightLayer*) dad;

    if (getTouchOn(frigidS)){
        if (mainlayer->_MenuSideBar->frigids > 0){
            GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/nosepush.wav", 1.0f,1.0f,1.0f);
            if (mainlayer->_MenuSideBar->frigidActive){
                mainlayer->_MenuSideBar->frigidActive = false;
                frigidSOutline->setVisible(mainlayer->_MenuSideBar->frigidActive);
            }
            else {
                mainlayer->_MenuSideBar->frigidActive = true;
                frigidSOutline->setVisible(mainlayer->_MenuSideBar->frigidActive);
            }
        }
    }

    if (getTouchOn(threeCoinsS)){
        if (mainlayer->_MenuSideBar->threeCoins > 0){
            GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/nosepush.wav", 1.0f,1.0f,1.0f);
            if (mainlayer->_MenuSideBar->threeCoinsActive){
                mainlayer->_MenuSideBar->threeCoinsActive = false;
                threeCoinsSOutline->setVisible(mainlayer->_MenuSideBar->threeCoinsActive);
            }
            else {
                mainlayer->_MenuSideBar->threeCoinsActive = true;
                threeCoinsSOutline->setVisible(mainlayer->_MenuSideBar->threeCoinsActive);
            }
        }
    }

    if (getTouchOn(batteryS)){
        if (mainlayer->_MenuSideBar->batterys > 0){
            GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/nosepush.wav", 1.0f,1.0f,1.0f);
            if (mainlayer->_MenuSideBar->batteryActive){
                mainlayer->_MenuSideBar->batteryActive = false;
                batterySOutline->setVisible(mainlayer->_MenuSideBar->batteryActive);
            }
            else {
                mainlayer->_MenuSideBar->batteryActive = true;
                batterySOutline->setVisible(mainlayer->_MenuSideBar->batteryActive);
            }
        }
    }

        if (getTouchOn(DDRepelS)){
        if (mainlayer->_MenuSideBar->DDRepels > 0){
            GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/nosepush.wav", 1.0f,1.0f,1.0f);
            if (mainlayer->_MenuSideBar->DDRepelActive){
                mainlayer->_MenuSideBar->DDRepelActive = false;
                DDRepelSOutline->setVisible(mainlayer->_MenuSideBar->DDRepelActive);
            }
            else {
                mainlayer->_MenuSideBar->DDRepelActive = true;
                DDRepelSOutline->setVisible(mainlayer->_MenuSideBar->DDRepelActive);
            }
        }
    }
}

void PowerUpsLayer::keyBackClicked() {
    customNightLayer* mainLayer = (customNightLayer*)dad;
    mainLayer->_PowerUpsLayer = nullptr;
    GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);

    this->removeMeAndCleanup();
}

CCSprite* PowerUpsLayer::CreateOutline(){
    CCSprite* outline = CCSprite::create("abb2k.UltimateCustomDash/powerupOutlineW.png");

    CCRect outlinesprsRect = outline->getTextureRect();

    CCArray* outlinesprs = CCArray::create();

    outlinesprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/powerupOutlineW.png", outlinesprsRect));
    outlinesprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/powerupOutlineY.png", outlinesprsRect));

    CCAnimation* outlinesprsAnim = CCAnimation::createWithSpriteFrames(outlinesprs, 0.5f);

    CCAction* outlinesprA = CCRepeatForever::create(CCAnimate::create(outlinesprsAnim));

    outline->runAction(outlinesprA);

    return outline;
}

bool PowerUpsLayer::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void PowerUpsLayer::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void PowerUpsLayer::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void PowerUpsLayer::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

bool PowerUpsLayer::getHover(CCNode* node){
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

bool PowerUpsLayer::getTouchOn(CCNode* node, CCTouch* touch){
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

bool PowerUpsLayer::getTouchOn(CCNode* node){
    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}