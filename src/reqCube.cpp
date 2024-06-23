#include "reqCube.h"

reqCube* reqCube::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new reqCube();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool reqCube::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    cube = CCSprite::create("reqcube.png"_spr);
    cube->setZOrder(3);
    cube->setVisible(false);
    cube->setPosition({257, 192});
    cube->setScale(0.625f);
    mainLayer->World->addChild(cube);

    mainLayer->PreloadImages(std::vector<std::string>{
        "reqcube.jpg0001.png"_spr,
        "reqcube.jpg0002.png"_spr,
        "reqcube.jpg0003.png"_spr,
        "reqcube.jpg0004.png"_spr,
        "reqcube.jpg0005.png"_spr,
        "reqcube.jpg0006.png"_spr,
        "reqcube.jpg0007.png"_spr,
        "reqcube.jpg0008.png"_spr,
        "reqcube.jpg0009.png"_spr,
        "reqcube.jpg0010.png"_spr,
        "reqcube.jpg0011.png"_spr,
        "reqcube.jpg0012.png"_spr,
        "reqcube.jpg0013.png"_spr,
        "reqcube.jpg0014.png"_spr,
        "reqcube.jpg0015.png"_spr,
        "reqcube.jpg0016.png"_spr,
        "reqcube.jpg0017.png"_spr,
        "reqcube.jpg0018.png"_spr,
        "reqcube.jpg0019.png"_spr,
        "reqcube.jpg0020.png"_spr,
    });

    CCSize res = CCDirector::sharedDirector()->getWinSize();

    renderTexture = CCRenderTexture::create(res.width + 1, res.height + 1, cube->getTexture()->getPixelFormat());
    renderTexture->setVisible(false);
    this->addChild(renderTexture);

    scheduleUpdate();

    return true;
}

void reqCube::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (mainLayer->LookingAtCams){
            if (!rollWakeChance){
                rollWakeChance = true;
                int oppCalc = 1 + (rand() % 23);
                if (_AILevel != 0 && _AILevel >= oppCalc){
                    OnOpportunity();
                }
            }
        }
        else {
            rollWakeChance = false;
        }
        if (inRoom && !jumpscared){
            if (mainLayer->getTouchOnSprite(cube, renderTexture)){
                cube->stopAllActions();
                inRoom = false;

                auto animation = CCSequence::create(CCEaseOut::create(CCMoveBy::create(0.1f, {0, 5}), 1.5f), CCSpawn::create(CCEaseIn::create(CCMoveBy::create(0.1f, {0, -5}), 1.5f), CCScaleTo::create(0.1f, 0), nullptr), nullptr);
                
                cube->runAction(animation);
                
                mainLayer->fazCoins += 1;
                FMODAudioEngine::sharedEngine()->playEffect("Pop_Sharp_Quick_Small_Comical.mp3"_spr, 1.0f,1.0f,1.0f);
            }
        }
    }

    if (mainLayer->DEATHSCREEN || mainLayer->inJumpscare || mainLayer->nightComplete){
        cube->stopAllActions();
    }
}

void reqCube::OnOpportunity(){
    if (!inRoom && !jumpscared){
        inRoom = true;
        cube->stopAllActions();
        cube->setVisible(true);
        cube->setPosition({257, 192});
        cube->setScale(0.625f);
        cube->runAction(CCSequence::create(CCDelayTime::create(5), CCCallFunc::create(this, callfunc_selector(reqCube::disableCams)), nullptr));
    }
}

void reqCube::disableCams(){
    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
        0.075f, 29, new std::string[]{
            "reqcube.jpg0001.png"_spr,
            "reqcube.jpg0002.png"_spr,
            "reqcube.jpg0003.png"_spr,
            "reqcube.jpg0004.png"_spr,
            "reqcube.jpg0005.png"_spr,
            "reqcube.jpg0006.png"_spr,
            "reqcube.jpg0007.png"_spr,
            "reqcube.jpg0008.png"_spr,
            "reqcube.jpg0009.png"_spr,
            "reqcube.jpg0010.png"_spr,
            "reqcube.jpg0011.png"_spr,
            "reqcube.jpg0012.png"_spr,
            "reqcube.jpg0013.png"_spr,
            "reqcube.jpg0014.png"_spr,
            "reqcube.jpg0015.png"_spr,
            "reqcube.jpg0016.png"_spr,
            "reqcube.jpg0017.png"_spr,
            "reqcube.jpg0018.png"_spr,
            "reqcube.jpg0019.png"_spr,
            "reqcube.jpg0020.png"_spr,
            "reqcube.jpg0019.png"_spr,
            "reqcube.jpg0018.png"_spr,
            "reqcube.jpg0017.png"_spr,
            "reqcube.jpg0016.png"_spr,
            "reqcube.jpg0015.png"_spr,
            "reqcube.jpg0014.png"_spr,
            "reqcube.jpg0013.png"_spr,
            "reqcube.jpg0012.png"_spr,
            "reqcube.jpg0011.png"_spr,
        }
    ), "reqcubeSound.mp3"_spr, true, true, false);
    jumpscared = true;
    cube->setVisible(false);
    inRoom = false;
    mainLayer->camsDisabled = true;
    cube->runAction(CCSequence::create(CCDelayTime::create(9), CCCallFunc::create(this, callfunc_selector(reqCube::reEnableCams)), nullptr));
}

void reqCube::reEnableCams(){
    mainLayer->camsDisabled = false;
    jumpscared = false;
}