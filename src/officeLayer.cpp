#include <officeLayer.h>

#include "customNightLayer.h"

officeLayer* officeLayer::create(CCNode* _mainlayer) {
    auto ret = new officeLayer();
    if (ret && ret->init(_mainlayer)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool officeLayer::init(CCNode* _mainlayer){

    dad = _mainlayer;

    customNightLayer* mainlayer = (customNightLayer*)dad;

    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mainlayer);
    mainlayer->clicking = false;
    mainlayer->oneTimeClick = false;

    CCSprite* bg = CCSprite::create("abb2k.UltimateCustomDash/sidebarBG.png");
    bg->setPosition({526, 161});
    bg->setScaleX(1.175f);
    bg->setScaleY(1.21f);

    defaultOffice = CCSprite::create("abb2k.UltimateCustomDash/defaultOffice.png");
    defaultOffice->setPosition({33,223});

    fnafSisLocOffice = CCSprite::create("abb2k.UltimateCustomDash/sisterlocoffice.png");
    fnafSisLocOffice->setPosition({33,165});

    fnaf3Office = CCSprite::create("abb2k.UltimateCustomDash/fnaf3office.png");
    fnaf3Office->setPosition({33,107});

    fnaf4Office = CCSprite::create("abb2k.UltimateCustomDash/fnaf4office.png");
    fnaf4Office->setPosition({33,49});

    p2000 = CCSprite::create("abb2k.UltimateCustomDash/2000PointsLock.png");
    p2000->setPosition({33,165});

    p5000 = CCSprite::create("abb2k.UltimateCustomDash/5000PointsLock.png");
    p5000->setPosition({33,107});

    p8000 = CCSprite::create("abb2k.UltimateCustomDash/8000PointsLock.png");
    p8000->setPosition({33,49});

    if (mainlayer->_MenuSideBar->highScore < 2000){
        p2000->setVisible(true);
        fnafSisLocOffice->setOpacity(150);
    }
    else{
        p2000->setVisible(false);
        fnafSisLocOffice->setOpacity(255);
    }

    if (mainlayer->_MenuSideBar->highScore < 5000){
        p5000->setVisible(true);
        fnaf3Office->setOpacity(150);
    }
    else{
        p5000->setVisible(false);
        fnaf3Office->setOpacity(255);
    }

    if (mainlayer->_MenuSideBar->highScore < 8000){
        p8000->setVisible(true);
        fnaf4Office->setOpacity(150);
    }
    else{
        p8000->setVisible(false);
        fnaf4Office->setOpacity(255);
    }

    outline = CCSprite::create("abb2k.UltimateCustomDash/officeOutlineWhite.png");

    CCRect outlinesprsRect = outline->getTextureRect();

    CCArray* outlinesprs = CCArray::create();

    outlinesprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/officeOutlineWhite.png", outlinesprsRect));
    outlinesprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/officeOutlineYellow.png", outlinesprsRect));

    CCAnimation* outlinesprsAnim = CCAnimation::createWithSpriteFrames(outlinesprs, 0.5f);

    CCAction* outlinesprA = CCRepeatForever::create(CCAnimate::create(outlinesprsAnim));

    outline->runAction(outlinesprA);

    float outlinePosition = 223 - (58 * mainlayer->OfficeSelected);

    outline->setPosition({33,outlinePosition});

    okButton = CCSprite::create("abb2k.UltimateCustomDash/Ok.png");
    okButton->setPosition({33, 9});

    bg->addChild(defaultOffice);
    bg->addChild(fnafSisLocOffice);
    bg->addChild(fnaf3Office);
    bg->addChild(fnaf4Office);
    bg->addChild(p2000);
    bg->addChild(p5000);
    bg->addChild(p8000);
    bg->addChild(outline);
    bg->addChild(okButton);
    this->addChild(bg);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->setTouchPriority(100);
    setKeypadEnabled(true);

    scheduleUpdate();

    return true;
}

void officeLayer::update(float delta){

    customNightLayer* mainlayer = (customNightLayer*) dad;

    if (getTouchOn(okButton)){
        keyBackClicked();
    }

    float outlinePosition = 223 - (58 * mainlayer->OfficeSelected);

    outline->setPosition({33,outlinePosition});

    if (getTouchOn(defaultOffice)){
        mainlayer->OfficeSelected = 0;
        this->addChild(AudioSource::createEffect("Office Equipment_NF060059_371612.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
    }

    if (mainlayer->_MenuSideBar->highScore < 2000){
        p2000->setVisible(true);
        fnafSisLocOffice->setOpacity(150);
    }
    else{
        p2000->setVisible(false);
        fnafSisLocOffice->setOpacity(255);

        if (getTouchOn(fnafSisLocOffice)){
            mainlayer->OfficeSelected = 1;
            this->addChild(AudioSource::createEffect("Office Equipment_NF060059_371612.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        }
    }

    if (mainlayer->_MenuSideBar->highScore < 5000){
        p5000->setVisible(true);
        fnaf3Office->setOpacity(150);
    }
    else{
        p5000->setVisible(false);
        fnaf3Office->setOpacity(255);

        if (getTouchOn(fnaf3Office)){
            mainlayer->OfficeSelected = 2;
            this->addChild(AudioSource::createEffect("Office Equipment_NF060059_371612.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        }
    }

    if (mainlayer->_MenuSideBar->highScore < 8000){
        p8000->setVisible(true);
        fnaf4Office->setOpacity(150);
    }
    else{
        p8000->setVisible(false);
        fnaf4Office->setOpacity(255);

        if (getTouchOn(fnaf4Office)){
            mainlayer->OfficeSelected = 3;
            this->addChild(AudioSource::createEffect("Office Equipment_NF060059_371612.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
        }
    }

}

void officeLayer::keyBackClicked() {
    customNightLayer* mainLayer = (customNightLayer*)dad;

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(static_cast<CCLayer*>(mainLayer), 10, true);
    mainLayer->setTouchEnabled(true);
    handleTouchPriority(mainLayer);

    mainLayer->_officeLayer = nullptr;
    mainLayer->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));

    this->removeMeAndCleanup();
}

bool officeLayer::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void officeLayer::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void officeLayer::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void officeLayer::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

bool officeLayer::getHover(CCNode* node){
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

bool officeLayer::getTouchOn(CCNode* node, CCTouch* touch){
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

bool officeLayer::getTouchOn(CCNode* node){

    customNightLayer* mainLayer = (customNightLayer*)dad;

    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}