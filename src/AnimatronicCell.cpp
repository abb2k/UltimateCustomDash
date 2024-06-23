
#include <AnimatronicCell.h>
#include <AnimatronicCellContainer.h>
#include "customNightLayer.h"
AnimatronicCell* AnimatronicCell::create(std::string animatronicImageName, std::string name, std::string discription) {
    auto ret = new AnimatronicCell();
    if (ret && ret->init(animatronicImageName, name, discription)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool AnimatronicCell::init(std::string animatronicImageName, std::string name, std::string discription){

    std::string animatronicPath = "abb2k.UltimateCustomDash/" + animatronicImageName;

    Name = name;
    Discription = discription;

    CellOutline = CCSprite::create("iconCell.png"_spr);
    CellOutlineSelected = CCSprite::create("iconCellSelected.png"_spr);
    CellOutlineSelected->setVisible(false);

    AnimatronicSprite = CCSprite::create(animatronicPath.c_str());

    std::string AILevelString = std::to_string(AILevel);

    AILevelText = CCLabelBMFont::create(AILevelString.c_str(), "abb2k.UltimateCustomDash/clickteamSmall.fnt",40, CCTextAlignment::kCCTextAlignmentRight);
    AILevelText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    AILevelText->setScale(1);
    AILevelText->setPosition({16,-18});
    AILevelText->setZOrder(1);
//
    buttonUpspr = CCSprite::create("abb2k.UltimateCustomDash/arrowAdd1.png");

    CCRect buttonUpsprsRect = buttonUpspr->getTextureRect();

    CCArray* buttonUpsprs = CCArray::create();

    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd1.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd2.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd3.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd4.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd5.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd6.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd7.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd8.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd9.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd10.png", buttonUpsprsRect));
    buttonUpsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowAdd11.png", buttonUpsprsRect));

    CCAnimation* buttonUpsprsAnim = CCAnimation::createWithSpriteFrames(buttonUpsprs, 0.1f);

    CCAction* buttonUpsprA = CCRepeatForever::create(CCAnimate::create(buttonUpsprsAnim));

    buttonUpspr->runAction(buttonUpsprA);

    buttonUpspr->setScale(0.9f);
    buttonUpspr->setPosition({-10,-12});
//down
    buttonDownspr = CCSprite::create("abb2k.UltimateCustomDash/arrowRemove1.png");

    CCRect buttonDownsprsRect = buttonDownspr->getTextureRect();

    CCArray* buttonDownsprs = CCArray::create();

    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove1.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove2.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove3.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove4.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove5.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove6.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove7.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove8.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove9.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove10.png", buttonDownsprsRect));
    buttonDownsprs->addObject(CCSpriteFrame::create("abb2k.UltimateCustomDash/arrowRemove11.png", buttonDownsprsRect));

    CCAnimation* buttonDownsprsAnim = CCAnimation::createWithSpriteFrames(buttonDownsprs, 0.1f);

    CCAction* buttonDownsprA = CCRepeatForever::create(CCAnimate::create(buttonDownsprsAnim));

    buttonDownspr->runAction(buttonDownsprA);

    buttonDownspr->setScale(0.9f);
    buttonDownspr->setPosition({-10,-19});

    this->addChild(AnimatronicSprite);
    this->addChild(CellOutline);
    this->addChild(CellOutlineSelected);
    this->addChild(AILevelText);
    this->addChild(buttonUpspr);
    this->addChild(buttonDownspr);

    this->setPosition({261, 136});

    std::string debugString = std::to_string(0);
    debugText = CCTextFieldTTF::create(debugString.c_str(), "chatFont.fnt", 4);
    debugText->setVisible(false);

    this->addChild(debugText);

    CellOutlineSelected->setVisible(false);
    CellOutline->setVisible(true);
    buttonDownspr->setVisible(false);
    buttonUpspr->setVisible(false);

    scheduleUpdate();

    return true;
}

void AnimatronicCell::UpButton(){
    if (AILevel != 20){
        AILevel += 1;
        this->addChild(AudioSource::createEffect("click2.mp3"_spr, AudioSource::VolumeChannel::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
    }
}

void AnimatronicCell::DownButton(){
    if (AILevel != 0){
        AILevel -= 1;
        this->addChild(AudioSource::createEffect("click2.mp3"_spr, AudioSource::VolumeChannel::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
    }
}

void AnimatronicCell::OnTouchended(){
    OnTouchDown = false;
    SpeedUpLevelsDown = false;
    SpeedUpLevelsUp = false;
    startingButtonSpeedup = 0.25f;
    touchDouble = false;
}

void AnimatronicCell::update(float deltaTime){
    AnimatronicCellContainer* parentContainer = (AnimatronicCellContainer*)parent;

    customNightLayer* mainLayer = (customNightLayer*)parentContainer->dad;

    std::string AILevelString = std::to_string(AILevel);
    AILevelText->setString(AILevelString.c_str());

    //aiLevel based opacity
    if (AILevel == 0){
        AnimatronicSprite->setOpacity(100);
        //CellOutline->setOpacity(130);
        AILevelText->setOpacity(100);
    }
    else{
        //link to the flashing effect

        AnimatronicSprite->setOpacity(parentContainer->OpacityFlash);
        //CellOutline->setOpacity(parentContainer->OpacityFlash);
        AILevelText->setOpacity(parentContainer->OpacityFlash);
    }

    if (getHover(AnimatronicSprite)){
        if (!isHovering){
            getHoverEnter();
        }
        isHovering = true;
        this->setZOrder(2);
        if (mainLayer->_creditsLayer == nullptr){
            if (mainLayer->_settingsLayer == nullptr){
                CellOutlineSelected->setVisible(true);
                CellOutline->setVisible(false);
            }
        }
        if (mainLayer->_officeLayer == nullptr){
            if (mainLayer->_PowerUpsLayer == nullptr){
                if (mainLayer->_challenges == nullptr){
                    if (mainLayer->_creditsLayer == nullptr){
                        if (mainLayer->_settingsLayer == nullptr){
                            buttonDownspr->setVisible(true);
                            buttonUpspr->setVisible(true);
                        }
                    }
                }
            }
        }
    }
    else {
        if (isHovering){
            getHoverExit();
        }
        isHovering = false;
        this->setZOrder(0);
        CellOutlineSelected->setVisible(false);
        CellOutline->setVisible(true);
        buttonDownspr->setVisible(false);
        buttonUpspr->setVisible(false);
    }

//up
    if (getTouchOn(buttonUpspr)){
        if (!OnTouchDown){
            OnTouchDown = true;
            startingButtonSpeedup = 0.25f;
            UpButton();
            SpeedUpLevelsUp = true;
        }
        
    }

//down
    if (getTouchOn(buttonDownspr)){
        if (!OnTouchDown){
            OnTouchDown = true;
            startingButtonSpeedup = 0.25f;
            DownButton();
            SpeedUpLevelsDown = true;
        }
    }

    if (startingButtonSpeedup > 0 && SpeedUpLevelsUp){
        startingButtonSpeedup -= deltaTime;
    }

    if (SpeedUpLevelsUp && startingButtonSpeedup <= 0){
        if (buttonHoldTimeDelay > 0){
            buttonHoldTimeDelay -= deltaTime;

            if (!getHover(buttonUpspr)){
                SpeedUpLevelsUp = false;
            }
        }
        else {
            UpButton();
            buttonHoldTimeDelay = 0.025f;
        }
    }
    

    if (startingButtonSpeedup > 0 && SpeedUpLevelsDown){
        startingButtonSpeedup -= deltaTime;
    }

    if (SpeedUpLevelsDown && startingButtonSpeedup <= 0){
        if (buttonHoldTimeDelay > 0){
            buttonHoldTimeDelay -= deltaTime;

            if (!getHover(buttonDownspr)){
                SpeedUpLevelsDown = false;
            }
        }
        else {
            DownButton();
            buttonHoldTimeDelay = 0.025f;
        }
    }

    if (getTouchOnDouble(buttonUpspr)){
        AILevel = 20;
        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::VolumeChannel::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
    }
    if (getTouchOnDouble(buttonDownspr)){
        AILevel = 0;
        this->addChild(AudioSource::createEffect("blip.mp3"_spr, AudioSource::VolumeChannel::Custom, 1.5f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f)));
    }

    if (!mainLayer->clicking){
        OnTouchended();
    }

    std::stringstream ss1, ss2, ss3;  
    ss1 << std::boolalpha << mainLayer->clicking;  
    ss2 << std::boolalpha << SpeedUpLevelsDown;
    ss3 << std::boolalpha << SpeedUpLevelsUp;

    std::string Debugmessage = "clicking: " + ss1.str() + "\n" + " SpeedUpLevelsDown: " + ss2.str() + "\n" + " SpeedUpLevelsUp: " + ss3.str() + "\n" + " startingButtonSpeedup: " + std::to_string(startingButtonSpeedup) + "\n" + " buttonHoldTimeDelay: " + std::to_string(buttonHoldTimeDelay);

    debugText->setString(Debugmessage.c_str());
}

bool AnimatronicCell::getHover(CCNode* node){
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

bool AnimatronicCell::getTouchOn(CCNode* node, CCTouch* touch){
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

bool AnimatronicCell::getTouchOn(CCNode* node){
    AnimatronicCellContainer* parentContainer = (AnimatronicCellContainer*)parent;
    customNightLayer* mainLayer = (customNightLayer*)parentContainer->dad;

    if (mainLayer->clicking){
        if (getHover(node)){
            return true;
        }
    }
    return false;
}

void AnimatronicCell::getHoverEnter(){
    AnimatronicCellContainer* parentContainer = (AnimatronicCellContainer*)parent;
    customNightLayer* mainLayer = (customNightLayer*)parentContainer->dad;

    if (mainLayer->_MenuSideBar->UsingcharInfo){
        if (mainLayer->_creditsLayer == nullptr){
            if (mainLayer->_settingsLayer == nullptr){
                discripBox = discriptionBox::create(Name, Discription);
                if (!lastInRow){
                    discripBox->setPosition({55,0});
                }
                else {
                    discripBox->setPosition({-55,0});
                }

                this->addChild(discripBox);
            }
        }
    }
}

void AnimatronicCell::getHoverExit(){
    AnimatronicCellContainer* parentContainer = (AnimatronicCellContainer*)parent;
    customNightLayer* mainLayer = (customNightLayer*)parentContainer->dad;

    if (mainLayer->_MenuSideBar->UsingcharInfo){
        if (discripBox != nullptr){
            discripBox->removeMeAndCleanup();
            discripBox = nullptr;
        }
    }
}

bool AnimatronicCell::getTouchOnDouble(CCNode* node){
    AnimatronicCellContainer* parentContainer = (AnimatronicCellContainer*)parent;
    customNightLayer* mainLayer = (customNightLayer*)parentContainer->dad;

    if (mainLayer->clicking && !touchDouble){
        if (getHover(node)){
            touchDouble = true;

            if (mainLayer->doubleClickTimer <= 0){
                mainLayer->doubleClickTimer = 0.2f;
            }
            else {
                return true;
            }  
        }
    }
    return false;
}