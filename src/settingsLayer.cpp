#include <settingsLayer.h>

#include "customNightLayer.h"
#include "MenuSideBar.h"

settingsLayer* settingsLayer::create(CCNode* _mainlayer, CCNode* _sideMenuLayer) {
    auto ret = new settingsLayer();
    if (ret && ret->init(_mainlayer, _sideMenuLayer)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool settingsLayer::init(CCNode* _mainlayer, CCNode* _sideMenuLayer){

    dad = _mainlayer;
    sideMenuLayer = _sideMenuLayer;

    customNightLayer* mainlayer = (customNightLayer*) dad;
    MenuSideBar* Slayer = (MenuSideBar*) sideMenuLayer;

    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mainlayer);
    mainlayer->clicking = false;
    mainlayer->oneTimeClick = false;

    CCSprite* bg = CCSprite::create("blackscreen.png"_spr);
    bg->setOpacity(150);
    bg->setScale(5);
    CCSize res = CCDirector::sharedDirector()->getWinSize();
    bg->setPosition(res / 2);
    this->addChild(bg);

    centerP = CCNode::create();
    centerP->setPosition(res / 2);
    centerP->setZOrder(1);
    this->addChild(centerP);

    auto Minibg = CCSprite::create("square02_001.png");
    Minibg->setOpacity(150);
    Minibg->setScaleX(5.175f);
    Minibg->setScaleY(3.375f);
    centerP->addChild(Minibg);

    exitButt = CCSprite::create("togglesOnX.png"_spr);
    exitButt->setScale(4.15f);
    exitButt->setPosition({-173, 97});
    centerP->addChild(exitButt);

    showCharInfo = CCSprite::create("togglesOff.png"_spr);
    showCharInfo->setPosition({-34, 24});
    showCharInfo->setScale(2.5f);
    showCharInfo->setVisible(!Slayer->UsingcharInfo);

    showCharInfoOn = CCSprite::create("togglesOnV.png"_spr);
    showCharInfoOn->setPosition({-34, 24});
    showCharInfoOn->setScale(2.5f);
    showCharInfoOn->setVisible(Slayer->UsingcharInfo);

    visualEffects = CCSprite::create("togglesOff.png"_spr);
    visualEffects->setPosition({120, 24});
    visualEffects->setScale(2.5f);
    visualEffects->setVisible(!Slayer->UsingVisualeffects);

    visualEffectsOn = CCSprite::create("togglesOnV.png"_spr);
    visualEffectsOn->setPosition({120, 24});
    visualEffectsOn->setScale(2.5f);
    visualEffectsOn->setVisible(Slayer->UsingVisualeffects);

    volumeSlider = Slider::create(this, menu_selector(settingsLayer::OnVolumeChanged), 0.8f);
    volumeSlider->setValue(Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    volumeSlider->updateBar();
    volumeSlider->setPosition({0, -75});
    centerP->addChild(volumeSlider);

    CCNode* textcont = CCNode::create();
    textcont->setPosition({0,-55});
    centerP->addChild(textcont);

    numberVolumeInput = CCLabelBMFont::create(std::to_string(Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)).c_str(), "clickteamMedium.fnt"_spr);
    textcont->addChild(numberVolumeInput);

    CCLabelBMFont* volLabel = CCLabelBMFont::create("Volume:", "chatFont.fnt");
    volLabel->setPosition({6, 16});
    textcont->addChild(volLabel);

    precentSign = CCSprite::create("%Text.png"_spr);
    precentSign->setScale(2.075f);
    textcont->addChild(precentSign);

    CCLabelBMFont* showCharInfoText = CCLabelBMFont::create("Show\nChar Info:", "chatFont.fnt");
    showCharInfoText->setAnchorPoint(ccp(0.5f,0.5f)); // center align
    showCharInfoText->setPosition({-81, 29});
    centerP->addChild(showCharInfoText);

    CCLabelBMFont* visualEffectsText = CCLabelBMFont::create("Visual\nEffects:", "chatFont.fnt");
    visualEffectsText->setAnchorPoint(ccp(0.5f,0.5f)); // center align
    visualEffectsText->setPosition({81, 29});
    centerP->addChild(visualEffectsText);

    CCLabelBMFont* holdDelToErace = CCLabelBMFont::create("Hold DEL to erase data.", "chatFont.fnt");
    holdDelToErace->setAnchorPoint(ccp(0.5f,0.5f)); // center align
    holdDelToErace->setPosition({0, -118});
    centerP->addChild(holdDelToErace);

    dtext = CCTextFieldTTF::create("blip.mp3"_spr, "chatFont.fnt", 10);
    dtext->setPosition({191, 225});
    dtext->setVisible(false);
    this->addChild(dtext);

    centerP->addChild(showCharInfo);
    centerP->addChild(showCharInfoOn);
    centerP->addChild(visualEffects);
    centerP->addChild(visualEffectsOn);
    centerP->addChild(holdDelToErace);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->setTouchPriority(1);
    setKeypadEnabled(true);

    scheduleUpdate();

    return true;
}

void settingsLayer::update(float delta){
    customNightLayer* mainlayer = (customNightLayer*) dad;
    MenuSideBar* Slayer = (MenuSideBar*) sideMenuLayer;

    if (getTouchOn(exitButt)){
        keyBackClicked();
    }

    if (getTouchOn(showCharInfo)){
        if (Slayer->UsingcharInfo){
            Slayer->UsingcharInfo = false;
            Mod::get()->setSavedValue<bool>("Show_Character_Descriptions", false);
            showCharInfo->setVisible(true);
            showCharInfoOn->setVisible(false);
        }
        else{
            Slayer->UsingcharInfo = true;
            Mod::get()->setSavedValue<bool>("Show_Character_Descriptions", true);
            showCharInfo->setVisible(false);
            showCharInfoOn->setVisible(true);
        }
    }

    if (getTouchOn(visualEffects)){
        if (Slayer->UsingVisualeffects){
            Slayer->UsingVisualeffects = false;
            Mod::get()->setSavedValue<bool>("Visual_Effects", false);
            visualEffects->setVisible(true);
            visualEffectsOn->setVisible(false);
        }
        else{
            Slayer->UsingVisualeffects = true;
            Mod::get()->setSavedValue<bool>("Visual_Effects", true);
            visualEffects->setVisible(false);
            visualEffectsOn->setVisible(true);
        }
    }

    float volume = volumeSlider->m_touchLogic->m_thumb->getValue() * 100;
    std::stringstream numberVolumeInputFixed;
    numberVolumeInputFixed << std::fixed << std::setprecision(0) << volume;
    numberVolumeInput->setString(numberVolumeInputFixed.str().c_str());

    if (volume >= 9.5f && volume < 99.5f){
        //if has 2 numbas
        precentSign->setPosition({16, 0});
    }
    else if (volume >= 99.5f){
        //if at 100
        precentSign->setPosition({21, 0});
    }
    else {
        //if has 1 numba
        precentSign->setPosition({12, 0});
    }
}

void settingsLayer::keyBackClicked() {
    
    customNightLayer* mainLayer = (customNightLayer*)dad;

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(static_cast<CCLayer*>(mainLayer), 10, true);
    mainLayer->setTouchEnabled(true);
    handleTouchPriority(mainLayer);

    mainLayer->_settingsLayer = nullptr;
    mainLayer->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));

    this->removeMeAndCleanup();
}

bool settingsLayer::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void settingsLayer::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void settingsLayer::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void settingsLayer::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

bool settingsLayer::getHover(CCNode* node){
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

bool settingsLayer::getTouchOn(CCNode* node, CCTouch* touch){
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

bool settingsLayer::getTouchOn(CCNode* node){
    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}

void settingsLayer::OnVolumeChanged(CCObject* mobject){
    float fixedThing = volumeSlider->m_touchLogic->m_thumb->getValue();
    if (fixedThing < 0){
        fixedThing = 0;
        volumeSlider->setValue(fixedThing);
        volumeSlider->updateBar();
    }
    if (fixedThing > 1){
        fixedThing = 1;
        volumeSlider->setValue(fixedThing);
        volumeSlider->updateBar();
    }
    Mod::get()->setSavedValue("Game_Volume", fixedThing);
    numberVolumeInput->setString(std::to_string(fixedThing * 100).c_str());
}