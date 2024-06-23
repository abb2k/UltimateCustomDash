#include <creditsLayer.h>

#include "customNightLayer.h"

creditsLayer* creditsLayer::create(CCNode* _mainlayer) {
    auto ret = new creditsLayer();
    if (ret && ret->init(_mainlayer)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool creditsLayer::init(CCNode* _mainlayer){

    dad = _mainlayer;

    customNightLayer* mainlayer = (customNightLayer*) dad;

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
    this->addChild(centerP);

    exitButt = CCSprite::create("togglesOnX.png"_spr);
    centerP->addChild(exitButt);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->setTouchPriority(1);
    setKeypadEnabled(true);

    scheduleUpdate();

    return true;
}

void creditsLayer::update(float delta){

    if (getTouchOn(exitButt)){
        keyBackClicked();
    }
}

void creditsLayer::keyBackClicked() {
    customNightLayer* mainLayer = (customNightLayer*)dad;

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(static_cast<CCLayer*>(mainLayer), 10, true);
    mainLayer->setTouchEnabled(true);
    handleTouchPriority(mainLayer);

    mainLayer->_creditsLayer = nullptr;
    FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);

    this->removeMeAndCleanup();
}

bool creditsLayer::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void creditsLayer::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void creditsLayer::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void creditsLayer::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

bool creditsLayer::getHover(CCNode* node){
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

bool creditsLayer::getTouchOn(CCNode* node, CCTouch* touch){
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

bool creditsLayer::getTouchOn(CCNode* node){
    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}