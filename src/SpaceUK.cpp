#include "SpaceUK.h"

SpaceUK* SpaceUK::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new SpaceUK();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SpaceUK::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    spaceUKIcon = CCSprite::create("spaceIcon.png"_spr);
    spaceUKIcon->setPosition({-97, -90});
    spaceUKIcon->setScale(3.45f);
    spaceUKIcon->setRotationX(-8);
    spaceUKIcon->setRotationY(4);
    mainLayer->Cam08->addChild(spaceUKIcon);

    CCPoint* center = new CCPoint[]{
        {-132,-9},
        {-138,70},
        {23,69},
        {21,-17}
    };
    ccColor4F col = {255,255,255,255};

    auto stencil = CCDrawNode::create();
    stencil->drawPolygon(center, 4, col, 1.0f, col);

    auto clipper = CCClippingNode::create();
    clipper->setStencil(stencil);
    mainLayer->Cam08->addChild(clipper);

    MaskPCLayer = CCNode::create();
    MaskPCLayer->setPosition({((center[1].x + center[2].x) / 2), ((center[1].y + center[3].y) / 2)});
    MaskPCLayer->setRotationX(-3);
    MaskPCLayer->setRotationY(3);
    clipper->addChild(MaskPCLayer);

    SmallCam01 = CCSprite::create("Cam01.png"_spr);
    SmallCam01->setScale(0.675f);
    MaskPCLayer->addChild(SmallCam01);

    SmallCam02 = CCSprite::create("Cam02.png"_spr);
    SmallCam02->setScale(0.675f);
    MaskPCLayer->addChild(SmallCam02);

    SmallCam03 = CCSprite::create("Cam03.png"_spr);
    SmallCam03->setScale(0.675f);
    MaskPCLayer->addChild(SmallCam03);

    CCSprite* SmallmapS = CCSprite::create("smallmap.png"_spr);
    SmallmapS->setZOrder(3);
    SmallmapS->setPosition({52, 21});
    SmallmapS->setScale(2.45f);
    MaskPCLayer->addChild(SmallmapS);

    SmallCam01ButtonCont = CCNode::create();
    SmallCam01ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    SmallCam01ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    SmallCam01ButtonText = CCSprite::create("Cam01Text.png"_spr);
    SmallmapS->addChild(SmallCam01ButtonCont);
    SmallCam01ButtonText->setPosition({-6, 2});
    SmallCam01ButtonCont->addChild(SmallCam01ButtonOff);
    SmallCam01ButtonCont->addChild(SmallCam01ButtonOn);
    SmallCam01ButtonCont->addChild(SmallCam01ButtonText);
    SmallCam01ButtonText->setZOrder(1);
    SmallCam01ButtonCont->setPosition({1, 8});
    SmallCam01ButtonCont->setScale(0.3f);

    SmallCam02ButtonCont = CCNode::create();
    SmallCam02ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    SmallCam02ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    SmallCam02ButtonText = CCSprite::create("Cam02Text.png"_spr);
    SmallmapS->addChild(SmallCam02ButtonCont);
    SmallCam02ButtonText->setPosition({-6, 2});
    SmallCam02ButtonCont->addChild(SmallCam02ButtonOff);
    SmallCam02ButtonCont->addChild(SmallCam02ButtonOn);
    SmallCam02ButtonCont->addChild(SmallCam02ButtonText);
    SmallCam02ButtonText->setZOrder(1);
    SmallCam02ButtonCont->setPosition({17, 8});
    SmallCam02ButtonCont->setScale(0.3f);

    SmallCam03ButtonCont = CCNode::create();
    SmallCam03ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    SmallCam03ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    SmallCam03ButtonText = CCSprite::create("Cam03Text.png"_spr);
    SmallmapS->addChild(SmallCam03ButtonCont);
    SmallCam03ButtonText->setPosition({-6, 2});
    SmallCam03ButtonCont->addChild(SmallCam03ButtonOff);
    SmallCam03ButtonCont->addChild(SmallCam03ButtonOn);
    SmallCam03ButtonCont->addChild(SmallCam03ButtonText);
    SmallCam03ButtonText->setZOrder(1);
    SmallCam03ButtonCont->setPosition({9, 17});
    SmallCam03ButtonCont->setScale(0.3f);

    CCSprite* SmallCamStatic = mainLayer->CreateAnimatedSprite(0.04f, 6, new std::string[]{
        "static1.png"_spr,
        "static2.png"_spr,
        "static3.png"_spr,
        "static4.png"_spr,
        "static5.png"_spr,
        "static6.png"_spr
    });
    SmallCamStatic->setScale(2.5f);
    SmallCamStatic->setZOrder(2);
    SmallCamStatic->setOpacity(50);
    MaskPCLayer->addChild(SmallCamStatic);

    dtext = CCTextFieldTTF::create("", "chatFont.fnt", 15);
    dtext->setPosition({180, 80});
    //dtext->setVisible(false);
    this->addChild(dtext);

    updateMiniCams(SmallCams::SmallCam1);

    currZBotPos = RandomPosition();

    ZBotS = CCSprite::create("zbor.png"_spr);
    ZBotS->setScale(0.275f);
    switch (currZBotPos)
    {
    case SmallCams::SmallCam1:
        SmallCam01->addChild(ZBotS);
        ZBotS->setPosition({183, 38});
        ZBotS->setRotationX(3);
        ZBotS->setRotationY(-32);
        break;

    case SmallCams::SmallCam2:
        SmallCam02->addChild(ZBotS);
        ZBotS->setPosition({124, 55});
        ZBotS->setRotationX(0);
        ZBotS->setRotationY(12);
        break;

    case SmallCams::SmallCam3:
        SmallCam03->addChild(ZBotS);
        ZBotS->setPosition({156, 65});
        ZBotS->setRotationX(18);
        ZBotS->setRotationY(-35);
        break;
    }

    //1
    CCNode* b1 = CCNode::create();
    b1->setScale(0.5f);
    b1->setPosition({1, 3});
    SmallmapS->addChild(b1);

    CblockCam1 = CCSprite::create("closeSmallDoor.png"_spr);
    b1->addChild(CblockCam1);

    OblockCam1 = CCSprite::create("OpenSmallDoor.png"_spr);
    b1->addChild(OblockCam1);

    //2
    CCNode* b2 = CCNode::create();
    b2->setScale(0.5f);
    b2->setPosition({17, 3});
    SmallmapS->addChild(b2);

    CblockCam2 = CCSprite::create("closeSmallDoor.png"_spr);
    b2->addChild(CblockCam2);

    OblockCam2 = CCSprite::create("OpenSmallDoor.png"_spr);
    b2->addChild(OblockCam2);

    //3
    CCNode* b3 = CCNode::create();
    b3->setScale(0.5f);
    b3->setPosition({9, 12});
    SmallmapS->addChild(b3);

    CblockCam3 = CCSprite::create("closeSmallDoor.png"_spr);
    b3->addChild(CblockCam3);

    OblockCam3 = CCSprite::create("OpenSmallDoor.png"_spr);
    b3->addChild(OblockCam3);

    CCRepeat* a = mainLayer->CreateAnimAction(0.01f, 2, new std::string[]{
        "spacegameover.png"_spr,
        "spacegameover.png"_spr
    });

    if (_AILevel == 0){
        MaskPCLayer->setVisible(false);
        spaceUKIcon->setVisible(false);
    }
    else {
        mainLayer->Cam08S->runAction(a);
    }
    int randCam = rand() % 3;
    updateMiniCams((SmallCams)randCam);

    scheduleUpdate();

    return true;
}

void SpaceUK::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (opportunityTimer > 0){
            opportunityTimer -= delta;
        }
        else{
            opportunityTimer = _opportunity;
            int oppCalc = 1 + (rand() % 22);
            if (_AILevel != 0 && _AILevel >= oppCalc){
                OnOpportunity();
            }
        }

        if (mainLayer->getTouchOn(SmallCam01ButtonOn)){
            updateMiniCams(SmallCams::SmallCam1);
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);
        }
        if (mainLayer->getTouchOn(SmallCam02ButtonOn)){
            updateMiniCams(SmallCams::SmallCam2);
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);
        }
        if (mainLayer->getTouchOn(SmallCam03ButtonOn)){
            updateMiniCams(SmallCams::SmallCam3);
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);
        }
        if (mainLayer->getTouchOn(CblockCam1)){
            CloseSmallDoor(blockPoses::blockCam1);
            FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr, 1.0f,1.0f,1.0f);
        }
        if (mainLayer->getTouchOn(CblockCam2)){
            CloseSmallDoor(blockPoses::blockCam2);
            FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr, 1.0f,1.0f,1.0f);
        }
        if (mainLayer->getTouchOn(CblockCam3)){
            CloseSmallDoor(blockPoses::blockCam3);
            FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr, 1.0f,1.0f,1.0f);
        }
    }
}

void SpaceUK::OnOpportunity(){
    switch (currZBotPos)
    {
    case SmallCams::SmallCam1:
        if (currBlockPos == blockPoses::blockCam1){
            changeZBotPosition();
        }
        else {
            kill();
        }
        break;

    case SmallCams::SmallCam2:
        if (currBlockPos == blockPoses::blockCam2){
            changeZBotPosition();
        }
        else {
            kill();
        }
        break;

    case SmallCams::SmallCam3:
        if (currBlockPos == blockPoses::blockCam3){
            changeZBotPosition();
        }
        else {
            kill();
        }
        break;
    }
}

void SpaceUK::updateMiniCams(SmallCams cam){
    currCamera = cam;
    switch (currCamera)
    {
    case SmallCams::SmallCam1:
        SmallCam01->setVisible(true);
        SmallCam02->setVisible(false);
        SmallCam03->setVisible(false);
        SmallCam01ButtonOff->setVisible(false);
        SmallCam01ButtonOn->setVisible(true);
        SmallCam02ButtonOff->setVisible(true);
        SmallCam02ButtonOn->setVisible(false);
        SmallCam03ButtonOff->setVisible(true);
        SmallCam03ButtonOn->setVisible(false);
        break;

    case SmallCams::SmallCam2:
        SmallCam01->setVisible(false);
        SmallCam02->setVisible(true);
        SmallCam03->setVisible(false);
        SmallCam01ButtonOff->setVisible(true);
        SmallCam01ButtonOn->setVisible(false);
        SmallCam02ButtonOff->setVisible(false);
        SmallCam02ButtonOn->setVisible(true);
        SmallCam03ButtonOff->setVisible(true);
        SmallCam03ButtonOn->setVisible(false);
        break;

    case SmallCams::SmallCam3:
        SmallCam01->setVisible(false);
        SmallCam02->setVisible(false);
        SmallCam03->setVisible(true);
        SmallCam01ButtonOff->setVisible(true);
        SmallCam01ButtonOn->setVisible(false);
        SmallCam02ButtonOff->setVisible(true);
        SmallCam02ButtonOn->setVisible(false);
        SmallCam03ButtonOff->setVisible(false);
        SmallCam03ButtonOn->setVisible(true);
        break;
    
    default:
        break;
    }
}

void SpaceUK::changeZBotPosition(){
    currZBotPos = RandomPosition();

    switch (currZBotPos)
    {
    case SmallCams::SmallCam1:
        ZBotS->retain();
        ZBotS->removeFromParent();
        SmallCam01->addChild(ZBotS);
        ZBotS->release();
        ZBotS->setPosition({183, 38});
        ZBotS->setRotationX(3);
        ZBotS->setRotationY(-32);
        break;

    case SmallCams::SmallCam2:
        ZBotS->retain();
        ZBotS->removeFromParent();
        SmallCam02->addChild(ZBotS);
        ZBotS->release();
        ZBotS->setPosition({124, 55});
        ZBotS->setRotationX(0);
        ZBotS->setRotationY(12);
        break;

    case SmallCams::SmallCam3:
        ZBotS->retain();
        ZBotS->removeFromParent();
        SmallCam03->addChild(ZBotS);
        ZBotS->release();
        ZBotS->setPosition({156, 65});
        ZBotS->setRotationX(18);
        ZBotS->setRotationY(-35);
        break;
    }
}

SpaceUK::SmallCams SpaceUK::RandomPosition(){
    int random = rand() % 3;

    switch (random)
    {
    case 0:
        return SmallCams::SmallCam1;
        break;

    case 1:
        return SmallCams::SmallCam2;
        break;

    case 2:
        return SmallCams::SmallCam3;
        break;
    }
    return SmallCams::SmallCam1;
}

void SpaceUK::CloseSmallDoor(blockPoses pos){
    currBlockPos = pos;
    switch (currBlockPos)
    {
    case blockPoses::blockCam1:
        CblockCam1->setVisible(true);
        OblockCam1->setVisible(false);

        CblockCam2->setVisible(false);
        OblockCam2->setVisible(true);

        CblockCam3->setVisible(false);
        OblockCam3->setVisible(true);
        break;

    case blockPoses::blockCam2:
        CblockCam1->setVisible(false);
        OblockCam1->setVisible(true);

        CblockCam2->setVisible(true);
        OblockCam2->setVisible(false);

        CblockCam3->setVisible(false);
        OblockCam3->setVisible(true);
        break;

    case blockPoses::blockCam3:
        CblockCam1->setVisible(false);
        OblockCam1->setVisible(true);

        CblockCam2->setVisible(false);
        OblockCam2->setVisible(true);

        CblockCam3->setVisible(true);
        OblockCam3->setVisible(false);
        break;
    }
}

void SpaceUK::kill(){
    MaskPCLayer->setVisible(false);
    spaceUKIcon->setVisible(false);
    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
        0.7f, 2, new std::string[]{
            "spaceUK.png"_spr,
            "spaceUK.png"_spr
        }
    ), "", false, false, false, 7);
}