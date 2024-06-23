
#include "customNightLayer.h"
#include "fireworkBlast.h"
#include "animatronicsInclude.h"
#include <CNGameLayer.h>

CNGameLayer* CNGameLayer::create(std::vector<animatronic*> animatronics, int office, bool frigidA, bool coinsA, bool batteryA, bool DDRepelA) {
    auto ret = new CNGameLayer();
    if (ret && ret->init(animatronics, office, frigidA, coinsA, batteryA, DDRepelA)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool CNGameLayer::init(std::vector<animatronic*> animatronics, int officeS, bool frigidA, bool coinsA, bool batteryA, bool DDRepelA) { 

    animatronicsSave = animatronics;

    //get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    //setup
    MainCont = CCNode::create();
    MainCont->setPosition(windowSize / 2);
    this->addChild(MainCont);

    World = CCNode::create();
    World->setPosition({0, (-windowSize.height / 2)});
    Canvas = CCNode::create();
    Canvas->setZOrder(50);
    MainCont->addChild(World);
    MainCont->addChild(Canvas);

    std::string debugString = std::to_string(0);
    debugText = CCTextFieldTTF::create(debugString.c_str(), "chatFont.fnt", 6);
    debugText->setVisible(false);

    Canvas->addChild(debugText);

    //start blackScreen (above all)
    BlackScreen = CCSprite::create("blackscreen.png"_spr);
    BlackScreen->setScale(5);
    BlackScreen->setZOrder(100);

    redScreen = CCSprite::create("redScreen.png"_spr);
    redScreen->setScale(5);
    redScreen->setZOrder(99);
    redScreen->setVisible(false);

    redVignette = CCSprite::create("redVignette.png"_spr);
    redVignette->setZOrder(101);
    redVignette->setVisible(false);
    redVignette->setScale(4.75f);

    gameOverText = CreateAnimatedSprite(0.05f, 10, new std::string[]{
        "gameOver3.png"_spr,
        "gameOver4.png"_spr,
        "gameOver5.png"_spr,
        "gameOver6.png"_spr,
        "gameOver7.png"_spr,
        "gameOver7.png"_spr,
        "gameOver6.png"_spr,
        "gameOver5.png"_spr,
        "gameOver4.png"_spr,
        "gameOver3.png"_spr
    });
    gameOverText->setZOrder(102);
    gameOverText->setOpacity(0);
    gameOverText->setVisible(false);

    gameOverTimeText = CCLabelBMFont::create("0:00:0", "clickteamMedium.fnt"_spr);
    gameOverTimeText->setOpacity(175);
    gameOverTimeText->setZOrder(102);
    gameOverTimeText->setOpacity(0);
    gameOverTimeText->setPosition({0, -22});
    gameOverTimeText->setScale(0.55f);
    gameOverTimeText->setVisible(false);

    //effect blackscreen (above cams and world)
    effectBlackscreen = CCSprite::create("blackscreen.png"_spr);
    effectBlackscreen->setScale(10);
    effectBlackscreen->setZOrder(25);
    effectBlackscreen->setOpacity(0);

    //o2 or power outage Blackscreen (on top of everything but the timer)
    SpacialBlackscreen = CCSprite::create("blackscreen.png"_spr);
    SpacialBlackscreen->setScale(10);
    SpacialBlackscreen->setZOrder(44);
    SpacialBlackscreen->setOpacity(0);

    //left door
    doorLeft = CCSprite::create("doorLeft1.png"_spr);
    doorLeft->setPosition({5, 132});
    doorLeft->setScale(1.2f);
    doorLeft->setZOrder(1);

    //up door
    doorUp = CCSprite::create("doorUp1.png"_spr);
    doorUp->setPosition({224, 255});
    doorUp->setScale(1.2f);
    doorUp->setZOrder(1);

    //right door
    doorRight = CCSprite::create("doorRight1.png"_spr);
    doorRight->setPosition({554, 132});
    doorRight->setScale(1.2f);
    doorRight->setZOrder(1);

    //bottom right door
    doorBottomRight = CCSprite::create("doorRight1.png"_spr);
    doorBottomRight->setPosition({627, -24});
    doorBottomRight->setScaleY(1.25f);
    doorBottomRight->setScaleX(1.3f);
    doorBottomRight->setZOrder(2);

    CCNode* bottomLeftCont = CCNode::create();

    //noise bar
    CCSprite* barOutlineNoise = CCSprite::create("barOutline.png"_spr);
    CCSprite* BarInsideNoise = CCSprite::create("BarInside.png"_spr);
    barOutlineNoise->addChild(BarInsideNoise);
    BarInsideNoise->setZOrder(1);
    BarInsideNoise->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->setPosition({-245, -146});
    barOutlineNoise->setScale(1.25f);

    noiseS1 = CCSprite::create("use1.png"_spr);
    noiseS1->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->addChild(noiseS1);
    noiseS1->setVisible(false);
    noiseS1->setZOrder(2);
    
    noiseS2 = CCSprite::create("use2.png"_spr);
    noiseS2->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->addChild(noiseS2);
    noiseS2->setVisible(false);
    noiseS2->setZOrder(2);
    
    noiseS3Red = CCSprite::create("use3Red.png"_spr);
    noiseS3Red->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->addChild(noiseS3Red);
    noiseS3Red->setVisible(false);
    noiseS3Red->setZOrder(2);
    
    noiseS4Red = CCSprite::create("use4Red.png"_spr);
    noiseS4Red->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->addChild(noiseS4Red);
    noiseS4Red->setVisible(false);
    noiseS4Red->setZOrder(2);
    
    noiseS5Red = CCSprite::create("use5Red.png"_spr);
    noiseS5Red->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->addChild(noiseS5Red);
    noiseS5Red->setVisible(false);
    noiseS5Red->setZOrder(2);
    
    noiseS6Red = CCSprite::create("use6Red.png"_spr);
    noiseS6Red->setPosition(barOutlineNoise->getContentSize() / 2);
    barOutlineNoise->addChild(noiseS6Red);
    noiseS6Red->setVisible(false);
    noiseS6Red->setZOrder(2);

    CCSprite* noiseText = CCSprite::create("noiseText.png"_spr);
    noiseText->setPosition({7,-2.5f});
    noiseText->setScale(1.05f);
    barOutlineNoise->addChild(noiseText);
    bottomLeftCont->addChild(barOutlineNoise);

    //usage bar
    CCSprite* barOutlineUsage = CCSprite::create("barOutline.png"_spr);
    CCSprite* BarInsideUsage = CCSprite::create("BarInside.png"_spr);
    barOutlineUsage->addChild(BarInsideUsage);
    BarInsideUsage->setZOrder(1);
    BarInsideUsage->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->setPosition({-245, -130});
    barOutlineUsage->setScale(1.25f);

    usageS1 = CCSprite::create("use1.png"_spr);
    usageS1->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->addChild(usageS1);
    usageS1->setVisible(false);
    usageS1->setZOrder(2);
    
    usageS2 = CCSprite::create("use2.png"_spr);
    usageS2->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->addChild(usageS2);
    usageS2->setVisible(false);
    usageS2->setZOrder(2);
    
    usageS3 = CCSprite::create("use3.png"_spr);
    usageS3->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->addChild(usageS3);
    usageS3->setVisible(false);
    usageS3->setZOrder(2);
    
    usageS4 = CCSprite::create("use4.png"_spr);
    usageS4->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->addChild(usageS4);
    usageS4->setVisible(false);
    usageS4->setZOrder(2);
    
    usageS5Red = CCSprite::create("use5Red.png"_spr);
    usageS5Red->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->addChild(usageS5Red);
    usageS5Red->setVisible(false);
    usageS5Red->setZOrder(2);

    usageS6Red = CCSprite::create("use6Red.png"_spr);
    usageS6Red->setPosition(barOutlineUsage->getContentSize() / 2);
    barOutlineUsage->addChild(usageS6Red);
    usageS6Red->setVisible(false);
    usageS6Red->setZOrder(2);

    CCSprite* usageText = CCSprite::create("UsageText.png"_spr);
    usageText->setPosition({8,-3});
    usageText->setScale(1.05f);
    barOutlineUsage->addChild(usageText);
    bottomLeftCont->addChild(barOutlineUsage);

    //dest & fan
    office = CCSprite::create("Main Office Light.png"_spr);
    officePowerDown = CCSprite::create("Main Office Down.png"_spr);
    desk = CreateAnimatedSprite(0.03f, 4, new std::string[]{
        "desk1.png"_spr,
        "desk2.png"_spr,
        "desk3.png"_spr,
        "desk4.png"_spr
    });
    desk->setScale(1.2f);
    desk->setZOrder(10);
    freedyNoseHitbox = CCNode::create();
    freedyNoseHitbox->setPosition({182, 75});
    freedyNoseHitbox->setContentSize({9, 7});
    desk->addChild(freedyNoseHitbox);
    CCSprite* starChain = CCSprite::create("starChain.png"_spr);
    starChain->setPosition({191, 256});
    starChain->setScale(1.2f);
    desk->addChild(starChain);

    noiseAmount++;
    usageAmount++;
    CoolMultiplier++;

    //mask
    MaskButton = CCSprite::create("maskButton.png"_spr);
    MaskButton->setPosition({-85.25f, -140});
    MaskButton->setScale(1.25f);
    MaskButton->setZOrder(35);
    Mask = CCSprite::create("mask1.png"_spr);
    Mask->setZOrder(1);
    Mask->setScale(4.75f);
    MaskButtonDetection = CCNode::create();
    MaskButtonDetection->setPosition({0, -12});
    MaskButtonDetection->setContentSize({120, 22});
    MaskButton->addChild(MaskButtonDetection);

    //cameras
    CamsButton = CCSprite::create("CamsButton.png"_spr);
    CamsButton->setPosition({85.25f, -140});
    CamsButton->setScale(1.25f);
    CamsButton->setZOrder(35);
    Cams = CCSprite::create("monitor1.png"_spr);
    Cams->setZOrder(15);
    Cams->setScale(4.75f);
    CamsButtonDetection = CCNode::create();
    CamsButtonDetection->setPosition({0, -12});
    CamsButtonDetection->setContentSize({120, 22});
    CamsButton->addChild(CamsButtonDetection);

    CamStatic = CreateAnimatedSprite(0.04f, 6, new std::string[]{
        "static1.png"_spr,
        "static2.png"_spr,
        "static3.png"_spr,
        "static4.png"_spr,
        "static5.png"_spr,
        "static6.png"_spr
    });
    CamStatic->setScale(4.75f);
    CamStatic->setVisible(false);
    CamStatic->setZOrder(16);

    cameraView = CCNode::create();
    cameraView->setZOrder(3);
    cameraView->setPosition({0, 999});

    cameraUI = CCNode::create();
    cameraUI->setZOrder(17);
    cameraUI->setPosition({0, 999});

    cameraOverallUI = CCNode::create();
    cameraOverallUI->setZOrder(17);
    cameraOverallUI->setPosition({0, 999});
    cameraOverallUI->setScale(1.2f);

    camSystem = CCSprite::create("camSystem.png"_spr);
    camSystem->setPosition({120, 92});
    cameraOverallUI->addChild(camSystem);

    ventSystem = CCSprite::create("ventSystem.png"_spr);
    ventSystem->setPosition({120, 67});
    cameraOverallUI->addChild(ventSystem);

    ductSystem = CCSprite::create("ductSystem.png"_spr);
    ductSystem->setPosition({120, 42});
    cameraOverallUI->addChild(ductSystem);

    systemButtonsBG = CCSprite::create("systemsBG.png"_spr);
    systemButtonsBG->setPosition({120, 92});
    systemButtonsBG->setZOrder(-1);
    cameraOverallUI->addChild(systemButtonsBG);

    powerGenButton = CCSprite::create("PowerGen.png"_spr);
    powerGenButton->setScale(1.1f);
    powerGenButton->setPosition({199, 98.5f});
    cameraOverallUI->addChild(powerGenButton);

    silVentButton = CCSprite::create("silentVent.png"_spr);
    silVentButton->setScale(1.1f);
    silVentButton->setPosition({199, 87});
    cameraOverallUI->addChild(silVentButton);

    heaterButton = CCSprite::create("Heater.png"_spr);
    heaterButton->setScale(1.1f);
    heaterButton->setPosition({199, 75.5f});
    cameraOverallUI->addChild(heaterButton);

    powerACButton = CCSprite::create("PowerAC.png"_spr);
    powerACButton->setScale(1.1f);
    powerACButton->setPosition({199, 64});
    cameraOverallUI->addChild(powerACButton);

    GMBButton = CCSprite::create("GMB.png"_spr);
    GMBButton->setScale(1.1f);
    GMBButton->setPosition({199, 52.5f});
    cameraOverallUI->addChild(GMBButton);

    spacialsOffButton = CCSprite::create("SpacialsOff.png"_spr);
    spacialsOffButton->setScale(1.1f);
    spacialsOffButton->setPosition({199, 41});
    cameraOverallUI->addChild(spacialsOffButton);

    musicBoxCont = CCNode::create();
    musicBoxCont->setVisible(false);

    windBoxOff = CCSprite::create("windBoxOff.png"_spr);
    windBoxOff->setPosition({197, 15});
    windBoxOff->setScale(1.1f);
    musicBoxCont->addChild(windBoxOff);

    windBoxOn = CCSprite::create("windBoxOn.png"_spr);
    windBoxOn->setPosition({197, 15});
    windBoxOn->setScale(1.1f);
    windBoxOn->setVisible(false);
    musicBoxCont->addChild(windBoxOn);

    ChangeMusicButton = CCSprite::create("ChangeMusic.png"_spr);
    ChangeMusicButton->setPosition({197, -3});
    ChangeMusicButton->setScale(1.1f);
    musicBoxCont->addChild(ChangeMusicButton);

    boxWindBar = CCSprite::create("musicProgress.png"_spr);
    boxWindBar->setPosition({172, 10});
    boxWindBar->setAnchorPoint({0, 0.5f});
    boxWindBar->setScaleY(0.75f);
    boxWindBar->setZOrder(1);
    musicBoxCont->addChild(boxWindBar);

    cameraOverallUI->addChild(musicBoxCont);

    closeCurtainsB = CCSprite::create("closeCurtains.png"_spr);
    closeCurtainsB->setVisible(false);
    closeCurtainsB->setScale(1.15f);
    closeCurtainsB->setPosition({196, 10});
    cameraOverallUI->addChild(closeCurtainsB);

    resetVentelation = CCSprite::create("resetVentOff.png"_spr);
    resetVentelation->setPosition({188, -92.5f});
    cameraOverallUI->addChild(resetVentelation);

    resetVentelationActive = CreateAnimatedSprite(0.25f,2,new std::string[]{
        "resetVentOff.png"_spr,
        "resetVentOn.png"_spr
    });
    resetVentelationActive->setPosition({188, -92.5f});
    resetVentelationActive->setVisible(false);
    cameraOverallUI->addChild(resetVentelationActive);

    venWarnMask = CreateAnimatedSprite(0.25f,2,new std::string[]{
        "bigwEmpty.png"_spr,
        "bigw.png"_spr
    });
    venWarnMask->setPosition({0, -140});
    venWarnMask->setVisible(false);
    venWarnMask->setZOrder(2);

    venWarnCams = CreateAnimatedSprite(0.25f,2,new std::string[]{
        "bigwEmpty.png"_spr,
        "bigw.png"_spr
    });
    venWarnCams->setPosition({170, -140});
    venWarnCams->setVisible(false);

    spacialUsed = CreateAnimatedSprite(0.5f, 2, new std::string[]{
        "spacialUsed1.png"_spr,
        "spacialUsed2.png"_spr
    });
    spacialUsed->setPosition({(spacialsOffButton->getPositionX() - 28), 41});
    cameraOverallUI->addChild(spacialUsed);

    AONLY = CreateAnimatedSprite(0.5f, 2, new std::string[]{
        "AONLY.png"_spr,
        "bigwEmpty.png"_spr
    });
    AONLY->setVisible(false);
    AONLY->setPosition({-190, 90});
    cameraOverallUI->addChild(AONLY);

    ventUI = CCNode::create();
    ventUI->setZOrder(2);
    ventUI->setPosition({0, 999});
    ventUI->setVisible(false);

    CCSprite* ventUIBG = CCSprite::create("blackscreen.png"_spr);
    ventUIBG->setScale(1.15f);
    ventUI->addChild(ventUIBG);

    CCSprite* ventMap = CCSprite::create("Ventmap.png"_spr);
    ventMap->setScale(1.2f);
    ventMap->setPosition({-80, 16});
    ventUI->addChild(ventMap);

    ventSnareEmptyRight = CCSprite::create("ventSnareEmpty.png"_spr);
    ventSnareEmptyRight->setPosition({-56, -38});
    ventSnareEmptyRight->setZOrder(5);
    ventSnareEmptyRight->setOpacity(200);

    ventSnareEmptyTop = CCSprite::create("ventSnareEmpty.png"_spr);
    ventSnareEmptyTop->setPosition({-79, -12});
    ventSnareEmptyTop->setZOrder(5);
    ventSnareEmptyTop->setOpacity(200);

    ventSnareEmptyLeft = CCSprite::create("ventSnareEmpty.png"_spr);
    ventSnareEmptyLeft->setPosition({-102, -38});
    ventSnareEmptyLeft->setZOrder(5);
    ventSnareEmptyLeft->setOpacity(200);

    ventSnareSelectedRight = CCSprite::create("ventSnareVer.png"_spr);
    ventSnareSelectedRight->setPosition({-56, -38});
    ventSnareSelectedRight->setZOrder(5);
    ventSnareSelectedRight->setVisible(false);

    ventSnareSelectedTop = CCSprite::create("ventSnareHor.png"_spr);
    ventSnareSelectedTop->setPosition({-79, -12});
    ventSnareSelectedTop->setZOrder(5);
    ventSnareSelectedTop->setVisible(false);

    ventSnareSelectedLeft = CCSprite::create("ventSnareVer.png"_spr);
    ventSnareSelectedLeft->setPosition({-102, -38});
    ventSnareSelectedLeft->setZOrder(5);
    ventSnareSelectedLeft->setVisible(false);

    ventUI->addChild(ventSnareEmptyRight);
    ventUI->addChild(ventSnareEmptyTop);
    ventUI->addChild(ventSnareEmptyLeft);
    ventUI->addChild(ventSnareSelectedRight);
    ventUI->addChild(ventSnareSelectedTop);
    ventUI->addChild(ventSnareSelectedLeft);

    CCSprite* ventHelp1 = CCSprite::create("ventHelp1.png"_spr);
    ventHelp1->setScale(1.1f);
    ventHelp1->setPosition({5, -67});
    ventUI->addChild(ventHelp1);
    CCSprite* ventHelp2 = CCSprite::create("ventHelp2.png"_spr);
    ventHelp2->setScale(1.2f);
    ventHelp2->setPosition({-17, -84});
    ventUI->addChild(ventHelp2);

    ductUI = CCNode::create();
    ductUI->setZOrder(2);
    ductUI->setPosition({0, 999});
    ductUI->setVisible(false);
    
    CCSprite* ductUIBG = CCSprite::create("blackscreen.png"_spr);
    ductUIBG->setScale(1.15f);
    ductUI->addChild(ductUIBG);

    CCSprite* ductMap = CCSprite::create("ductMap.png"_spr);
    ductMap->setScale(1.2f);
    ductMap->setPosition({-80, 16});
    ductUI->addChild(ductMap);

    openDuctArrow = CreateAnimatedSprite(0.15f, 6, new std::string[]{
        "ODuct1.png"_spr,
        "ODuct2.png"_spr,
        "ODuct3.png"_spr,
        "ODuct4.png"_spr,
        "ODuct5.png"_spr,
        "ODuct6.png"_spr
    });
    openDuctArrow->setPosition({-118, -76});
    openDuctArrow->setZOrder(5);
    ductUI->addChild(openDuctArrow);

    ClosedDuctX = CCSprite::create("CDuct1.png"_spr);
    ClosedDuctX->setPosition({-43, -76});
    ClosedDuctX->setZOrder(5);
    ductUI->addChild(ClosedDuctX);

    audioLore = CCSprite::create("audioLore.png"_spr);
    audioLore->setPosition({999, 999});
    audioLore->setOpacity(110);
    audioLore->setZOrder(5);
    ductUI->addChild(audioLore);

    OpenDuctLeftB = CCSprite::create("openDuctOff.png"_spr);
    OpenDuctLeftB->setPosition({-182, -88});
    OpenDuctLeftB->setScale(1.1f);
    OpenDuctLeftB->setZOrder(5);
    OpenDuctLeftB->setOpacity(150);
    ductUI->addChild(OpenDuctLeftB);

    OpenDuctRightB = CCSprite::create("openDuctOff.png"_spr);
    OpenDuctRightB->setPosition({26, -88});
    OpenDuctRightB->setScale(1.1f);
    ductUI->addChild(OpenDuctRightB);

    //contact Points for duct map
    topleftContactPoint1 = CCNode::create();
    topleftContactPoint1->setPosition({-119, 126});
    topleftContactPoint1->setAnchorPoint({0.5f,0.5f});
    topleftContactPoint1->setContentSize({25, 25});
    ductUI->addChild(topleftContactPoint1);

    topleftContactPoint2 = CCNode::create();
    topleftContactPoint2->setPosition({-119, 100});
    topleftContactPoint2->setAnchorPoint({0.5f,0.5f});
    topleftContactPoint2->setContentSize({25, 25});
    ductUI->addChild(topleftContactPoint2);

    toprightContactPoint1 = CCNode::create();
    toprightContactPoint1->setPosition({-41, 126});
    toprightContactPoint1->setAnchorPoint({0.5f,0.5f});
    toprightContactPoint1->setContentSize({25, 25});
    ductUI->addChild(toprightContactPoint1);

    toprightContactPoint2 = CCNode::create();
    toprightContactPoint2->setPosition({-41, 100});
    toprightContactPoint2->setAnchorPoint({0.5f,0.5f});
    toprightContactPoint2->setContentSize({25, 25});
    ductUI->addChild(toprightContactPoint2);

    toplineContactPoint1 = CCNode::create();
    toplineContactPoint1->setPosition({-41, 80});
    toplineContactPoint1->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint1->setContentSize({25, 16});
    ductUI->addChild(toplineContactPoint1);

    toplineContactPoint2 = CCNode::create();
    toplineContactPoint2->setPosition({-119, 80});
    toplineContactPoint2->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint2->setContentSize({25, 16});
    ductUI->addChild(toplineContactPoint2);

    toplineContactPoint3 = CCNode::create();
    toplineContactPoint3->setPosition({-97, 80});
    toplineContactPoint3->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint3->setContentSize({20, 16});
    ductUI->addChild(toplineContactPoint3);

    toplineContactPoint4 = CCNode::create();
    toplineContactPoint4->setPosition({-80, 80});
    toplineContactPoint4->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint4->setContentSize({16, 16});
    ductUI->addChild(toplineContactPoint4);

    toplineContactPoint5 = CCNode::create();
    toplineContactPoint5->setPosition({-62, 80});
    toplineContactPoint5->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint5->setContentSize({20, 16});
    ductUI->addChild(toplineContactPoint5);

    toplineContactPoint6 = CCNode::create();
    toplineContactPoint6->setPosition({-142, 80});
    toplineContactPoint6->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint6->setContentSize({20, 16});
    ductUI->addChild(toplineContactPoint6);

    toplineContactPoint7 = CCNode::create();
    toplineContactPoint7->setPosition({-18, 80});
    toplineContactPoint7->setAnchorPoint({0.5f,0.5f});
    toplineContactPoint7->setContentSize({20, 16});
    ductUI->addChild(toplineContactPoint7);

    topRightTurn = CCNode::create();
    topRightTurn->setPosition({-2, 80});
    topRightTurn->setAnchorPoint({0.5f,0.5f});
    topRightTurn->setContentSize({12, 16});
    ductUI->addChild(topRightTurn);

    topLeftTurn = CCNode::create();
    topLeftTurn->setPosition({-158, 80});
    topLeftTurn->setAnchorPoint({0.5f,0.5f});
    topLeftTurn->setContentSize({12, 16});
    ductUI->addChild(topLeftTurn);

    rightLineContactPoint1 = CCNode::create();
    rightLineContactPoint1->setPosition({-2, 59});
    rightLineContactPoint1->setAnchorPoint({0.5f,0.5f});
    rightLineContactPoint1->setContentSize({20, 25});
    ductUI->addChild(rightLineContactPoint1);

    rightLineContactPoint2 = CCNode::create();
    rightLineContactPoint2->setPosition({-2, 35});
    rightLineContactPoint2->setAnchorPoint({0.5f,0.5f});
    rightLineContactPoint2->setContentSize({20, 22});
    ductUI->addChild(rightLineContactPoint2);

    rightMiddleTurn = CCNode::create();
    rightMiddleTurn->setPosition({-2, 15});
    rightMiddleTurn->setAnchorPoint({0.5f,0.5f});
    rightMiddleTurn->setContentSize({20, 16});
    ductUI->addChild(rightMiddleTurn);

    rightLineContactPoint3 = CCNode::create();
    rightLineContactPoint3->setPosition({-2, -5});
    rightLineContactPoint3->setAnchorPoint({0.5f,0.5f});
    rightLineContactPoint3->setContentSize({20, 22});
    ductUI->addChild(rightLineContactPoint3);

    rightLineContactPoint4 = CCNode::create();
    rightLineContactPoint4->setPosition({-2, -29});
    rightLineContactPoint4->setAnchorPoint({0.5f,0.5f});
    rightLineContactPoint4->setContentSize({20, 25});
    ductUI->addChild(rightLineContactPoint4);

    bottomRightTurn = CCNode::create();
    bottomRightTurn->setPosition({-2, -45});
    bottomRightTurn->setAnchorPoint({0.5f,0.5f});
    bottomRightTurn->setContentSize({20, 7});
    ductUI->addChild(bottomRightTurn);

    bottomRightLineContactPoint1 = CCNode::create();
    bottomRightLineContactPoint1->setPosition({-22, -45});
    bottomRightLineContactPoint1->setAnchorPoint({0.5f,0.5f});
    bottomRightLineContactPoint1->setContentSize({20, 12});
    ductUI->addChild(bottomRightLineContactPoint1);

    bottomRightToEndTurn = CCNode::create();
    bottomRightToEndTurn->setPosition({-43, -45});
    bottomRightToEndTurn->setAnchorPoint({0.5f,0.5f});
    bottomRightToEndTurn->setContentSize({22, 12});
    ductUI->addChild(bottomRightToEndTurn);

    RightEndContactPoint = CCNode::create();
    RightEndContactPoint->setPosition({-43, -65});
    RightEndContactPoint->setAnchorPoint({0.5f,0.5f});
    RightEndContactPoint->setContentSize({22, 26});
    ductUI->addChild(RightEndContactPoint);
    
    leftLineContactPoint1 = CCNode::create();
    leftLineContactPoint1->setPosition({-157, 59});
    leftLineContactPoint1->setAnchorPoint({0.5f,0.5f});
    leftLineContactPoint1->setContentSize({20, 25});
    ductUI->addChild(leftLineContactPoint1);

    leftLineContactPoint2 = CCNode::create();
    leftLineContactPoint2->setPosition({-157, 35});
    leftLineContactPoint2->setAnchorPoint({0.5f,0.5f});
    leftLineContactPoint2->setContentSize({20, 22});
    ductUI->addChild(leftLineContactPoint2);

    leftMiddleTurn = CCNode::create();
    leftMiddleTurn->setPosition({-157, 15});
    leftMiddleTurn->setAnchorPoint({0.5f,0.5f});
    leftMiddleTurn->setContentSize({20, 16});
    ductUI->addChild(leftMiddleTurn);

    leftLineContactPoint3 = CCNode::create();
    leftLineContactPoint3->setPosition({-157, -5});
    leftLineContactPoint3->setAnchorPoint({0.5f,0.5f});
    leftLineContactPoint3->setContentSize({20, 22});
    ductUI->addChild(leftLineContactPoint3);

    leftLineContactPoint4 = CCNode::create();
    leftLineContactPoint4->setPosition({-157, -29});
    leftLineContactPoint4->setAnchorPoint({0.5f,0.5f});
    leftLineContactPoint4->setContentSize({20, 25});
    ductUI->addChild(leftLineContactPoint4);

    bottomLeftTurn = CCNode::create();
    bottomLeftTurn->setPosition({-157, -45});
    bottomLeftTurn->setAnchorPoint({0.5f,0.5f});
    bottomLeftTurn->setContentSize({20, 7});
    ductUI->addChild(bottomLeftTurn);

    bottomLeftLineContactPoint1 = CCNode::create();
    bottomLeftLineContactPoint1->setPosition({-133, -45});
    bottomLeftLineContactPoint1->setAnchorPoint({0.5f,0.5f});
    bottomLeftLineContactPoint1->setContentSize({20, 12});
    ductUI->addChild(bottomLeftLineContactPoint1);

    bottomLeftToEndTurn = CCNode::create();
    bottomLeftToEndTurn->setPosition({-118, -45});
    bottomLeftToEndTurn->setAnchorPoint({0.5f,0.5f});
    bottomLeftToEndTurn->setContentSize({22, 12});
    ductUI->addChild(bottomLeftToEndTurn);

    LeftEndContactPoint = CCNode::create();
    LeftEndContactPoint->setPosition({-118, -65});
    LeftEndContactPoint->setAnchorPoint({0.5f,0.5f});
    LeftEndContactPoint->setContentSize({22, 26});
    ductUI->addChild(LeftEndContactPoint);

    middleLineContactPoint1 = CCNode::create();
    middleLineContactPoint1->setPosition({-135, 15});
    middleLineContactPoint1->setAnchorPoint({0.5f,0.5f});
    middleLineContactPoint1->setContentSize({22, 20});
    ductUI->addChild(middleLineContactPoint1);

    middleLineContactPoint2 = CCNode::create();
    middleLineContactPoint2->setPosition({-115, 15});
    middleLineContactPoint2->setAnchorPoint({0.5f,0.5f});
    middleLineContactPoint2->setContentSize({18, 20});
    ductUI->addChild(middleLineContactPoint2);

    middleLineContactPoint3 = CCNode::create();
    middleLineContactPoint3->setPosition({-95, 15});
    middleLineContactPoint3->setAnchorPoint({0.5f,0.5f});
    middleLineContactPoint3->setContentSize({18, 20});
    ductUI->addChild(middleLineContactPoint3);

    middleLineContactPoint4 = CCNode::create();
    middleLineContactPoint4->setPosition({-63, 15});
    middleLineContactPoint4->setAnchorPoint({0.5f,0.5f});
    middleLineContactPoint4->setContentSize({22, 22});
    ductUI->addChild(middleLineContactPoint4);

    middleLineContactPoint5 = CCNode::create();
    middleLineContactPoint5->setPosition({-41, 15});
    middleLineContactPoint5->setAnchorPoint({0.5f,0.5f});
    middleLineContactPoint5->setContentSize({22, 22});
    ductUI->addChild(middleLineContactPoint5);

    middleLineContactPoint6 = CCNode::create();
    middleLineContactPoint6->setPosition({-21, 15});
    middleLineContactPoint6->setAnchorPoint({0.5f,0.5f});
    middleLineContactPoint6->setContentSize({20, 22});
    ductUI->addChild(middleLineContactPoint6);

    middleLineTurn = CCNode::create();
    middleLineTurn->setPosition({-79, 15});
    middleLineTurn->setAnchorPoint({0.5f,0.5f});
    middleLineTurn->setContentSize({10, 22});
    ductUI->addChild(middleLineTurn);

    middleLineUpContactPoint1 = CCNode::create();
    middleLineUpContactPoint1->setPosition({-79, 37});
    middleLineUpContactPoint1->setAnchorPoint({0.5f,0.5f});
    middleLineUpContactPoint1->setContentSize({18, 22});
    ductUI->addChild(middleLineUpContactPoint1);

    middleLineUpContactPoint2 = CCNode::create();
    middleLineUpContactPoint2->setPosition({-79, 60});
    middleLineUpContactPoint2->setAnchorPoint({0.5f,0.5f});
    middleLineUpContactPoint2->setContentSize({18, 22});
    ductUI->addChild(middleLineUpContactPoint2);

    CamViewStatic = CCNode::create();
    CamViewStatic->setZOrder(10);
    cameraView->addChild(CamViewStatic);

    //camera images
    Cam01 = CCNode::create();
    cameraView->addChild(Cam01);
    CCSprite* Cam01S = CCSprite::create("Cam01.png"_spr);
    Cam01S->setScale(2.275f);
    Cam01->addChild(Cam01S);

    Cam02 = CCNode::create();
    cameraView->addChild(Cam02);
    CCSprite* Cam02S = CCSprite::create("Cam02.png"_spr);
    Cam02S->setScale(2.275f);
    Cam02->addChild(Cam02S);

    Cam03 = CCNode::create();
    cameraView->addChild(Cam03);
    CCSprite* Cam03S = CCSprite::create("Cam03.png"_spr);
    Cam03S->setScale(2.275f);
    Cam03->addChild(Cam03S);

    Cam04 = CCNode::create();
    cameraView->addChild(Cam04);
    CCSprite* Cam04S = CCSprite::create("Cam04.png"_spr);
    Cam04S->setScale(2.275f);
    Cam04->addChild(Cam04S);

    Cam05 = CCNode::create();
    cameraView->addChild(Cam05);
    Cam05S = CCSprite::create("Cam05.png"_spr);
    Cam05S->setScale(2.275f);
    Cam05->addChild(Cam05S);

    Cam06 = CCNode::create();
    cameraView->addChild(Cam06);
    CCSprite* Cam06S = CCSprite::create("Cam06.png"_spr);
    Cam06S->setScale(2.275f);
    Cam06->addChild(Cam06S);

    Cam07 = CCNode::create();
    cameraView->addChild(Cam07);
    CCSprite* Cam07S = CCSprite::create("Cam07.png"_spr);
    Cam07S->setScale(2.275f);
    Cam07->addChild(Cam07S);

    CCLabelBMFont* DeathCoinCostText = CCLabelBMFont::create("10", "clickteamMedium.fnt"_spr);
    DeathCoinCostText->setPosition({-14, -41});
    DeathCoinCostText->setColor({ 35, 35, 35 });
    Cam07->addChild(DeathCoinCostText);

    deathCoinBuyButtton = CCSprite::create("buyButton.png"_spr);
    deathCoinBuyButtton->setPosition({-14, -59});
    Cam07->addChild(deathCoinBuyButtton);

    Cam08 = CCNode::create();
    cameraView->addChild(Cam08);
    Cam08S = CCSprite::create("Cam08.png"_spr);
    Cam08S->setScale(2.275f);
    Cam08->addChild(Cam08S);

    CCSprite* mapS = CCSprite::create("map.png"_spr);
    mapS->setPosition({87, -40});
    mapS->setScale(1.2f);
    cameraUI->addChild(mapS);

    Cam01ButtonCont = CCNode::create();
    Cam01ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam01ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam01ButtonText = CCSprite::create("Cam01Text.png"_spr);
    mapS->addChild(Cam01ButtonCont);
    Cam01ButtonText->setPosition({-6, 2});
    Cam01ButtonCont->addChild(Cam01ButtonOff);
    Cam01ButtonCont->addChild(Cam01ButtonOn);
    Cam01ButtonCont->addChild(Cam01ButtonText);
    Cam01ButtonText->setZOrder(1);
    Cam01ButtonCont->setPosition({37, 4});

    Cam02ButtonCont = CCNode::create();
    Cam02ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam02ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam02ButtonText = CCSprite::create("Cam02Text.png"_spr);
    mapS->addChild(Cam02ButtonCont);
    Cam02ButtonText->setPosition({-6, 2});
    Cam02ButtonCont->addChild(Cam02ButtonOff);
    Cam02ButtonCont->addChild(Cam02ButtonOn);
    Cam02ButtonCont->addChild(Cam02ButtonText);
    Cam02ButtonText->setZOrder(1);
    Cam02ButtonCont->setPosition({97, 4});

    Cam03ButtonCont = CCNode::create();
    Cam03ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam03ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam03ButtonText = CCSprite::create("Cam03Text.png"_spr);
    mapS->addChild(Cam03ButtonCont);
    Cam03ButtonText->setPosition({-6, 2});
    Cam03ButtonCont->addChild(Cam03ButtonOff);
    Cam03ButtonCont->addChild(Cam03ButtonOn);
    Cam03ButtonCont->addChild(Cam03ButtonText);
    Cam03ButtonText->setZOrder(1);
    Cam03ButtonCont->setPosition({22, 24});

    Cam04ButtonCont = CCNode::create();
    Cam04ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam04ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam04ButtonText = CCSprite::create("Cam04Text.png"_spr);
    mapS->addChild(Cam04ButtonCont);
    Cam04ButtonText->setPosition({-6, 2});
    Cam04ButtonCont->addChild(Cam04ButtonOff);
    Cam04ButtonCont->addChild(Cam04ButtonOn);
    Cam04ButtonCont->addChild(Cam04ButtonText);
    Cam04ButtonText->setZOrder(1);
    Cam04ButtonCont->setPosition({126, 37});

    Cam05ButtonCont = CCNode::create();
    Cam05ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam05ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam05ButtonText = CCSprite::create("Cam05Text.png"_spr);
    mapS->addChild(Cam05ButtonCont);
    Cam05ButtonText->setPosition({-6, 2});
    Cam05ButtonCont->addChild(Cam05ButtonOff);
    Cam05ButtonCont->addChild(Cam05ButtonOn);
    Cam05ButtonCont->addChild(Cam05ButtonText);
    Cam05ButtonText->setZOrder(1);
    Cam05ButtonCont->setPosition({35, 62});

    Cam06ButtonCont = CCNode::create();
    Cam06ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam06ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam06ButtonText = CCSprite::create("Cam06Text.png"_spr);
    mapS->addChild(Cam06ButtonCont);
    Cam06ButtonText->setPosition({-6, 2});
    Cam06ButtonCont->addChild(Cam06ButtonOff);
    Cam06ButtonCont->addChild(Cam06ButtonOn);
    Cam06ButtonCont->addChild(Cam06ButtonText);
    Cam06ButtonText->setZOrder(1);
    Cam06ButtonCont->setPosition({109, 80});

    Cam07ButtonCont = CCNode::create();
    Cam07ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam07ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam07ButtonText = CCSprite::create("Cam07Text.png"_spr);
    mapS->addChild(Cam07ButtonCont);
    Cam07ButtonText->setPosition({-6, 2});
    Cam07ButtonCont->addChild(Cam07ButtonOff);
    Cam07ButtonCont->addChild(Cam07ButtonOn);
    Cam07ButtonCont->addChild(Cam07ButtonText);
    Cam07ButtonText->setZOrder(1);
    Cam07ButtonCont->setPosition({74, 102});

    Cam08ButtonCont = CCNode::create();
    Cam08ButtonOn = CCSprite::create("cameraButtonOn.png"_spr);
    Cam08ButtonOff = CCSprite::create("cameraButtonOff.png"_spr);
    Cam08ButtonText = CCSprite::create("Cam08Text.png"_spr);
    mapS->addChild(Cam08ButtonCont);
    Cam08ButtonText->setPosition({-6, 2});
    Cam08ButtonCont->addChild(Cam08ButtonOff);
    Cam08ButtonCont->addChild(Cam08ButtonOn);
    Cam08ButtonCont->addChild(Cam08ButtonText);
    Cam08ButtonText->setZOrder(1);
    Cam08ButtonCont->setPosition({2, 106});

    switch (currentCamSelected){
    case Cameras::Camera01:
        Cam01->setPosition({0, 0});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(true);
        Cam01ButtonOff->setVisible(false);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;
    
    case Cameras::Camera02:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 0});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(true);
        Cam02ButtonOff->setVisible(false);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;

    case Cameras::Camera03:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 0});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(true);
        Cam03ButtonOff->setVisible(false);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;

    case Cameras::Camera04:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 0});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(true);
        Cam04ButtonOff->setVisible(false);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;

    case Cameras::Camera05:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 0});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(true);
        Cam05ButtonOff->setVisible(false);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;

    case Cameras::Camera06:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 0});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(true);
        Cam06ButtonOff->setVisible(false);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;

    case Cameras::Camera07:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 0});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(true);
        Cam07ButtonOff->setVisible(false);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        break;

    case Cameras::Camera08:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 0});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(true);
        Cam08ButtonOff->setVisible(false);
        break;
    
    default:
        break;
    }

    //flashlight
    Flashlight = CCSprite::create("FlashLight.png"_spr);
    Flashlight->setVisible(false);
    Flashlight->setScale(4.75f);
    Flashlight->setOpacity(60);
    Canvas->addChild(Flashlight);

    //candy codet
    CandyCoddet = CCSprite::create("candyCoddet11.png"_spr);
    CandyCoddet->setZOrder(1);
    candyCoddetPulseTimer = 5 + (rand() % 30);
    CandyCoddet->setPosition({142, 119});
    CandyCoddet->setScale(1.15f);

    //movement detection
    MoveDetecSlowRight = CCNode::create();
    MoveDetecFastRight = CCNode::create();

    MoveDetecSlowRight->setContentSize({95,320});
    MoveDetecSlowRight->setPosition({65,-160});
    MoveDetecFastRight->setContentSize({140,320});
    MoveDetecFastRight->setPosition({160,-160});

    MoveDetecSlowLeft = CCNode::create();
    MoveDetecFastLeft = CCNode::create();

    MoveDetecSlowLeft->setContentSize({95,320});
    MoveDetecSlowLeft->setPosition({-165,-160});
    MoveDetecFastLeft->setContentSize({140,320});
    MoveDetecFastLeft->setPosition({-290,-160});

    //timer
    nightTimer = CCLabelBMFont::create("0:00.0", "clickteamMedium.fnt"_spr);
    nightTimer->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    nightTimer->setPosition({270, 128});
    nightTimer->setScale(0.45f);
    nightTimer->setOpacity(175);
    nightTimer->setZOrder(45);

    //am texts
    amTextDy = CCTextFieldTTF::create("12", "chatFont.fnt", 14, {300, 300}, CCTextAlignment::kCCTextAlignmentRight);
    CCSprite* amText = CCSprite::create("amText.png"_spr);
    amText->addChild(amTextDy);
    amTextDy->setOpacity(175);
    amText->setOpacity(175);
    amText->setPosition({263, 136});
    amText->setScale(1.375f);
    amTextDy->setPosition({-151, -137});
    amTextDy->setScale(1);
    amText->setZOrder(45);

    //precent texts
    precentTextDy = CCLabelBMFont::create("100", "abb2k.UltimateCustomDash/clickteamMedium.fnt", 300, CCTextAlignment::kCCTextAlignmentRight);
    precentTextDy->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    precentTextDy->setPosition({-1, 1});
    precentTextDy->setScale(0.85f);
    CCSprite* precentText = CCSprite::create("%Text.png"_spr);
    precentText->setPosition({-233, -114});
    precentText->setScale(1.45f);
    precentText->addChild(precentTextDy);
    bottomLeftCont->addChild(precentText);
    bottomLeftCont->setZOrder(35);
    bottomLeftCont->setPosition({1, 8});

    //tempreture
    tempretureContainer = CCNode::create();
    tempretureContainer->setPosition({273, -142});
    tempretureText = CCLabelBMFont::create("60", "abb2k.UltimateCustomDash/clickteamMedium.fnt", 300, CCTextAlignment::kCCTextAlignmentRight);
    tempretureText->setAnchorPoint(ccp(1.0f,0.5f)); // right align
    littlDotThing = CCTextFieldTTF::create("0", "chatFont.fnt", 7);
    littlDotThing->setPosition({2, 5});
    littlDotThing->setScale(0.95f);
    tempretureContainer->addChild(tempretureText);
    tempretureContainer->addChild(littlDotThing);
    tempretureContainer->setZOrder(35);

    //fazCoinCounter
    CCNode* fazcoinCont = CCNode::create();
    fazcoinCont->setPosition({-262, 137});
    fazcoinCont->setScale(1.35f);
    CCSprite* fazcoin = CCSprite::create("fazCoin.png"_spr);
    fazcoin->setScale(0.825f);
    fazcoin->setPosition({0, -1});
    fazcoin->setOpacity(150);

    fazCoinsText = CCLabelBMFont::create("0", "abb2k.UltimateCustomDash/clickteamBig.fnt", 300, CCTextAlignment::kCCTextAlignmentRight);
    fazCoinsText->setAnchorPoint(ccp(0.0f,0.5f)); // left align
    fazCoinsText->setPosition({13, -8});
    fazCoinsText->setScale(0.375f);
    fazCoinsText->setOpacity(180);

    fazcoinCont->addChild(fazcoin);
    fazcoinCont->addChild(fazCoinsText);
    fazcoinCont->setZOrder(35);

    //floorSignenter
    floorSignLeft = CCSprite::create("floorSignLeft.png"_spr);
    floorSignRight = CCSprite::create("floorSignRight.png"_spr);
    floorSignRight->setVisible(false);

    floorSignLeft->setPosition({83, 52});
    floorSignLeft->setScale(1.2f);
    floorSignLeft->setZOrder(2);

    floorSignRight->setPosition({474, 52});
    floorSignRight->setScale(1.2f);
    floorSignRight->setZOrder(2);

    //deathcoin
    deathcoinSoff = CCSprite::create("DeathCoin.png"_spr);
    deathcoinSoff->setZOrder(35);
    deathcoinSoff->setPosition({-263, 104});
    deathcoinSoff->setScale(1.125f);
    deathcoinSoff->setVisible(false);
    deathcoinSon = CCSprite::create("DeathClick.png"_spr);
    deathcoinSon->setZOrder(35);
    deathcoinSon->setPosition({-263, 104});
    deathcoinSon->setScale(1.125f);
    deathcoinSon->setVisible(false);

    //endscreen
    udidit = CCSprite::create("udidit.png"_spr);
    udidit->setZOrder(106);
    udidit->setOpacity(0);

    highScoreText = CCSprite::create("newHScore.png"_spr);
    highScoreText->setZOrder(106);
    highScoreText->setOpacity(0);
    highScoreText->setPosition({0, -10});

    highScoreTextDy = CCLabelBMFont::create("0", "abb2k.UltimateCustomDash/clickteamBig.fnt", 300);
    highScoreTextDy->setOpacity(0);
    highScoreTextDy->setZOrder(106);
    highScoreTextDy->setPosition({0, 14});

    greatJob = CreateAnimatedSprite(0.05f, 21, new std::string[]{
        "greatJob1.png"_spr,
        "greatJob2.png"_spr,
        "greatJob3.png"_spr,
        "greatJob4.png"_spr,
        "greatJob5.png"_spr,
        "greatJob6.png"_spr,
        "greatJob7.png"_spr,
        "greatJob8.png"_spr,
        "greatJob9.png"_spr,
        "greatJob10.png"_spr,
        "greatJob11.png"_spr,
        "greatJob12.png"_spr,
        "greatJob13.png"_spr,
        "greatJob14.png"_spr,
        "greatJob15.png"_spr,
        "greatJob16.png"_spr,
        "greatJob17.png"_spr,
        "greatJob18.png"_spr,
        "greatJob19.png"_spr,
        "greatJob20.png"_spr,
        "greatJob21.png"_spr
    });
    greatJob->setOpacity(0);
    greatJob->setZOrder(106);
    greatJob->setPosition({0, 40});

    fantastic = CreateAnimatedSprite(0.05f, 21, new std::string[]{
        "fantastic1.png"_spr,
        "fantastic2.png"_spr,
        "fantastic3.png"_spr,
        "fantastic4.png"_spr,
        "fantastic5.png"_spr,
        "fantastic6.png"_spr,
        "fantastic7.png"_spr,
        "fantastic8.png"_spr,
        "fantastic9.png"_spr,
        "fantastic10.png"_spr,
        "fantastic11.png"_spr,
        "fantastic12.png"_spr,
        "fantastic13.png"_spr,
        "fantastic14.png"_spr,
        "fantastic15.png"_spr,
        "fantastic16.png"_spr,
        "fantastic17.png"_spr,
        "fantastic18.png"_spr,
        "fantastic19.png"_spr,
        "fantastic20.png"_spr,
        "fantastic21.png"_spr
    });
    fantastic->setOpacity(0);
    fantastic->setZOrder(106);
    fantastic->setPosition({0, 40});

    amazing = CreateAnimatedSprite(0.05f, 21, new std::string[]{
        "amazing1.png"_spr,
        "amazing2.png"_spr,
        "amazing3.png"_spr,
        "amazing4.png"_spr,
        "amazing5.png"_spr,
        "amazing6.png"_spr,
        "amazing7.png"_spr,
        "amazing8.png"_spr,
        "amazing9.png"_spr,
        "amazing10.png"_spr,
        "amazing11.png"_spr,
        "amazing12.png"_spr,
        "amazing13.png"_spr,
        "amazing14.png"_spr,
        "amazing15.png"_spr,
        "amazing16.png"_spr,
        "amazing17.png"_spr,
        "amazing18.png"_spr,
        "amazing19.png"_spr,
        "amazing20.png"_spr,
        "amazing21.png"_spr
    });
    amazing->setOpacity(0);
    amazing->setZOrder(106);
    amazing->setPosition({0, 42});

    stupendous = CreateAnimatedSprite(0.05f, 21, new std::string[]{
        "stupendous1.png"_spr,
        "stupendous2.png"_spr,
        "stupendous3.png"_spr,
        "stupendous4.png"_spr,
        "stupendous5.png"_spr,
        "stupendous6.png"_spr,
        "stupendous7.png"_spr,
        "stupendous8.png"_spr,
        "stupendous9.png"_spr,
        "stupendous10.png"_spr,
        "stupendous11.png"_spr,
        "stupendous12.png"_spr,
        "stupendous13.png"_spr,
        "stupendous14.png"_spr,
        "stupendous15.png"_spr,
        "stupendous16.png"_spr,
        "stupendous17.png"_spr,
        "stupendous18.png"_spr,
        "stupendous19.png"_spr,
        "stupendous20.png"_spr,
        "stupendous21.png"_spr
    });
    stupendous->setOpacity(0);
    stupendous->setZOrder(106);
    stupendous->setPosition({0, 47});

    perfect = CreateAnimatedSprite(0.05f, 21, new std::string[]{
        "perfect1.png"_spr,
        "perfect2.png"_spr,
        "perfect3.png"_spr,
        "perfect4.png"_spr,
        "perfect5.png"_spr,
        "perfect6.png"_spr,
        "perfect7.png"_spr,
        "perfect8.png"_spr,
        "perfect9.png"_spr,
        "perfect10.png"_spr,
        "perfect11.png"_spr,
        "perfect12.png"_spr,
        "perfect13.png"_spr,
        "perfect14.png"_spr,
        "perfect15.png"_spr,
        "perfect16.png"_spr,
        "perfect17.png"_spr,
        "perfect18.png"_spr,
        "perfect19.png"_spr,
        "perfect20.png"_spr,
        "perfect21.png"_spr
    });
    perfect->setOpacity(0);
    perfect->setZOrder(106);
    perfect->setPosition({0, 52});

    unbeatable = CreateAnimatedSprite(0.05f, 21, new std::string[]{
        "unbeatable1.png"_spr,
        "unbeatable2.png"_spr,
        "unbeatable3.png"_spr,
        "unbeatable4.png"_spr,
        "unbeatable5.png"_spr,
        "unbeatable6.png"_spr,
        "unbeatable7.png"_spr,
        "unbeatable8.png"_spr,
        "unbeatable9.png"_spr,
        "unbeatable10.png"_spr,
        "unbeatable11.png"_spr,
        "unbeatable12.png"_spr,
        "unbeatable13.png"_spr,
        "unbeatable14.png"_spr,
        "unbeatable15.png"_spr,
        "unbeatable16.png"_spr,
        "unbeatable17.png"_spr,
        "unbeatable18.png"_spr,
        "unbeatable19.png"_spr,
        "unbeatable20.png"_spr,
        "unbeatable21.png"_spr
    });
    unbeatable->setOpacity(0);
    unbeatable->setZOrder(106);
    unbeatable->setPosition({0, 51});

    //setup
    officeFlickerTimer = randomFloat(0.2f, 3);
    office->setPosition(windowSize / 2);

    office->setScale(1.2f);

    officePowerDown->setPosition(windowSize / 2);

    officePowerDown->setScale(1.2f);
    officePowerDown->setVisible(false);

    World->addChild(floorSignLeft);
    World->addChild(floorSignRight);
    World->addChild(doorBottomRight);
    World->addChild(doorRight);
    World->addChild(doorUp);
    World->addChild(doorLeft);
    World->addChild(CandyCoddet);
    World->addChild(desk);
    World->addChild(office);
    World->addChild(officePowerDown);

    Canvas->addChild(unbeatable);
    Canvas->addChild(perfect);
    Canvas->addChild(stupendous);
    Canvas->addChild(amazing);
    Canvas->addChild(fantastic);
    Canvas->addChild(greatJob);
    Canvas->addChild(highScoreTextDy);
    Canvas->addChild(highScoreText);
    Canvas->addChild(udidit);
    Canvas->addChild(gameOverTimeText);
    Canvas->addChild(gameOverText);
    Canvas->addChild(redVignette);
    Canvas->addChild(redScreen);
    Canvas->addChild(venWarnMask);
    Canvas->addChild(venWarnCams);
    Canvas->addChild(deathcoinSoff);
    Canvas->addChild(deathcoinSon);
    Canvas->addChild(cameraOverallUI);
    Canvas->addChild(ventUI);
    Canvas->addChild(ductUI);
    Canvas->addChild(cameraUI);
    Canvas->addChild(cameraView);
    Canvas->addChild(CamStatic);
    Canvas->addChild(CamsButton);
    Canvas->addChild(Cams);
    Canvas->addChild(MaskButton);
    Canvas->addChild(Mask);
    Canvas->addChild(SpacialBlackscreen);
    Canvas->addChild(effectBlackscreen);
    Canvas->addChild(fazcoinCont);
    Canvas->addChild(tempretureContainer);
    Canvas->addChild(bottomLeftCont);
    Canvas->addChild(amText);
    Canvas->addChild(MoveDetecSlowRight);
    Canvas->addChild(MoveDetecFastRight);
    Canvas->addChild(MoveDetecSlowLeft);
    Canvas->addChild(MoveDetecFastLeft);
    Canvas->addChild(nightTimer);
    Canvas->addChild(BlackScreen);

    int mechiDiff = -1;
    int cotDiff = -1;
    int midncapDiff = -1;
    bool spawnedPlushes = false;

    for (size_t i = 0; i < animatronicsSave.size(); i++)
    {
        roundPointsWorth += animatronicsSave[i]->difficulty * 10;

        std::string name = animatronics[i]->name;

        

        if (name == "Killbot"){
            killbot* killbot = killbot::create(this, 10, animatronics[i]->difficulty);
            this->addChild(killbot);
        }
        else if (name == "Zoink"){
            zoink* zoink = zoink::create(this, 0.2f, animatronics[i]->difficulty);
            this->addChild(zoink);
        }
        else if (name == "Cube"){
            gdcube* cube = gdcube::create(this, 1, animatronics[i]->difficulty);
            this->addChild(cube);
        }
        else if (name == "Time Machine Dinosaur"){
            timeMachineDinosaur* TimeMachineDinosaur = timeMachineDinosaur::create(this, 5, animatronics[i]->difficulty);
            this->addChild(TimeMachineDinosaur);
        }
        else if (name == "Grandpa Demon"){
            grandpaDemon* GrandpaDemon = grandpaDemon::create(this, 0, animatronics[i]->difficulty);
            this->addChild(GrandpaDemon);
        }
        else if (name == "Viprin"){
            viprin* Viprin = viprin::create(this, 1, animatronics[i]->difficulty);
            this->addChild(Viprin);
        }
        else if (name == "Doggie"){
            doggie* Doggie = doggie::create(this, 0.05f, animatronics[i]->difficulty);
            this->addChild(Doggie);
        }
        else if (name == "Deadlocked Cubes"){
            deadlockedCubes* DeadlockedCubes = deadlockedCubes::create(this, 12, animatronics[i]->difficulty);
            this->addChild(DeadlockedCubes);
        }
        else if (name == "The Eschaton"){
            theEschaton* eschaton = theEschaton::create(this, 8, animatronics[i]->difficulty);
            this->addChild(eschaton);
        }
        else if (name == "Firework Skull"){
            fireworkSkull* fskull = fireworkSkull::create(this, 0.8f, animatronics[i]->difficulty);
            this->addChild(fskull);
        }
        else if (name == "Riot"){
            riot* Riot = riot::create(this, 0.1f, animatronics[i]->difficulty);
            this->addChild(Riot);
        }
        else if (name == "RobTop"){
            robtop* RobTop = robtop::create(this, animatronics[i]->difficulty);
            this->addChild(RobTop);
        }
        else if (name == "Spike"){
            spike* Spike = spike::create(this, 0.8f, animatronics[i]->difficulty);
            this->addChild(Spike);
        }
        else if (name == "Press Start"){
            pressStartSkull* PressStart = pressStartSkull::create(this, 12, animatronics[i]->difficulty);
            this->addChild(PressStart);
        }
        else if (name == "Npesta"){
            npesta* Npesta = npesta::create(this, 0.1f, animatronics[i]->difficulty);
            this->addChild(Npesta);
        }
        else if (name == "Loochi"){
            loochi* Loochi = loochi::create(this, animatronics[i]->difficulty);
            this->addChild(Loochi);
        }
        else if (name == "Theory of Everything II Monster"){
            toe2Monster* TheoryofEverythingIIMonster = toe2Monster::create(this, 0.8f, animatronics[i]->difficulty);
            this->addChild(TheoryofEverythingIIMonster);
        }
        else if (name == "Extreme Demon"){
            extremeDemonFace* ExtremeDemon = extremeDemonFace::create(this, 23, animatronics[i]->difficulty);
            this->addChild(ExtremeDemon);
        }
        else if (name == "Demon Gurdian"){
            basementMonster* bMonster = basementMonster::create(this, 23, animatronics[i]->difficulty);
            this->addChild(bMonster);//was 13 previ
        }
        else if (name == "The Keymaster"){
            voskeeper* TheKeymaster = voskeeper::create(this, 11, animatronics[i]->difficulty);
            this->addChild(TheKeymaster);
        }
        else if (name == "B"){
            B* bee = B::create(this, 0.025f, animatronics[i]->difficulty);
            this->addChild(bee);
        }
        else if (name == "Deadlocked Monsters"){
            deadlockedMonsters* Deadlockedm = deadlockedMonsters::create(this, 5, animatronics[i]->difficulty);
            this->addChild(Deadlockedm);
        }
        else if (name == "Magma Bound"){
            magmaBound* MagmaBound = magmaBound::create(this, 1, animatronics[i]->difficulty);
            this->addChild(MagmaBound);
        }
        else if (name == "The Gate Keeper"){
            cotDiff = animatronics[i]->difficulty;
        }
        else if (name == "Muchigun"){
            mechiDiff = animatronics[i]->difficulty;
        }
        else if (name == "Mindcap"){
            midncapDiff = animatronics[i]->difficulty;
        }
        else if (name == "Technical"){
            technical* Technical = technical::create(this, 12, animatronics[i]->difficulty);
            this->addChild(Technical);
        }
        else if (name == "Slaughterhouse Snowman"){
            SHSnowman* SlaughterhouseSnowman = SHSnowman::create(this, animatronics[i]->difficulty);
            this->addChild(SlaughterhouseSnowman);
        }
        else if (name == "KarmaL"){
            karmaL* KarmaL = karmaL::create(this, animatronics[i]->difficulty);
            this->addChild(KarmaL);
        }
        else if (name == "Requiem Cube"){
            reqCube* RequiemCube = reqCube::create(this, animatronics[i]->difficulty);
            this->addChild(RequiemCube);
        }
        else if (name == "Clubstep Monster"){
            clubstepMonster* ClubstepMonster = clubstepMonster::create(this, 17, animatronics[i]->difficulty);
            this->addChild(ClubstepMonster);
        }
        else if (name == "Shopkeeper"){
            shopkeeper* Shopkeeper = shopkeeper::create(this, 21, animatronics[i]->difficulty);
            this->addChild(Shopkeeper);
        }
        else if (name == "Bloodbath"){
            BB* Bloodbath = BB::create(this, 0.05f, animatronics[i]->difficulty);
            this->addChild(Bloodbath);
        }
        else if (name == "nSwish"){
            nSwish* nswish = nSwish::create(this, animatronics[i]->difficulty);
            this->addChild(nswish);
        }
        else if (name == "Spooky"){
            Spooky* spooky = Spooky::create(this, 0.8f, animatronics[i]->difficulty);
            this->addChild(spooky);
        }
        else if (name == "Demon"){
            DefaultDemonFace* Demon = DefaultDemonFace::create(this, animatronics[i]->difficulty);
            this->addChild(Demon);
        }
        else if (name == "SpaceUK"){
            SpaceUK* spaceUK = SpaceUK::create(this, 10, animatronics[i]->difficulty);
            this->addChild(spaceUK);
        }
        else if (name == "Animation Monster"){
            egcfra* AnimationMonster = egcfra::create(this, 1, animatronics[i]->difficulty);
            this->addChild(AnimationMonster);
        }
        else if (name == "Scratch"){
            SSKeeper* Scratch = SSKeeper::create(this, 0.8f, animatronics[i]->difficulty);
            this->addChild(Scratch);
        }
        else if (name == "Astral Devinity"){
            AstralD* AstralDevinity = AstralD::create(this, 11, animatronics[i]->difficulty);
            this->addChild(AstralDevinity);
        }
        else if (name == "Yatagarasu"){
            yata* Yatagarasu = yata::create(this, 30, animatronics[i]->difficulty);
            this->addChild(Yatagarasu);
        }
        else if (name == "EricVanWilderman"){
            EVW* EricVanWilderman = EVW::create(this, animatronics[i]->difficulty);
            this->addChild(EricVanWilderman);
        }
        else if (name == "Wulzy"){
            wulzy* Wulzy = wulzy::create(this, 5, animatronics[i]->difficulty);
            this->addChild(Wulzy);
        }
        else if (name == "Aeon Air"){
            aeonair* AeonAir = aeonair::create(this, 0.05f, animatronics[i]->difficulty);
            this->addChild(AeonAir);
        }
        else if (name == "Dorami"){
            dorami* Dorami = dorami::create(this, 1, animatronics[i]->difficulty);
            this->addChild(Dorami);
        }
        else if (name == "Crazy III Clown"){
            cIIIClown* CrazyIIIClown = cIIIClown::create(this, 1, animatronics[i]->difficulty);
            this->addChild(CrazyIIIClown);
        }
        else if (name == "Bloodlust"){
            bloodlust* Bloodlust = bloodlust::create(this, 0.8f, animatronics[i]->difficulty);
            this->addChild(Bloodlust);
        }
        else if (name == "Solar Flare Sun"){
            SFSun* SolarFlareSun = SFSun::create(this, animatronics[i]->difficulty);
            this->addChild(SolarFlareSun);
        }
        else if (name == "Potbor"){
            CSKeeper* Potbor = CSKeeper::create(this, 21, animatronics[i]->difficulty);
            this->addChild(Potbor);
        }
        else if (name == "Peaceful"){
            peacefulP* Peaceful = peacefulP::create(this, 9, animatronics[i]->difficulty);
            this->addChild(Peaceful);
        }

        if (mechiDiff != -1 && cotDiff != -1 && midncapDiff != -1 && !spawnedPlushes){
            spawnedPlushes = true;
            plushAnimatronics* plushes = plushAnimatronics::create(this, 45, cotDiff, midncapDiff, mechiDiff);
            this->addChild(plushes);
        }
    }

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    setKeypadEnabled(true);
    setKeyboardEnabled(true);

    scheduleUpdate();

    return true;
}

void CNGameLayer::onEnterTransitionDidFinish(){
    NIGHTSTARTED = true;
}

void CNGameLayer::update(float delta){

    if (doubleClickTimer > 0){
        doubleClickTimer -= delta;
    }
    if (NIGHTSTARTED){
        if (!nightStartedLock){
            nightStartedLock = true;
            OnNightStart();
        }

        if (!LookingAtCams){
            OutsideOfAll(delta);
        }
        else {
            AllCamsUpda(delta);
        }
        if (blackScreenFade > 2){
            blackScreenFade -= delta * 140; //num = speed
            BlackScreen->setOpacity((int)blackScreenFade);
        }
        else {
            BlackScreen->setOpacity(0);
        }

        NightTime += delta;
        NightTimeOverall += delta;
        std::string nightTimeDisplay = "";

        std::stringstream nightTimeSecondsFixed;
        nightTimeSecondsFixed << std::fixed << std::setprecision(1) << NightTime;

        if (NightTime < 10){
            nightTimeDisplay = std::to_string(NightMinutes) + ":0" + nightTimeSecondsFixed.str();
        }
        if (NightTime >= 10){
            nightTimeDisplay = std::to_string(NightMinutes) + ":" + nightTimeSecondsFixed.str();
        }

        if (NightTime >= 60){
            NightTime -= 60;
            NightMinutes++;
        }

        nightTimer->setString(nightTimeDisplay.c_str());

        if (escaping){
            escapeTimer -= delta;
        }
        if (escapeTimer <= 0){
            keyBackClicked();
        }

        if (RedBarFlashTimer > 0){
            RedBarFlashTimer -= delta;
        }
        else {
            RedBarFlashTimer = 0.1f;
            if (RedBarOpacity == 255){
                RedBarOpacity = 0;
                noiseS3Red->setOpacity(RedBarOpacity);
                noiseS4Red->setOpacity(RedBarOpacity);
                noiseS5Red->setOpacity(RedBarOpacity);
                noiseS6Red->setOpacity(RedBarOpacity);
                usageS5Red->setOpacity(RedBarOpacity);
                usageS6Red->setOpacity(RedBarOpacity);

                if (tempreture >= 99.5f){
                    tempretureText->setOpacity(RedBarOpacity);
                    littlDotThing->setOpacity(RedBarOpacity);
                }
            }
            else {
                RedBarOpacity = 255;
                noiseS3Red->setOpacity(RedBarOpacity);
                noiseS4Red->setOpacity(RedBarOpacity);
                noiseS5Red->setOpacity(RedBarOpacity);
                noiseS6Red->setOpacity(RedBarOpacity);
                usageS5Red->setOpacity(RedBarOpacity);
                usageS6Red->setOpacity(RedBarOpacity);

                if (tempreture >= 99.5f){
                    tempretureText->setOpacity(RedBarOpacity);
                    littlDotThing->setOpacity(RedBarOpacity);
                }
            }
            
        }

        if (tempreture < 99.5f){
            tempretureText->setOpacity(220);
            littlDotThing->setOpacity(220);
            tempretureText->setColor({ 255, 255, 255 });
            littlDotThing->setColor({ 255, 255, 255 });
            tempretureContainer->setScale(1);
        }
        else {
            tempretureText->setColor({ 186, 28, 28 });
            littlDotThing->setColor({ 186, 28, 28 });
            tempretureContainer->setScale(1.4f);
        }

        //noise
        switch (noiseAmount){
            case 1:
                noiseS1->setVisible(true);
                noiseS2->setVisible(false);
                noiseS3Red->setVisible(false);
                noiseS4Red->setVisible(false);
                noiseS5Red->setVisible(false);
                noiseS6Red->setVisible(false);
                break;

            case 2:
                noiseS1->setVisible(false);
                noiseS2->setVisible(true);
                noiseS3Red->setVisible(false);
                noiseS4Red->setVisible(false);
                noiseS5Red->setVisible(false);
                noiseS6Red->setVisible(false);
                break;

            case 3:
                noiseS1->setVisible(false);
                noiseS2->setVisible(false);
                noiseS3Red->setVisible(true);
                noiseS4Red->setVisible(false);
                noiseS5Red->setVisible(false);
                noiseS6Red->setVisible(false);
                break;
                
            case 4:
                noiseS1->setVisible(false);
                noiseS2->setVisible(false);
                noiseS3Red->setVisible(false);
                noiseS4Red->setVisible(true);
                noiseS5Red->setVisible(false);
                noiseS6Red->setVisible(false);
                break;

            case 5:
                noiseS1->setVisible(false);
                noiseS2->setVisible(false);
                noiseS3Red->setVisible(false);
                noiseS4Red->setVisible(false);
                noiseS5Red->setVisible(true);
                noiseS6Red->setVisible(false);
                break;

            default:
                break;
        }
        if (noiseAmount >= 6){
            noiseS1->setVisible(false);
            noiseS2->setVisible(false);
            noiseS3Red->setVisible(false);
            noiseS4Red->setVisible(false);
            noiseS5Red->setVisible(false);
            noiseS6Red->setVisible(true);
        }
        else if (noiseAmount <= 0){
            noiseS1->setVisible(false);
            noiseS2->setVisible(false);
            noiseS3Red->setVisible(false);
            noiseS4Red->setVisible(false);
            noiseS5Red->setVisible(false);
            noiseS6Red->setVisible(false);
        }

        //usage
        switch (usageAmount){
            case 1:
                usageS1->setVisible(true);
                usageS2->setVisible(false);
                usageS3->setVisible(false);
                usageS4->setVisible(false);
                usageS5Red->setVisible(false);
                usageS6Red->setVisible(false);
                break;

            case 2:
                usageS1->setVisible(false);
                usageS2->setVisible(true);
                usageS3->setVisible(false);
                usageS4->setVisible(false);
                usageS5Red->setVisible(false);
                usageS6Red->setVisible(false);
                break;

            case 3:
                usageS1->setVisible(false);
                usageS2->setVisible(false);
                usageS3->setVisible(true);
                usageS4->setVisible(false);
                usageS5Red->setVisible(false);
                usageS6Red->setVisible(false);
                break;

            case 4:
                usageS1->setVisible(false);
                usageS2->setVisible(false);
                usageS3->setVisible(false);
                usageS4->setVisible(true);
                usageS5Red->setVisible(false);
                usageS6Red->setVisible(false);
                break;

            case 5:
                usageS1->setVisible(false);
                usageS2->setVisible(false);
                usageS3->setVisible(false);
                usageS4->setVisible(false);
                usageS5Red->setVisible(true);
                usageS6Red->setVisible(false);
                break;

            default:
                break;
        }
        if (usageAmount >= 6){
            usageS1->setVisible(false);
            usageS2->setVisible(false);
            usageS3->setVisible(false);
            usageS4->setVisible(false);
            usageS5Red->setVisible(false);
            usageS6Red->setVisible(true);
        }
        else if (usageAmount <= 0){
            usageS1->setVisible(false);
            usageS2->setVisible(false);
            usageS3->setVisible(false);
            usageS4->setVisible(false);
            usageS5Red->setVisible(false);
            usageS6Red->setVisible(false);
        }

        if (Power > 0){
            Power -= (delta * (usageAmount + 1)) / 7.5f;

            if (currSpacialMode == SpacialMode::PowerGenerator){
                Power += (delta * (0.75f)) / 7.5f;
            }

            if (officeFlickerTimer > 0){
                officeFlickerTimer -= delta;
            }
            else {
                officeFlickerTimer = randomFloat(0.35f, 2.1f);
                PlayAnimationOnSprite(office, randomFloat(0.45f, 1.35f), 2, new std::string[]{
                "Main Office Flicker.png"_spr,
                "Main Office Light.png"_spr
                });
            }
            if (effectBlackscreenOpacity > 0){
                effectBlackscreenOpacity -= delta * 500;

                if (effectBlackscreenOpacity <= 0){
                    effectBlackscreenOpacity = 0;
                }
            }
            else {
                effectBlackscreenOpacity = 0;
            }
        }
        else {
            Power = 0;
            //No Power left
            if (!powerDownLock){
                powerDownLock = true;
                OnPowerDown();
            }
            if (SpacialBlackscreenOpacity < 255){
                SpacialBlackscreenOpacity += delta * 100;

                if (SpacialBlackscreenOpacity >= 255){
                    SpacialBlackscreenOpacity = 255;
                }
            }
            else {
                SpacialBlackscreenOpacity = 255;
            }
            officePowerDown->setVisible(true);
            office->setVisible(false);
        }
        
        effectBlackscreen->setOpacity(effectBlackscreenOpacity);
        SpacialBlackscreen->setOpacity(SpacialBlackscreenOpacity);

        std::stringstream PowerDisplayFix;
        PowerDisplayFix << std::fixed << std::setprecision(0) << Power;

        precentTextDy->setString(PowerDisplayFix.str().c_str());
        
        fazCoinsText->setString(std::to_string(fazCoins).c_str());

        if (tempreture >= 60 && tempreture <= 120){
            float maxSlowdown = 1;
            if (tempreture >= 100 && tempreture < 110){
                maxSlowdown = 0.65f;
            }
            else if (tempreture >= 110){
                maxSlowdown = 0.45f;
            }
            tempreture += (delta * (heatMultiplier + 1)) * maxSlowdown;

            tempreture -= delta * (CoolMultiplier * 3);
        }
        if (tempreture < 60){
            tempreture = 60;
        }
        if (tempreture > 120){
            tempreture = 120;
        }
        if (tempreture >= 120){
            if (fastVentelation){
                vetolationMutliplier = 3;
            }
            else {
                vetolationMutliplier = 2;
            }
        }
        else {
            if (fastVentelation){
                vetolationMutliplier = 2;
            }
            else {
                vetolationMutliplier = 1;
            }
        }
        std::stringstream tempretureDisplayFix;
        tempretureDisplayFix << std::fixed << std::setprecision(0) << tempreture;

        tempretureText->setString(tempretureDisplayFix.str().c_str());
        
        
        //1 am
        if (NightTimeOverall >= 60 && NightTimeOverall < 120){
            amTextDy->setString("1");
        }
        //2 am
        else if (NightTimeOverall >= 120 && NightTimeOverall < 180){
            amTextDy->setString("2");
        }
        //3 am
        else if (NightTimeOverall >= 180 && NightTimeOverall < 240){
            amTextDy->setString("3");
        }
        //4 am
        else if (NightTimeOverall >= 240 && NightTimeOverall < 300){
            amTextDy->setString("4");
        }
        //5 am
        else if (NightTimeOverall >= 300 && NightTimeOverall < 360){
            amTextDy->setString("5");
        }
        //6 am
        else if (NightTimeOverall >= 360){
            amTextDy->setString("6");
            //end the night here
            NIGHTSTARTED = false;
            desk->pauseSchedulerAndActions();
            doorLeft->pauseSchedulerAndActions();
            doorRight->pauseSchedulerAndActions();
            doorUp->pauseSchedulerAndActions();
            doorBottomRight->pauseSchedulerAndActions();
            CandyCoddet->pauseSchedulerAndActions();
            nightTimer->setString("6:00.0");
            Mask->pauseSchedulerAndActions();
            if (bgMusic != nullptr){
                bgMusic->CleanUpSound();
            }
            Ambiance->CleanUpSound();
            
            Cams->pauseSchedulerAndActions();
            if (musicBoxAudio != nullptr){
                musicBoxAudio->RemoveMeAndCleanUpSound();
                musicBoxAudio = nullptr;
            }
            fanSound->RemoveMeAndCleanUpSound();
            nightComplete = true;
            if (roundPointsWorth >= 0 && roundPointsWorth < 800){
                completionMusic = AudioSource::create("winnight.mp3"_spr, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
            if (roundPointsWorth >= 800 && roundPointsWorth < 1800){
                completionMusic = AudioSource::create("10sec C.mp3"_spr, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
            if (roundPointsWorth >= 1800 && roundPointsWorth < 3800){
                completionMusic = AudioSource::create("20sec C.mp3"_spr, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
            if (roundPointsWorth >= 3800 && roundPointsWorth < 6200){
                completionMusic = AudioSource::create("30sec C.mp3"_spr, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
            if (roundPointsWorth >= 6200 && roundPointsWorth < 8000){
                completionMusic = AudioSource::create("40sec C.mp3"_spr, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
            if (roundPointsWorth >= 8000){
                completionMusic = AudioSource::create("60sec C.mp3"_spr, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
            this->addChild(completionMusic);
        }

        //mask
        if (getHover(MaskButtonDetection) && !buttonHoverLock && !InCams){
            buttonHoverLock = true;
            InMask = !InMask;
            CamsButton->setVisible(false);
            if (InMask){
                FMODAudioEngine::sharedEngine()->playEffect("maskon.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                PlayAnimationOnSprite(Mask, 0.02f, 9, new std::string[]{
                    "mask1.png"_spr,
                    "mask2.png"_spr,
                    "mask3.png"_spr,
                    "mask4.png"_spr,
                    "mask5.png"_spr,
                    "mask6.png"_spr,
                    "mask7.png"_spr,
                    "mask8.png"_spr,
                    "mask9.png"_spr
                });
            }
            else {
                CamsButton->setVisible(true);
                FMODAudioEngine::sharedEngine()->playEffect("maskoff.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                PlayAnimationOnSprite(Mask, 0.02f, 9, new std::string[]{
                    "mask9.png"_spr,
                    "mask8.png"_spr,
                    "mask7.png"_spr,
                    "mask6.png"_spr,
                    "mask5.png"_spr,
                    "mask4.png"_spr,
                    "mask3.png"_spr,
                    "mask2.png"_spr,
                    "mask1.png"_spr
                });
            }
        }

        //cameras
        if (!camsDisabled){
            if (getHover(CamsButtonDetection) && !buttonHoverLock && !InMask && Power > 0){

                if (!InCams){
                    InCams = true;
                    buttonHoverLock = true;
                    
                    FMODAudioEngine::sharedEngine()->playEffect("camera.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                    PlayAnimationOnSpriteWithCallBack(Cams, 0.02f, 12, new std::string[]{
                        "monitor1.png"_spr,
                        "monitor2.png"_spr,
                        "monitor3.png"_spr,
                        "monitor4.png"_spr,
                        "monitor5.png"_spr,
                        "monitor6.png"_spr,
                        "monitor7.png"_spr,
                        "monitor8.png"_spr,
                        "monitor9.png"_spr,
                        "monitor10.png"_spr,
                        "monitor11.png"_spr,
                        "monitor12.png"_spr
                    },
                    callfunc_selector(CNGameLayer::onCamsOpened));
                }
                else if (LookingAtCams) {
                    InCams = false;
                    PlayAnimationOnSprite(Cams, 0, 2, new std::string[]{
                        "monitor12.png"_spr,
                        "monitor12.png"_spr
                    });
                    buttonHoverLock = true;
                    LookingAtCams = false;
                    usageAmount--;
                    MaskButton->setVisible(true);
                    cameraView->setPosition({0, 999});
                    CamsButton->setOpacity(255);
                    cameraUI->setPosition({0, 999});
                    cameraOverallUI->setPosition({0, 999});
                    ventUI->setPosition({0, 999});
                    ductUI->setPosition({0, 999});
                    FMODAudioEngine::sharedEngine()->playEffect("putdown.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                    if (currSpacialMode != SpacialMode::GMB && musicBoxAudio != nullptr){
                        musicBoxAudio->RemoveMeAndCleanUpSound();
                        musicBoxAudio = nullptr;
                    }

                    PlayAnimationOnSprite(Cams, 0.02f, 12, new std::string[]{
                        "monitor12.png"_spr,
                        "monitor11.png"_spr,
                        "monitor10.png"_spr,
                        "monitor9.png"_spr,
                        "monitor8.png"_spr,
                        "monitor7.png"_spr,
                        "monitor6.png"_spr,
                        "monitor5.png"_spr,
                        "monitor4.png"_spr,
                        "monitor3.png"_spr,
                        "monitor2.png"_spr,
                        "monitor1.png"_spr
                    });
                }
            }
        }
        else {
            if (getHover(CamsButtonDetection) && !buttonHoverLock && !InMask && Power > 0){
                buttonHoverLock = true;
                FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
        }


        CamStatic->setVisible(LookingAtCams);

        if (!getHover(CamsButtonDetection) && !getHover(MaskButtonDetection) && buttonHoverLock){
            buttonHoverLock = false;
        }

        if (CamStaticOpacity > 60){
            CamStaticOpacity -= delta * 600;
        }
        CamStatic->setOpacity((int)CamStaticOpacity);

        if (cameraView->getPositionX() >= 72){
            moveToRight = true;
        }
        if (cameraView->getPositionX() <= -72){
            moveToRight = false;
        }

        CamViewStatic->setPosition({-cameraView->getPositionX(), 0});

        if (movementPauseTimer > 0 && cameraView->getPositionX() >= 72 || movementPauseTimer > 0 && cameraView->getPositionX() <= -72){
            movementPauseTimer -= delta;
        }
        else {
            movementPauseTimer = 3;
            if (!moveToRight){
                cameraView->setPositionX(cameraView->getPositionX() + (delta * 20));
            }
            else {
                cameraView->setPositionX(cameraView->getPositionX() - (delta * 20));
            }
            if (cameraView->getPositionX() >= 72){
                cameraView->setPositionX(72);
            }
            if (cameraView->getPositionX() <= -72){
                cameraView->setPositionX(-72);
            }
        }

        if (vetelationTimer > 0){
            vetelationTimer -= delta * vetolationMutliplier;
        }
        else {
            canResetVen = true;
            resetVentelationActive->setVisible(true);
            resetVentelation->setVisible(false);
            venWarnMask->setVisible(true);
            venWarnCams->setVisible(true);
            if (SpacialBlackscreenOpacity < 255){
                SpacialBlackscreenOpacity += delta * (20 * vetolationMutliplier);

                if (SpacialBlackscreenOpacity >= 255){
                    SpacialBlackscreenOpacity = 255;
                }
            }
            else {
                SpacialBlackscreenOpacity = 255;
            }
        }
        if (getTouchOn(resetVentelation)){
            FMODAudioEngine::sharedEngine()->playEffect("Snapmouse_1_clk_3.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            if (canResetVen){
                canResetVen = false;
                vetelationTimer = 30;
                SpacialBlackscreenOpacity = 0;
                resetVentelationActive->setVisible(false);
                resetVentelation->setVisible(true);
                venWarnMask->setVisible(false);
                venWarnCams->setVisible(false);
            }
        }
        
        if (confirmLookingAtCams){
            confirmLookingAtCams = false;
            LookingAtCams = true;
        }
        if (flashForTime > 0){
            playBlackFlashes = true;
            flashForTime -= delta;
        }
        else {
            playBlackFlashes = false;
        }
        if (playBlackFlashes){
            if (FlashRate > 0){
                FlashRate -= delta;
            }
            else{
                FlashRate = 0.1f;
                effectBlackscreenOpacity = 255;
            }
        }
        else{
            FlashRate = 0;
        }
    }
    if (inJumpscare){
        inJumpUpdate(delta);
    }
    if (DEATHSCREEN){
        deathscreenUpdate(delta);
    }
    if (nightComplete){
        NightCompleteUpdate(delta);
    }
    
}

void CNGameLayer::onCamsOpened(){
    confirmLookingAtCams = true;
    CamStatic->setVisible(true);
    CamStaticOpacity = 255;
    usageAmount++;
    cameraView->setPosition({0, 0});
    cameraUI->setPosition({0, 0});
    MaskButton->setVisible(false);
    CamsButton->setOpacity(150);
    cameraOverallUI->setPosition({0, 0});
    ventUI->setPosition({0, 0});
    ductUI->setPosition({0, 0});
    PlayAnimationOnSprite(Cams, 0.01f, 2, new std::string[]{
        "monitor13.png"_spr,
        "monitor13.png"_spr
    });
    if (currSpacialMode != SpacialMode::GMB){
        musicBoxAudio = AudioSource::create(currMusicString, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        this->addChild(musicBoxAudio);
    }
    SwitchCamera(currentCamSelected);
}

void CNGameLayer::AllCamsUpda(float delta){
    if (inCamSys){
        if (getTouchOn(Cam01ButtonOn)){
            SwitchCamera(Camera01);
            musicBoxCont->setVisible(false);
        }
        if (getTouchOn(Cam02ButtonOn)){
            SwitchCamera(Camera02);
            musicBoxCont->setVisible(false);
        }
        if (getTouchOn(Cam03ButtonOn)){
            SwitchCamera(Camera03);
            musicBoxCont->setVisible(false);
        }
        if (getTouchOn(Cam04ButtonOn)){
            SwitchCamera(Camera04);
            musicBoxCont->setVisible(true);
        }
        if (getTouchOn(Cam05ButtonOn)){
            SwitchCamera(Camera05);
            musicBoxCont->setVisible(false);
        }
        if (getTouchOn(Cam06ButtonOn)){
            SwitchCamera(Camera06);
            musicBoxCont->setVisible(false);
        }
        if (getTouchOn(Cam07ButtonOn)){
            SwitchCamera(Camera07);
            musicBoxCont->setVisible(false);
        }
        if (getTouchOn(Cam08ButtonOn)){
            SwitchCamera(Camera08);
            musicBoxCont->setVisible(false);
        }
        if (currentCamSelected == Camera07){
            if (!baughtDeathCoin && fazCoins >= 10){
                if (getTouchOn(deathCoinBuyButtton)){
                    baughtDeathCoin = true;
                    deathcoinSoff->setVisible(true);
                    fazCoins -= 10;
                    deathCoinBuyButtton->setVisible(false);
                    FMODAudioEngine::sharedEngine()->playEffect("reg2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                }
            }
        }
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                if (getHover(CamCoins[i]->sprite)){
                    CamCoins[i]->sprite->removeMeAndCleanup();
                    CamCoins[i]->sprite = nullptr;
                    fazCoins++;
                    FMODAudioEngine::sharedEngine()->playEffect("coin.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                }
            }
        }
        
    }
    if (inVentSys){
        if (getTouchOn(ventSnareEmptyRight)){
            snareLocation = ventSnareLocation::right;
            ventSnareEmptyRight->setVisible(false);
            ventSnareSelectedRight->setVisible(true);
            ventSnareEmptyLeft->setVisible(true);
            ventSnareSelectedLeft->setVisible(false);
            ventSnareEmptyTop->setVisible(true);
            ventSnareSelectedTop->setVisible(false);
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(ventSnareEmptyLeft)){
            snareLocation = ventSnareLocation::left;
            ventSnareEmptyRight->setVisible(true);
            ventSnareSelectedRight->setVisible(false);
            ventSnareEmptyLeft->setVisible(false);
            ventSnareSelectedLeft->setVisible(true);
            ventSnareEmptyTop->setVisible(true);
            ventSnareSelectedTop->setVisible(false);
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(ventSnareEmptyTop)){
            snareLocation = ventSnareLocation::up;
            ventSnareEmptyRight->setVisible(true);
            ventSnareSelectedRight->setVisible(false);
            ventSnareEmptyLeft->setVisible(true);
            ventSnareSelectedLeft->setVisible(false);
            ventSnareEmptyTop->setVisible(false);
            ventSnareSelectedTop->setVisible(true);
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
    }
    if (inDuctSys){
        if (RightDuctOpen){
            if (getTouchOn(OpenDuctLeftB)){
                RightDuctOpen = false;
                OpenDuctLeftB->setOpacity(150);
                OpenDuctRightB->setOpacity(255);
                openDuctArrow->setPosition({-118, -76});
                ClosedDuctX->setPosition({-43, -76});
                FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
        }
        else {
            if (getTouchOn(OpenDuctRightB)){
                RightDuctOpen = true;
                OpenDuctLeftB->setOpacity(255);
                OpenDuctRightB->setOpacity(150);
                openDuctArrow->setPosition({-43, -76});
                ClosedDuctX->setPosition({-118, -76});
                FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            }
        }
        if (getTouchOn(topleftContactPoint1)){
            audioLoreLocation = ductLocations::entrenceLeft1;
            audioLore->setPosition(topleftContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(topleftContactPoint2)){
            audioLoreLocation = ductLocations::entrenceLeft2;
            audioLore->setPosition(topleftContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toprightContactPoint1)){
            audioLoreLocation = ductLocations::entrenceRight1;
            audioLore->setPosition(toprightContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toprightContactPoint2)){
            audioLoreLocation = ductLocations::entrenceRight1;
            audioLore->setPosition(toprightContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint1)){
            audioLoreLocation = ductLocations::topLine1;
            audioLore->setPosition(toplineContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint2)){
            audioLoreLocation = ductLocations::topLine2;
            audioLore->setPosition(toplineContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint3)){
            audioLoreLocation = ductLocations::topLine3;
            audioLore->setPosition(toplineContactPoint3->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint4)){
            audioLoreLocation = ductLocations::topLine4;
            audioLore->setPosition(toplineContactPoint4->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint5)){
            audioLoreLocation = ductLocations::topLine5;
            audioLore->setPosition(toplineContactPoint5->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint6)){
            audioLoreLocation = ductLocations::topLine6;
            audioLore->setPosition(toplineContactPoint6->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(toplineContactPoint7)){
            audioLoreLocation = ductLocations::topLine7;
            audioLore->setPosition(toplineContactPoint7->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(topRightTurn)){
            audioLoreLocation = ductLocations::topRightTurn_;
            audioLore->setPosition(topRightTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(topLeftTurn)){
            audioLoreLocation = ductLocations::topLeftTurn_;
            audioLore->setPosition(topLeftTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(rightLineContactPoint1)){
            audioLoreLocation = ductLocations::rightLine1;
            audioLore->setPosition(rightLineContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(rightLineContactPoint2)){
            audioLoreLocation = ductLocations::rightLine2;
            audioLore->setPosition(rightLineContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(rightLineContactPoint3)){
            audioLoreLocation = ductLocations::rightLine3;
            audioLore->setPosition(rightLineContactPoint3->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(rightLineContactPoint4)){
            audioLoreLocation = ductLocations::rightLine4;
            audioLore->setPosition(rightLineContactPoint4->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(bottomRightTurn)){
            audioLoreLocation = ductLocations::bottomRightTurn_;
            audioLore->setPosition(bottomRightTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineContactPoint1)){
            audioLoreLocation = ductLocations::middleLine1;
            audioLore->setPosition(middleLineContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineContactPoint2)){
            audioLoreLocation = ductLocations::middleLine2;
            audioLore->setPosition(middleLineContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineContactPoint3)){
            audioLoreLocation = ductLocations::middleLine3;
            audioLore->setPosition(middleLineContactPoint3->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineContactPoint4)){
            audioLoreLocation = ductLocations::middleLine4;
            audioLore->setPosition(middleLineContactPoint4->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineContactPoint5)){
            audioLoreLocation = ductLocations::middleLine5;
            audioLore->setPosition(middleLineContactPoint5->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }

        if (getTouchOn(middleLineContactPoint6)){
            audioLoreLocation = ductLocations::middleLine6;
            audioLore->setPosition(middleLineContactPoint6->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineTurn)){
            audioLoreLocation = ductLocations::middleLineTurn_;
            audioLore->setPosition(middleLineTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineUpContactPoint1)){
            audioLoreLocation = ductLocations::middleLineUp1;
            audioLore->setPosition(middleLineUpContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(middleLineUpContactPoint2)){
            audioLoreLocation = ductLocations::middleLineUp2;
            audioLore->setPosition(middleLineUpContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(rightMiddleTurn)){
            audioLoreLocation = ductLocations::rightMiddleTurn_;
            audioLore->setPosition(rightMiddleTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(leftLineContactPoint1)){
            audioLoreLocation = ductLocations::leftLine1;
            audioLore->setPosition(leftLineContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(leftLineContactPoint2)){
            audioLoreLocation = ductLocations::leftLine2;
            audioLore->setPosition(leftLineContactPoint2->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(leftLineContactPoint3)){
            audioLoreLocation = ductLocations::leftLine3;
            audioLore->setPosition(leftLineContactPoint3->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(leftLineContactPoint4)){
            audioLoreLocation = ductLocations::leftLine4;
            audioLore->setPosition(leftLineContactPoint4->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(bottomLeftTurn)){
            audioLoreLocation = ductLocations::bottomLeftTurn_;
            audioLore->setPosition(bottomLeftTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(leftMiddleTurn)){
            audioLoreLocation = ductLocations::leftMiddleTurn_;
            audioLore->setPosition(leftMiddleTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(bottomRightLineContactPoint1)){
            audioLoreLocation = ductLocations::bottomRightLine1;
            audioLore->setPosition(bottomRightLineContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(bottomLeftLineContactPoint1)){
            audioLoreLocation = ductLocations::bottomLeftLine1;
            audioLore->setPosition(bottomLeftLineContactPoint1->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(bottomLeftToEndTurn)){
            audioLoreLocation = ductLocations::bottomLeftToEndTurn_;
            audioLore->setPosition(bottomLeftToEndTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(bottomRightToEndTurn)){
            audioLoreLocation = ductLocations::bottomRightToEndTurn_;
            audioLore->setPosition(bottomRightToEndTurn->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(RightEndContactPoint)){
            audioLoreLocation = ductLocations::RightEnd;
            audioLore->setPosition(RightEndContactPoint->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        if (getTouchOn(LeftEndContactPoint)){
            audioLoreLocation = ductLocations::LeftEnd;
            audioLore->setPosition(LeftEndContactPoint->getPosition());
            FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
    }
    if (getTouchOn(camSystem)){
        systemButtonsBG->setPosition(camSystem->getPosition());
        inCamSys = true;
        inVentSys = false;
        inDuctSys = false;
        CamStaticOpacity = 255;
        cameraUI->setVisible(true);
        cameraView->setVisible(true);
        ventUI->setVisible(true);
        ductUI->setVisible(true);
        FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    }
    if (getTouchOn(ventSystem)){
        systemButtonsBG->setPosition(ventSystem->getPosition());
        inCamSys = false;
        inVentSys = true;
        inDuctSys = false;
        CamStaticOpacity = 255;
        cameraUI->setVisible(false);
        cameraView->setVisible(false);
        ventUI->setVisible(true);
        ductUI->setVisible(false);
        FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    }
    if (getTouchOn(ductSystem)){
        systemButtonsBG->setPosition(ductSystem->getPosition());
        inCamSys = false;
        inVentSys = false;
        inDuctSys = true;
        CamStaticOpacity = 255;
        cameraUI->setVisible(false);
        cameraView->setVisible(false);
        ventUI->setVisible(false);
        ductUI->setVisible(true);
        FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    }
    if (getTouchOn(powerGenButton)){
        setSpacialMode(SpacialMode::PowerGenerator);
    }
    if (getTouchOn(silVentButton)){
        setSpacialMode(SpacialMode::SilentVentelation);
    }
    if (getTouchOn(heaterButton)){
        setSpacialMode(SpacialMode::Heater);
    }
    if (getTouchOn(powerACButton)){
        setSpacialMode(SpacialMode::PowerAC);
    }
    if (getTouchOn(GMBButton)){
        setSpacialMode(SpacialMode::GMB);
    }
    if (getTouchOn(spacialsOffButton)){
        setSpacialMode(SpacialMode::Off);
    }
}

void CNGameLayer::OnNightStart(){
    fanSound = AudioSource::create("fan.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    this->addChild(fanSound);

    int songSelected = rand() % 6;

    bool noMusic = false;

    Ambiance = AudioSource::create("ambiance2.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    this->addChild(Ambiance);

    switch (songSelected)
    {
    case 0:
        bgMusic = AudioSource::create("Hybernating Evil.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        break;

    case 1:
        bgMusic = AudioSource::create("Last Breath.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        break;

    case 2:
        bgMusic = AudioSource::create("Sleep No Morev2.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        break;

    case 3:
        bgMusic = AudioSource::create("Sonata for the Fallen.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        break;

    case 4:
        bgMusic = AudioSource::create("Where Dreams Die.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        break;

    case 5:
        noMusic = true;
        break;
    
    default:
        break;
    }
    if (!noMusic){
        this->addChild(bgMusic);
    }
    else {
        bgMusic = nullptr;
    }
}

float CNGameLayer::randomFloat(int a, int b)
{
    if (a > b)
        return randomFloat(b, a);
    if (a == b)
        return a;
 
    return (float)randomInt(a, b) + randomFloat();
}

float CNGameLayer::randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}
 
int CNGameLayer::randomInt(int a, int b)
{
    if (a > b)
        return randomInt(b, a);
    if (a == b)
        return a;
    return a + (rand() % (b - a));
}

void CNGameLayer::OnPowerDown(){
    FMODAudioEngine::sharedEngine()->playEffect("powerdown.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    setSpacialMode(SpacialMode::Off);
    if (fanOn){
        fanOn = false;
        FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        desk->pauseSchedulerAndActions();
        noiseAmount--;
        usageAmount--;
        CoolMultiplier--;
    }
    if (doorLeftClosed){
        doorLeftClosed = false;
        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        PlayAnimationOnSprite(doorLeft, 0.03f, 11, new std::string[]{
            "doorLeft11.png"_spr,
            "doorLeft10.png"_spr,
            "doorLeft9.png"_spr,
            "doorLeft8.png"_spr,
            "doorLeft7.png"_spr,
            "doorLeft6.png"_spr,
            "doorLeft5.png"_spr,
            "doorLeft4.png"_spr,
            "doorLeft3.png"_spr,
            "doorLeft2.png"_spr,
            "doorLeft1.png"_spr
        });
        usageAmount--;
    }
    if (doorUpClosed){
        doorUpClosed = false;
        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        PlayAnimationOnSprite(doorUp, 0.03f, 7, new std::string[]{
            "doorUp7.png"_spr,
            "doorUp6.png"_spr,
            "doorUp5.png"_spr,
            "doorUp4.png"_spr,
            "doorUp3.png"_spr,
            "doorUp2.png"_spr,
            "doorUp1.png"_spr
        });
        usageAmount--;
    }
    if (doorRightClosed){
        doorRightClosed = false;
        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        PlayAnimationOnSprite(doorRight, 0.03f, 11, new std::string[]{
            "doorRight11.png"_spr,
            "doorRight10.png"_spr,
            "doorRight9.png"_spr,
            "doorRight8.png"_spr,
            "doorRight7.png"_spr,
            "doorRight6.png"_spr,
            "doorRight5.png"_spr,
            "doorRight4.png"_spr,
            "doorRight3.png"_spr,
            "doorRight2.png"_spr,
            "doorRight1.png"_spr
        });
        usageAmount--;
    }
    if (doorBottomRightClosed){
        doorBottomRightClosed = false;
        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        PlayAnimationOnSprite(doorBottomRight, 0.03f, 6, new std::string[]{
            "doorBottomRight6.png"_spr,
            "doorBottomRight5.png"_spr,
            "doorBottomRight4.png"_spr,
            "doorBottomRight3.png"_spr,
            "doorBottomRight2.png"_spr,
            "doorBottomRight1.png"_spr
        });
        usageAmount--;
    }
    if (FlashlightOn){
        FlashlightOn = false;
        Flashlight->setVisible(false);
        usageAmount--;
        FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    }
    if (bgMusic != nullptr){
        bgMusic->CleanUpSound();
    }
    Ambiance->CleanUpSound();
    
    if (InCams){
        InCams = false;
        if (LookingAtCams){
            LookingAtCams = false;
            usageAmount--;
        }
        PlayAnimationOnSprite(Cams, 0, 2, new std::string[]{
            "monitor12.png"_spr,
            "monitor12.png"_spr
        });
        MaskButton->setVisible(true);
        cameraView->setPosition({0, 999});
        CamsButton->setOpacity(255);
        cameraUI->setPosition({0, 999});
        cameraOverallUI->setPosition({0, 999});
        ventUI->setPosition({0, 999});
        ductUI->setPosition({0, 999});
        FMODAudioEngine::sharedEngine()->playEffect("putdown.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        PlayAnimationOnSprite(Cams, 0.02f, 12, new std::string[]{
            "monitor12.png"_spr,
            "monitor11.png"_spr,
            "monitor10.png"_spr,
            "monitor9.png"_spr,
            "monitor8.png"_spr,
            "monitor7.png"_spr,
            "monitor6.png"_spr,
            "monitor5.png"_spr,
            "monitor4.png"_spr,
            "monitor3.png"_spr,
            "monitor2.png"_spr,
            "monitor1.png"_spr
        });
    }
    if (musicBoxAudio != nullptr){
        musicBoxAudio->RemoveMeAndCleanUpSound();
        musicBoxAudio = nullptr;
    }
}

void CNGameLayer::OutsideOfAll(float delta){

    //get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

    CCPoint layerPos = World->getPosition();

    float newX = layerPos.x + (delta * camMovementSpeed);

    //newX += -90;
    
    if (newX > (90 - (windowSize.width / 2))){
        newX = (90 - (windowSize.width / 2));
    }
    else if (newX < (-90 - (windowSize.width / 2))){
        newX = (-90 - (windowSize.width / 2));
    }
    
    CCPoint deskPos = desk->getPosition();

    desk->setPosition({(((-newX - (windowSize.width / 2)) / 9) + (windowSize.width / 2)), 114});
    World->setPosition({newX, layerPos.y});

    if (World->getPositionX() >= -284.5f){
        lookingTowardsRight = false;
    }
    else {
        lookingTowardsRight = true;
    }
    
    if (getHover(MoveDetecSlowRight)){
        camMovementSpeed = -200;
    }
    else if (getHover(MoveDetecFastRight)){
        camMovementSpeed = -600;
    }
    else if (getHover(MoveDetecSlowLeft)){
        camMovementSpeed = 200;
    }
    else if (getHover(MoveDetecFastLeft)){
        camMovementSpeed = 600;
    }
    else {
        camMovementSpeed = 0;
    }

    if (candyCoddetPulseTimer > 0){
        candyCoddetPulseTimer -= delta;
    }
    else {
        candyCoddetPulseTimer = 5 + (rand() % 30);
        PlayAnimationOnSprite(CandyCoddet, 0.06f, 11, new std::string[]{
        "candyCoddet1.png"_spr,
        "candyCoddet2.png"_spr,
        "candyCoddet3.png"_spr,
        "candyCoddet4.png"_spr,
        "candyCoddet5.png"_spr,
        "candyCoddet6.png"_spr,
        "candyCoddet7.png"_spr,
        "candyCoddet8.png"_spr,
        "candyCoddet9.png"_spr,
        "candyCoddet10.png"_spr,
        "candyCoddet11.png"_spr
        });
        int voiceLine = rand() % 4;

        switch(voiceLine){
            case 0:
                FMODAudioEngine::sharedEngine()->playEffect("cadetghost1.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                break;

            case 1:
                FMODAudioEngine::sharedEngine()->playEffect("cadetghost2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                break;

            case 2:
                FMODAudioEngine::sharedEngine()->playEffect("cadetghost3.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                break;

            case 3:
                FMODAudioEngine::sharedEngine()->playEffect("cadetghost4.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                break;

            default:
                break;
        }
    }

    if (getTouchOn(freedyNoseHitbox)){
        FMODAudioEngine::sharedEngine()->playEffect("partyfavor.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    }

    if (getTouchOnDouble(floorSignLeft)){
        if (floorSignOnLeft){
            floorSignLeft->setVisible(false);
            floorSignRight->setVisible(true);
            floorSignOnLeft = false;
            FMODAudioEngine::sharedEngine()->playEffect("metal6.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
    }

    if (getTouchOnDouble(floorSignRight)){
        if (!floorSignOnLeft){
            floorSignLeft->setVisible(true);
            floorSignRight->setVisible(false);
            floorSignOnLeft = true;
            FMODAudioEngine::sharedEngine()->playEffect("metal6.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        }
        
    }
}

void CNGameLayer::keyBackClicked() {
    if (escapeTimer <= 0){
        escaped = true;
        fanSound->CleanUpSound();
        escapeTimer = 100;
        CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
        if (bgMusic != nullptr){
            bgMusic->CleanUpSound();
        }
        Ambiance->CleanUpSound();
    }
}

void CNGameLayer::keyDown(enumKeyCodes keyCode){
    if (NIGHTSTARTED){
        if (Power > 0){
            if (keyCode == enumKeyCodes::KEY_Space){
                fanOn = !fanOn;

                FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                if (fanOn){
                    fanSound->Paused(false);
                    desk->resumeSchedulerAndActions();
                    noiseAmount++;
                    usageAmount++;
                    CoolMultiplier++;
                }
                else {
                    fanSound->Paused(true);
                    desk->pauseSchedulerAndActions();
                    noiseAmount--;
                    usageAmount--;
                    CoolMultiplier--;
                }
            }
            else if (keyCode == enumKeyCodes::KEY_A){
                if (!blockDoorUsage){
                    doorLeftClosed = !doorLeftClosed;

                    FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                    if (doorLeftClosed){
                        PlayAnimationOnSprite(doorLeft, 0.03f, 11, new std::string[]{
                            "doorLeft1.png"_spr,
                            "doorLeft2.png"_spr,
                            "doorLeft3.png"_spr,
                            "doorLeft4.png"_spr,
                            "doorLeft5.png"_spr,
                            "doorLeft6.png"_spr,
                            "doorLeft7.png"_spr,
                            "doorLeft8.png"_spr,
                            "doorLeft9.png"_spr,
                            "doorLeft10.png"_spr,
                            "doorLeft11.png"_spr
                        });
                        usageAmount++;
                    }
                    else {
                        PlayAnimationOnSprite(doorLeft, 0.03f, 11, new std::string[]{
                            "doorLeft11.png"_spr,
                            "doorLeft10.png"_spr,
                            "doorLeft9.png"_spr,
                            "doorLeft8.png"_spr,
                            "doorLeft7.png"_spr,
                            "doorLeft6.png"_spr,
                            "doorLeft5.png"_spr,
                            "doorLeft4.png"_spr,
                            "doorLeft3.png"_spr,
                            "doorLeft2.png"_spr,
                            "doorLeft1.png"_spr
                        });
                        usageAmount--;
                    }
                }
                else {
                    if (doorLeftClosed){
                        doorLeftClosed = false;
                        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                        PlayAnimationOnSprite(doorLeft, 0.03f, 11, new std::string[]{
                            "doorLeft11.png"_spr,
                            "doorLeft10.png"_spr,
                            "doorLeft9.png"_spr,
                            "doorLeft8.png"_spr,
                            "doorLeft7.png"_spr,
                            "doorLeft6.png"_spr,
                            "doorLeft5.png"_spr,
                            "doorLeft4.png"_spr,
                            "doorLeft3.png"_spr,
                            "doorLeft2.png"_spr,
                            "doorLeft1.png"_spr
                        });
                        usageAmount--;
                    }
                    else {
                        FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    }
                }
            }
            else if (keyCode == enumKeyCodes::KEY_W){
                if (!blockDoorUsage){
                    doorUpClosed = !doorUpClosed;

                    FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
        
                    if (doorUpClosed){
                        PlayAnimationOnSprite(doorUp, 0.03f, 7, new std::string[]{
                        "doorUp1.png"_spr,
                        "doorUp2.png"_spr,
                        "doorUp3.png"_spr,
                        "doorUp4.png"_spr,
                        "doorUp5.png"_spr,
                        "doorUp6.png"_spr,
                        "doorUp7.png"_spr
                        });
                        usageAmount++;
                    }
                    else {
                        PlayAnimationOnSprite(doorUp, 0.03f, 7, new std::string[]{
                        "doorUp7.png"_spr,
                        "doorUp6.png"_spr,
                        "doorUp5.png"_spr,
                        "doorUp4.png"_spr,
                        "doorUp3.png"_spr,
                        "doorUp2.png"_spr,
                        "doorUp1.png"_spr
                        });
                        usageAmount--;
                    }
                }
                else{
                    if (doorUpClosed){
                        doorUpClosed = false;
                        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                        PlayAnimationOnSprite(doorUp, 0.03f, 7, new std::string[]{
                        "doorUp7.png"_spr,
                        "doorUp6.png"_spr,
                        "doorUp5.png"_spr,
                        "doorUp4.png"_spr,
                        "doorUp3.png"_spr,
                        "doorUp2.png"_spr,
                        "doorUp1.png"_spr
                        });
                        usageAmount--;
                    }
                    else{
                        FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    }
                }
            }
            else if (keyCode == enumKeyCodes::KEY_D){
                if (!blockDoorUsage){
                    doorRightClosed = !doorRightClosed;

                    FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                    if (doorRightClosed){
                        PlayAnimationOnSprite(doorRight, 0.03f, 11, new std::string[]{
                        "doorRight1.png"_spr,
                        "doorRight2.png"_spr,
                        "doorRight3.png"_spr,
                        "doorRight4.png"_spr,
                        "doorRight5.png"_spr,
                        "doorRight6.png"_spr,
                        "doorRight7.png"_spr,
                        "doorRight8.png"_spr,
                        "doorRight9.png"_spr,
                        "doorRight10.png"_spr,
                        "doorRight11.png"_spr
                        });
                        usageAmount++;
                    }
                    else {
                        PlayAnimationOnSprite(doorRight, 0.03f, 11, new std::string[]{
                        "doorRight11.png"_spr,
                        "doorRight10.png"_spr,
                        "doorRight9.png"_spr,
                        "doorRight8.png"_spr,
                        "doorRight7.png"_spr,
                        "doorRight6.png"_spr,
                        "doorRight5.png"_spr,
                        "doorRight4.png"_spr,
                        "doorRight3.png"_spr,
                        "doorRight2.png"_spr,
                        "doorRight1.png"_spr
                        });
                        usageAmount--;
                    }
                }
                else {
                    if (doorRightClosed){
                        doorRightClosed = false;
                        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                        PlayAnimationOnSprite(doorRight, 0.03f, 11, new std::string[]{
                        "doorRight11.png"_spr,
                        "doorRight10.png"_spr,
                        "doorRight9.png"_spr,
                        "doorRight8.png"_spr,
                        "doorRight7.png"_spr,
                        "doorRight6.png"_spr,
                        "doorRight5.png"_spr,
                        "doorRight4.png"_spr,
                        "doorRight3.png"_spr,
                        "doorRight2.png"_spr,
                        "doorRight1.png"_spr
                        });
                        usageAmount--;
                    }
                    else{
                        FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    }
                }
            }
            else if (keyCode == enumKeyCodes::KEY_F){
                if (!blockDoorUsage){
                    doorBottomRightClosed = !doorBottomRightClosed;

                    FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                    if (doorBottomRightClosed){
                        PlayAnimationOnSprite(doorBottomRight, 0.03f, 6, new std::string[]{
                        "doorBottomRight1.png"_spr,
                        "doorBottomRight2.png"_spr,
                        "doorBottomRight3.png"_spr,
                        "doorBottomRight4.png"_spr,
                        "doorBottomRight5.png"_spr,
                        "doorBottomRight6.png"_spr
                        });
                        usageAmount++;
                    }
                    else {
                        PlayAnimationOnSprite(doorBottomRight, 0.03f, 6, new std::string[]{
                        "doorBottomRight6.png"_spr,
                        "doorBottomRight5.png"_spr,
                        "doorBottomRight4.png"_spr,
                        "doorBottomRight3.png"_spr,
                        "doorBottomRight2.png"_spr,
                        "doorBottomRight1.png"_spr
                        });
                        usageAmount--;
                    }
                }
                else {
                    if (doorBottomRightClosed){
                        doorBottomRightClosed = false;
                        FMODAudioEngine::sharedEngine()->playEffect("doorFX.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                        PlayAnimationOnSprite(doorBottomRight, 0.03f, 6, new std::string[]{
                        "doorBottomRight6.png"_spr,
                        "doorBottomRight5.png"_spr,
                        "doorBottomRight4.png"_spr,
                        "doorBottomRight3.png"_spr,
                        "doorBottomRight2.png"_spr,
                        "doorBottomRight1.png"_spr
                        });
                        usageAmount--;
                    }
                    else{
                        FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    }
                }
            }
            else if (keyCode == enumKeyCodes::KEY_Z){
                if (!FlashlightOn){
                    if (canUseFlashlight){
                        FlashlightOn = true;
                        Flashlight->setVisible(true);
                        usageAmount++;
                        FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    }
                    else {
                        FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    }
                }
            }
            else if (keyCode == enumKeyCodes::KEY_One){
                setSpacialMode(SpacialMode::PowerGenerator);
            }
            else if (keyCode == enumKeyCodes::KEY_Two){
                setSpacialMode(SpacialMode::SilentVentelation);
            }
            else if (keyCode == enumKeyCodes::KEY_Three){
                setSpacialMode(SpacialMode::Heater);
            }
            else if (keyCode == enumKeyCodes::KEY_Four){
                setSpacialMode(SpacialMode::PowerAC);
            }
            else if (keyCode == enumKeyCodes::KEY_Five){
                setSpacialMode(SpacialMode::GMB);
            }
            else if (keyCode == enumKeyCodes::KEY_Six){
                setSpacialMode(SpacialMode::Off);
            }
            else if (keyCode == enumKeyCodes::KEY_X){
                setSpacialMode(SpacialMode::Off);
            }
            else if (keyCode == enumKeyCodes::KEY_S && !InMask && Power > 0){
                if (!camsDisabled){
                    if (!InCams){
                        InCams = true;
                        FMODAudioEngine::sharedEngine()->playEffect("camera.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                        PlayAnimationOnSpriteWithCallBack(Cams, 0.02f, 12, new std::string[]{
                            "monitor1.png"_spr,
                            "monitor2.png"_spr,
                            "monitor3.png"_spr,
                            "monitor4.png"_spr,
                            "monitor5.png"_spr,
                            "monitor6.png"_spr,
                            "monitor7.png"_spr,
                            "monitor8.png"_spr,
                            "monitor9.png"_spr,
                            "monitor10.png"_spr,
                            "monitor11.png"_spr,
                            "monitor12.png"_spr
                        },
                        callfunc_selector(CNGameLayer::onCamsOpened));
                    }
                    else if (LookingAtCams) {
                        InCams = false;
                        PlayAnimationOnSprite(Cams, 0, 2, new std::string[]{
                            "monitor12.png"_spr,
                            "monitor12.png"_spr
                        });

                        if (currSpacialMode != SpacialMode::GMB && musicBoxAudio != nullptr){
                            musicBoxAudio->RemoveMeAndCleanUpSound();
                            musicBoxAudio = nullptr;
                        }

                        LookingAtCams = false;
                        MaskButton->setVisible(true);
                        usageAmount--;
                        cameraView->setPosition({0, 999});
                        CamsButton->setOpacity(255);
                        cameraUI->setPosition({0, 999});
                        cameraOverallUI->setPosition({0, 999});
                        ventUI->setPosition({0, 999});
                        ductUI->setPosition({0, 999});
                        FMODAudioEngine::sharedEngine()->playEffect("putdown.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

                        PlayAnimationOnSprite(Cams, 0.02f, 12, new std::string[]{
                            "monitor12.png"_spr,
                            "monitor11.png"_spr,
                            "monitor10.png"_spr,
                            "monitor9.png"_spr,
                            "monitor8.png"_spr,
                            "monitor7.png"_spr,
                            "monitor6.png"_spr,
                            "monitor5.png"_spr,
                            "monitor4.png"_spr,
                            "monitor3.png"_spr,
                            "monitor2.png"_spr,
                            "monitor1.png"_spr
                        });
                    }
                }
                else {
                    FMODAudioEngine::sharedEngine()->playEffect("error.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                }
            }
            else if (keyCode == enumKeyCodes::KEY_Y){
                fanSound = AudioSource::create("fan.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                this->addChild(fanSound);

                int songSelected = rand() % 6;

                bool noMusic = false;

                Ambiance = AudioSource::create("ambiance2.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                this->addChild(Ambiance);

                switch (songSelected)
                {
                case 0:
                    bgMusic = AudioSource::create("Hybernating Evil.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    break;

                case 1:
                    bgMusic = AudioSource::create("Last Breath.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    break;

                case 2:
                    bgMusic = AudioSource::create("Sleep No Morev2.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    break;

                case 3:
                    bgMusic = AudioSource::create("Sonata for the Fallen.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    break;

                case 4:
                    bgMusic = AudioSource::create("Where Dreams Die.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                    break;

                case 5:
                    noMusic = true;
                    break;
                
                default:
                    break;
                }
                if (!noMusic){
                    this->addChild(bgMusic);
                }
                else {
                    bgMusic = nullptr;
                }
            }
        }

        if (keyCode == enumKeyCodes::KEY_Escape){
            escaping = true;
        }
        else if (keyCode == enumKeyCodes::KEY_J){
            NightTimeOverall += 60;
            NightTime += 60;
        }
        else if (keyCode == enumKeyCodes::KEY_C){
            clickingC = true;
        }
        else if (keyCode == enumKeyCodes::KEY_Enter){
            enterClicked = true;
        }
    }
    if (keyCode == enumKeyCodes::KEY_Up){
        clickingUpArrow = true;
    }
    else if (keyCode == enumKeyCodes::KEY_Down){
        clickingDownArrow = true;
    }
    else if (keyCode == enumKeyCodes::KEY_Left){
        clickingLeftArrow = true;
    }
    else if (keyCode == enumKeyCodes::KEY_Right){
        clickingRightArrow = true;
    }
}

const char* const CNGameLayer::BoolToString(bool b)
{
    return b ? "true" : "false";
}

void CNGameLayer::keyUp(enumKeyCodes keyCode){
    if (NIGHTSTARTED){
        if (Power > 0){
            if (keyCode == enumKeyCodes::KEY_Z){
                if (FlashlightOn){
                    FlashlightOn = false;
                    Flashlight->setVisible(false);
                    usageAmount--;
                    FMODAudioEngine::sharedEngine()->playEffect("click2.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                }
                
            }
        }
        if (keyCode == enumKeyCodes::KEY_Escape){
            escaping = false;
            escapeTimer = 0.5f;
        }
        else if (keyCode == enumKeyCodes::KEY_C){
            clickingC = false;
        }
        else if (keyCode == enumKeyCodes::KEY_Enter){
            enterClicked = false;
        }
    }
    if (keyCode == enumKeyCodes::KEY_Up){
        clickingUpArrow = false;
    }
    else if (keyCode == enumKeyCodes::KEY_Down){
        clickingDownArrow = false;
    }
    else if (keyCode == enumKeyCodes::KEY_Left){
        clickingLeftArrow = false;
    }
    else if (keyCode == enumKeyCodes::KEY_Right){
        clickingRightArrow = false;
    }
}

void CNGameLayer::setSpacialMode(SpacialMode mode){
    SpacialMode prefiMode = currSpacialMode;
    currSpacialMode = mode;
    FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

    if (prefiMode == mode && mode != SpacialMode::Off){
        setSpacialMode(SpacialMode::Off);
    }
    else {
        //remove previ mode
        switch (prefiMode)
        {
        case SpacialMode::PowerGenerator:
            noiseAmount -= 2;
            break;
        case SpacialMode::SilentVentelation:
            usageAmount -= 1;
            break;
        case SpacialMode::Heater:
            noiseAmount -= 1;
            usageAmount -= 1;
            heatMultiplier -= 5;
            break;
        case SpacialMode::PowerAC:
            noiseAmount -= 1;
            usageAmount -= 1;
            CoolMultiplier -= 1;
            break;
        case SpacialMode::GMB:
            if (!LookingAtCams){
                if (musicBoxAudio != nullptr){
                    musicBoxAudio->RemoveMeAndCleanUpSound();
                    musicBoxAudio = nullptr;
                }
            }
            else {
                if (currentCamSelected != Cameras::Camera04){
                    musicBoxAudio->Paused(true);
                }
            }
            usageAmount -= 1;
            break;

        default:
            break;
        }
        //add the current selected mode
        switch (mode)
        {
        case SpacialMode::PowerGenerator:
            noiseAmount += 2;
            spacialUsed->setPosition({(powerGenButton->getPositionX() - 28), powerGenButton->getPositionY()});
            break;
        case SpacialMode::SilentVentelation:
            usageAmount += 1;
            spacialUsed->setPosition({(silVentButton->getPositionX() - 28), silVentButton->getPositionY()});
            break;
        case SpacialMode::Heater:
            noiseAmount += 1;
            usageAmount += 1;
            heatMultiplier += 5;
            spacialUsed->setPosition({(heaterButton->getPositionX() - 28), heaterButton->getPositionY()});
            break;
        case SpacialMode::PowerAC:
            noiseAmount += 1;
            usageAmount += 1;
            CoolMultiplier += 1;
            spacialUsed->setPosition({(powerACButton->getPositionX() - 28), powerACButton->getPositionY()});
            break;
        case SpacialMode::GMB:
            usageAmount += 1;
            spacialUsed->setPosition({(GMBButton->getPositionX() - 28), GMBButton->getPositionY()});

            if (!LookingAtCams){
                musicBoxAudio = AudioSource::create(currMusicString, FMOD_LOOP_NORMAL, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
                this->addChild(musicBoxAudio);
            }
            else {
                if (currentCamSelected != Cameras::Camera04){
                    musicBoxAudio->Paused(false);
                }
            }
            break;
        case SpacialMode::Off:
            spacialUsed->setPosition({(spacialsOffButton->getPositionX() - 28), spacialsOffButton->getPositionY()});
            break;
        }
    }
}

void CNGameLayer::SwitchCamera(Cameras camera){
    CamStaticOpacity = 255;
    currentCamSelected = camera;
    FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

    if (musicBoxAudio != nullptr && currSpacialMode != SpacialMode::GMB){
        if (currentCamSelected == Camera04){
            musicBoxAudio->Paused(false);
        }
        else{
            musicBoxAudio->Paused(true);
        }
    }
    if (currentCamSelected == Cameras::Camera06){
        closeCurtainsB->setVisible(true);
    }
    else{
        closeCurtainsB->setVisible(false);
    }

    switch (currentCamSelected){
    case Cameras::Camera01:
        Cam01->setPosition({0, 0});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(true);
        Cam01ButtonOff->setVisible(false);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera01;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam01->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }

        break;
    
    case Cameras::Camera02:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 0});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(true);
        Cam02ButtonOff->setVisible(false);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera02;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam02->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;

    case Cameras::Camera03:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 0});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(true);
        Cam03ButtonOff->setVisible(false);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera03;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam03->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;

    case Cameras::Camera04:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 0});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(true);
        Cam04ButtonOff->setVisible(false);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(true);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera04;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam04->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;

    case Cameras::Camera05:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 0});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(true);
        Cam05ButtonOff->setVisible(false);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera05;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam05->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;

    case Cameras::Camera06:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 0});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(true);
        Cam06ButtonOff->setVisible(false);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera06;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam06->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;

    case Cameras::Camera07:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 0});
        Cam08->setPosition({0, 999});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(true);
        Cam07ButtonOff->setVisible(false);
        Cam08ButtonOn->setVisible(false);
        Cam08ButtonOff->setVisible(true);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera07;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam07->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;

    case Cameras::Camera08:
        Cam01->setPosition({0, 999});
        Cam02->setPosition({0, 999});
        Cam03->setPosition({0, 999});
        Cam04->setPosition({0, 999});
        Cam05->setPosition({0, 999});
        Cam06->setPosition({0, 999});
        Cam07->setPosition({0, 999});
        Cam08->setPosition({0, 0});
        Cam01ButtonOn->setVisible(false);
        Cam01ButtonOff->setVisible(true);
        Cam02ButtonOn->setVisible(false);
        Cam02ButtonOff->setVisible(true);
        Cam03ButtonOn->setVisible(false);
        Cam03ButtonOff->setVisible(true);
        Cam04ButtonOn->setVisible(false);
        Cam04ButtonOff->setVisible(true);
        Cam05ButtonOn->setVisible(false);
        Cam05ButtonOff->setVisible(true);
        Cam06ButtonOn->setVisible(false);
        Cam06ButtonOff->setVisible(true);
        Cam07ButtonOn->setVisible(false);
        Cam07ButtonOff->setVisible(true);
        Cam08ButtonOn->setVisible(true);
        Cam08ButtonOff->setVisible(false);
        AONLY->setVisible(false);
        for (size_t i = 0; i < CamCoins.size(); i++)
        {
            if (CamCoins[i]->sprite != nullptr){
                CamCoins[i]->sprite->removeMeAndCleanup();
            }
        }

        CamCoins.clear();
        camCoinAmount = rand() % 3;
        
        for (int i = 0; i < camCoinAmount; i++)
        {
            camFazCoins* coi = new camFazCoins();
            coi->inCamera = Camera08;
            coi->sprite = CCSprite::create("fazCoin.png"_spr);
            coi->sprite->setPosition({randomFloat(-338, 338), randomFloat(-138, 138)});
            coi->sprite->setOpacity(200);
            Cam08->addChild(coi->sprite);
            CamCoins.insert(CamCoins.begin(),coi);
        }
        break;
    
    default:
        break;
    }
}

CNGameLayer::ventPosition CNGameLayer::resetVentPos(){
    ventPosition tempPos;
    tempPos.progressAmount = 0;
    int randomside = rand() % 3;
    switch (randomside)
    {
    case 0:
        tempPos.ventSide = ventPosition::ventsides::left;
        break;

    case 1:
        tempPos.ventSide = ventPosition::ventsides::up;
        break;

    case 2:
        tempPos.ventSide = ventPosition::ventsides::right;
        break;
    }
    
    return tempPos;
}

CCPoint CNGameLayer::getVentPointFromPosition(ventPosition position){
    
    CCPoint point = {-245, 59};

    bool reachedLastLine = false;

    float LastLineDictance = 0;

    //if passed first intersection
    if (-245 + position.progressAmount >= -161){
        if (position.ventSide == ventPosition::ventsides::left)
        {    
            //if in end of line 1
            if (-245 + position.progressAmount >= -135){
                float fixedLength = position.progressAmount - 110;

                if (59 - fixedLength <= -38){
                    float fixedLength2 = position.progressAmount - 110 - 97;

                    if (-135 + fixedLength2 >= -79){
                        reachedLastLine = true;
                        LastLineDictance = position.progressAmount - 110 - 97 - 56;
                    }
                    else {
                        point.y = 59 - (fixedLength - fixedLength2);
                        point.x = -245 + (position.progressAmount - fixedLength + fixedLength2);
                    }
                }
                else{
                    point.y = 59 - fixedLength;
                    point.x = -245 + (position.progressAmount - fixedLength);
                }
            }
            //if isnt in the end of line 1
            else {
                point.x = -245 + position.progressAmount;
            }
        }
        else if (position.ventSide == ventPosition::ventsides::up)
        {
            //upsijngkljsngblkjsdfngkljsdfnglkfsdngfngds
            float fixedLength = position.progressAmount - 84;
            if (59 + fixedLength >= 113){
                float fixedLength1 = position.progressAmount - 84 - 54;
                if (-161 + fixedLength1 >= -19){
                    float fixedLength2 = position.progressAmount - 84 - 54 - 142;
                    if (113 - fixedLength2 <= 52){
                        float fixedLength3 = position.progressAmount - 84 - 54 - 142 - 61;
                        if (-19 - fixedLength3 <= -79){
                            float fixedLength4 = position.progressAmount - 84 - 54 - 142 - 61 - 60;
                            if (52 - fixedLength4 <= -38){
                                reachedLastLine = true;
                                LastLineDictance = position.progressAmount - 84 - 54 - 142 - 61 - 60 - 90;
                            }
                            else{
                                point.x = -79;
                                point.y = 52 - fixedLength4;
                            }
                        }
                        else{
                            point.x = -19 - fixedLength3;
                            point.y = 52;
                        }
                    }
                    else{
                        point.x = -19;
                        point.y = 113 - fixedLength2;
                    }
                }
                else{
                    point.x = -161 + fixedLength1;
                    point.y = 113;
                }
            }
            else{
                point.x = -161;
                point.y = 59 + fixedLength;
            }
        }
        else if (position.ventSide == ventPosition::ventsides::right)
        {
            //upsijngkljsngblkjsdfngkljsdfnglkfsdngfngds
            float fixedLength = position.progressAmount - 84;
            if (59 + fixedLength >= 113){
                float fixedLength1 = position.progressAmount - 84 - 54;
                if (-161 + fixedLength1 >= -19){
                    float fixedLength2 = position.progressAmount - 84 - 54 - 142;
                    if (-19 + fixedLength2 >= 37){
                        float fixedLength3 = position.progressAmount - 84 - 54 - 142 - 56;
                        if (113 - fixedLength3 <= -38){
                            float fixedLength4 = position.progressAmount - 84 - 54 - 142 - 56 - 151;
                            if (37 - fixedLength4 <= -79){
                                reachedLastLine = true;
                                LastLineDictance = position.progressAmount - 84 - 54 - 142 - 56 - 151 - 116;
                            }
                            else{
                                point.x = 37 - fixedLength4;
                                point.y = -38;
                            }
                        }
                        else{
                            point.x = 37;
                            point.y = 113 - fixedLength3;
                        }
                    }
                    else{
                        point.x = -19 + fixedLength2;
                        point.y = 113;
                    }
                }
                else{
                    point.x = -161 + fixedLength1;
                    point.y = 113;
                }
            }
            else{
                point.x = -161;
                point.y = 59 + fixedLength;
            }
        }
    }
    //if is still didnt reach first intersection
    else{
        point.x = -245 + position.progressAmount;
    }

    if (reachedLastLine){
        if (-38 - LastLineDictance <= -75){
            point.y = -75;
            point.x = -79;
        }
        else{
            point.y = -38 - LastLineDictance;
            point.x = -79;
        }
    }
    
    /*
    first line: -245, 59 to -161, 59

    //

    Left path: -161, 59 to -135, 59
               -135, 59 to -135, -38
               -135, -38 to -79, -38

    //

    up and right paths: -161, 59 to -161, 113
                        -161, 113 to -19, 113

    //

    up path: -19, 113 to -19, 52
             -19, 52 to -79, 52
             -79, 52 to -79, -38

    //

    right path: -19, 113 to 37, 113
                37, 113 to 37, -38
                37, -38 to -79, -38

    //

    last line: -79, -38 to -79, -75

    */
    return point;
}

bool CNGameLayer::isTouchingVentSnare(ventPosition position){

    if (position.ventSide == ventPosition::ventsides::left){
        if (position.progressAmount >= 228 && position.progressAmount <= 243 && snareLocation == ventSnareLocation::left){
            return true;
        }
    }
    else if (position.ventSide == ventPosition::ventsides::up){
        if (position.progressAmount >= 455 && position.progressAmount <= 470 && snareLocation == ventSnareLocation::up){
            return true;
        }
    }
    else if (position.ventSide == ventPosition::ventsides::right){
        if (position.progressAmount >= 570 && position.progressAmount <= 585 && snareLocation == ventSnareLocation::right){
            return true;
        }
    }
    return false;
}

bool CNGameLayer::hasReachedEndOfVent(ventPosition position){

    if (position.ventSide == ventPosition::ventsides::left){
        if (position.progressAmount >= 300){
            return true;
        }
    }
    else if (position.ventSide == ventPosition::ventsides::up){
        if (position.progressAmount >= 528){
            return true;
        }
    }
    else if (position.ventSide == ventPosition::ventsides::right){
        if (position.progressAmount >= 640){
            return true;
        }
    }
    return false;
}

void CNGameLayer::deathscreenUpdate(float delta){
    if (DeathDelay > 0){
        DeathDelay -= delta;
    }
    else {
        MainCont->setRotation(0);
        redScreen->setVisible(true);
        if (blackScreenFade < 255){
            blackScreenFade += delta * 1200;

            if (blackScreenFade >= 255){
                blackScreenFade = 255;
            }
        }
        if (blackScreenFade >= 255){
            blackScreenFade = 255;
        }

        if (redVOpactiy > 0){
            redVOpactiy -= delta * 350;

            if (redVOpactiy <= 0){
                redVOpactiy = 0;
            }
        }
        if (redVOpactiy <= 0){
            redVOpactiy = 0;
        }

        BlackScreen->setOpacity((int)blackScreenFade);
        
        if (blackScreenFade >= 160){
            redVignette->setVisible(true);
            gameOverText->setVisible(true);

            std::string nightTimeDisplay = "";

            std::stringstream nightTimeSecondsFixed;
            nightTimeSecondsFixed << std::fixed << std::setprecision(1) << NightTime;

            if (NightTime < 10){
                nightTimeDisplay = std::to_string(NightMinutes) + ":0" + nightTimeSecondsFixed.str();
            }
            if (NightTime >= 10){
                nightTimeDisplay = std::to_string(NightMinutes) + ":" + nightTimeSecondsFixed.str();
            }

            gameOverTimeText->setString(nightTimeDisplay.c_str());
            gameOverTimeText->setVisible(true);
        }
        int gameOverTextOp = 255 - redVOpactiy;
        redVignette->setOpacity((int)redVOpactiy);
        gameOverText->setOpacity((int)gameOverTextOp);
        if (gameOverTextOp < 175){
            gameOverTimeText->setOpacity((int)gameOverTextOp);
        }
        else {
            gameOverTimeText->setOpacity(175);
        }
        if (redVignette->getOpacity() <= 0 && getTouchOn(redVignette)){
            escaped = true;
            if (jumpscaresound != nullptr){
                jumpscaresound->RemoveMeAndCleanUpSound();
            }

            CCDirector::sharedDirector()->popSceneWithTransition(2, PopTransition::kPopTransitionFade);
        
            if (bgMusic != nullptr){
                bgMusic->CleanUpSound();
            }
            Ambiance->CleanUpSound();
        }
    }
}

void CNGameLayer::inJumpUpdate(float delta){
    if (!deathrotationsDisabled){
        int min = -5;
        int max = 5;
        float rotationSpeed = 120;

        if (rotGoUp){
            if (officeRotation < max){
                officeRotation += delta * rotationSpeed;

                if (officeRotation >= max){
                    officeRotation = max;
                    rotGoUp = false;
                }
            }
            if (officeRotation >= max){
                officeRotation = max;
                rotGoUp = false;
            }
        }
        else {
            if (officeRotation > min){
                officeRotation -= delta * rotationSpeed;

                if (officeRotation <= min){
                    officeRotation = min;
                    rotGoUp = true;
                }
            }
            if (officeRotation <= min){
                officeRotation = min;
                rotGoUp = true;
            }
        }
        MainCont->setRotation(officeRotation);
    }
}

void CNGameLayer::EnterLayer(std::vector<animatronic*> animatronics, int office, bool frigidA, bool coinsA, bool batteryA, bool DDRepelA) {
    auto layer = CNGameLayer::create(animatronics, office, frigidA, coinsA, batteryA, DDRepelA);
    auto scene = CCScene::create();

    scene->addChild(layer);
    auto transition = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->pushScene(transition);
}

void CNGameLayer::NightCompleteUpdate(float delta){
    if (blackScreenFade < 255){
        blackScreenFade += delta * 300;
        fireworkBlastTimer = randomFloat(-1, 1);
        if (blackScreenFade >= 255){
            blackScreenFade = 255;
        }
    }
    if (blackScreenFade >= 255){
        blackScreenFade = 255;

        if (udiditOpacity < 255){
            udiditOpacity += delta * 100;

            if (udiditOpacity >= 255){
                udiditOpacity = 255;
            }
        }
        if (udiditOpacity >= 255){
            udiditOpacity = 255;
            delayForDrop -= delta;
        }
        
        udidit->setOpacity((int)udiditOpacity);
        udidit->setPosition({0, (udiditOpacity / 6.375f)});
        
    }
    BlackScreen->setOpacity((int)blackScreenFade);

    if (delayForDrop <= 0){
        //hit the drop
        highScoreTextDy->setOpacity(255);

        if (highScoreFlashTimer > 0){
            highScoreFlashTimer -= delta;
        }
        else {
            highScoreFlashTimer = 0.178f;
            if (scoreCounter != roundPointsWorth){
                if (highScoreText->getOpacity() == 255){
                    highScoreText->setOpacity(0);
                }
                else if (highScoreText->getOpacity() == 0){
                    highScoreText->setOpacity(255);
                }
            }
            else {
                highScoreText->setOpacity(255);
                if (highScoreTextDy->isVisible()){
                    highScoreTextDy->setVisible(false);
                }
                else {
                    highScoreTextDy->setVisible(true);
                }
            }
        }
        if (scoreCounter != roundPointsWorth){
            if (fireworkBlastTimer > 0){
                fireworkBlastTimer -= delta;
            }
            else {
                fireworkBlastTimer = randomFloat(-1, 1);
                fireworkBlast* blast = fireworkBlast::create(this);
                blast->setZOrder(105);
                blast->setPosition({randomFloat(-275, 275), randomFloat(-152, 152)});
                Canvas->addChild(blast);
            }
        }
        else if (getTouchOn(BlackScreen)){
            escaped = true;
            CCDirector::sharedDirector()->popSceneWithTransition(2, PopTransition::kPopTransitionFade);

            completionMusic->CleanUpSound();

            if (bgMusic != nullptr){
                bgMusic->CleanUpSound();
            }
            Ambiance->CleanUpSound();
        }

        if (countTimer > 0){
            countTimer -= delta;
        }
        else {
            countTimer = 0.045f;
            if (scoreCounter != roundPointsWorth){
                scoreCounter += 10;
                highScoreTextDy->setString(std::to_string(scoreCounter).c_str());
                if (scoreCounter == 10){
                    udidit->setVisible(false);
                    greatJob->setOpacity(255);
                }
                if (scoreCounter == 2000){
                    greatJob->setVisible(false);
                    fantastic->setOpacity(255);
                }
                if (scoreCounter == 4000){
                    fantastic->setVisible(false);
                    amazing->setOpacity(255);
                }
                if (scoreCounter == 6000){
                    amazing->setVisible(false);
                    stupendous->setOpacity(255);
                }
                if (scoreCounter == 8000){
                    stupendous->setVisible(false);
                    perfect->setOpacity(255);
                }
                if (scoreCounter == 10000){
                    perfect->setVisible(false);
                    unbeatable->setOpacity(255);
                }
            }
        }
    }
}

bool CNGameLayer::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void CNGameLayer::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void CNGameLayer::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void CNGameLayer::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

CCSprite* CNGameLayer::CreateAnimatedSprite(float speed, int amoutOfFrames, std::string frames[]){
    CCSprite* spr = CCSprite::create(frames[0].c_str());

    CCRect sprRect = spr->getTextureRect();

    CCArray* sprframes = CCArray::create();

    for (int i = 0; i < amoutOfFrames; i++)
    {
        sprframes->addObject(CCSpriteFrame::create(frames[i].c_str(), sprRect));
    }
     
    CCAnimation* sprAnimation = CCAnimation::createWithSpriteFrames(sprframes, speed);

    CCAction* sprAction = CCRepeatForever::create(CCAnimate::create(sprAnimation));

    spr->runAction(sprAction);

    return spr;
}

void CNGameLayer::PlayAnimationOnSprite(CCSprite* sprite, float speed, int amoutOfFrames, std::string frames[]){
    CCRect sprRect = sprite->getTextureRect();

    CCArray* sprframes = CCArray::create();

    for (int i = 0; i < amoutOfFrames; i++)
    {
        sprframes->addObject(CCSpriteFrame::create(frames[i].c_str(), sprRect));
    }
     
    CCAnimation* sprAnimation = CCAnimation::createWithSpriteFrames(sprframes, speed);

    CCAction* sprAction = CCRepeat::create(CCAnimate::create(sprAnimation), 1);

    sprite->runAction(sprAction);
}

CCRepeat* CNGameLayer::CreateAnimAction(float speed, int amoutOfFrames, std::string frames[], int repeats){
    CCSprite* spr = CCSprite::create(frames[0].c_str());

    CCRect sprRect = spr->getTextureRect();

    CCArray* sprframes = CCArray::create();

    for (int i = 0; i < amoutOfFrames; i++)
    {
        sprframes->addObject(CCSpriteFrame::create(frames[i].c_str(), sprRect));
    }
     
    CCAnimation* sprAnimation = CCAnimation::createWithSpriteFrames(sprframes, speed);

    return CCRepeat::create(CCAnimate::create(sprAnimation), repeats);
}

bool CNGameLayer::getHover(CCNode* node){
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

bool CNGameLayer::getHoveronPoint(CCNode* node, CCPoint pointInWorldSpace){
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

    CCRect* rect = new CCRect(pos.x, pos.y, contentSize.width * multiplyX, contentSize.height * multiplyY);

    //check
    if (rect->containsPoint(pointInWorldSpace)){
        return true;
    }

    return false;
}

bool CNGameLayer::getHoverOnOther(CCNode* node, CCNode* otherNode){
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

    CCRect* rect = new CCRect(pos.x, pos.y, contentSize.width * multiplyX, contentSize.height * multiplyY);

    //otehr
    auto contentSizeOther = otherNode->getContentSize();

    bool HasreachedEndOfParentCheckOther = false;

    CCNode* LastParentOther = otherNode->getParent();

    CCNode* SceneOther = nullptr;

    float multiplyXOther = otherNode->getScaleX();

    float multiplyYOther = otherNode->getScaleY();

    while(!HasreachedEndOfParentCheckOther){

        if (LastParentOther != nullptr){
            multiplyXOther = multiplyXOther * LastParentOther->getScaleX();
            multiplyYOther = multiplyYOther * LastParentOther->getScaleY();

            SceneOther = LastParentOther;
            LastParentOther = LastParentOther->getParent();
        }
        else {
            HasreachedEndOfParentCheckOther = true;
        }
    }

    //pos
    auto posOther = otherNode->convertToWorldSpace({0,0});

    CCRect* rectOther = new CCRect(posOther.x, posOther.y, contentSizeOther.width * multiplyXOther, contentSizeOther.height * multiplyYOther);

    //check
    if (rect->intersectsRect(*rectOther)){
        return true;
    }

    return false;
}

bool CNGameLayer::getHoverSprite(CCSprite* s, CCRenderTexture* renderTexture){
    auto pixpos = CC_POINT_POINTS_TO_PIXELS(getMousePos());
    auto oldPosition = s->getPosition();
    auto pixel = new GLubyte[4];

    s->setPosition(s->getParent()->convertToWorldSpace(s->getPosition()));

    renderTexture->beginWithClear(255,255,255,0);
    s->visit();

    glReadPixels(pixpos.x, pixpos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

    renderTexture->end();

    s->setPosition(oldPosition);
    if (pixel[3] != 0){
        return true;
    }
    return false;
}

GLubyte* CNGameLayer::getSpritePixelFromMouse(CCSprite* s, CCRenderTexture* renderTexture){

    if (getHover(s)){
        auto mousePos = CC_POINT_POINTS_TO_PIXELS(getMousePos());
        auto oldPosition = s->getPosition();
        auto pixel = new GLubyte[4];

        s->setPosition(s->getParent()->convertToWorldSpace(s->getPosition()));

        renderTexture->beginWithClear(255,255,255,0);
        s->visit();

        glReadPixels(mousePos.x, mousePos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

        renderTexture->end();

        s->setPosition(oldPosition);
        return (GLubyte*)pixel;
    }
    else {
        auto pixel = new GLubyte[4]{
            0,0,0,0
        };

        return (GLubyte*)pixel;
    }
    

    
}

bool CNGameLayer::getTouchOn(CCNode* node, CCTouch* touch){
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

bool CNGameLayer::getTouchOn(CCNode* node){
    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}

bool CNGameLayer::getTouchOnSprite(CCSprite* s, CCRenderTexture* renderTexture){
    if (clicking && !oneTimeClick){
        if (getHoverSprite(s, renderTexture)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}

bool CNGameLayer::getTouchOnDouble(CCNode* node){
    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;

            if (doubleClickTimer <= 0){
                doubleClickTimer = 0.2f;
            }
            else {
                return true;
            }  
        }
    }
    return false;
}

void CNGameLayer::PlayAnimationOnSpriteWithCallBack(CCSprite* sprite, float speed, int amoutOfFrames, std::string frames[], SEL_CallFunc callback){
    CCRect sprRect = sprite->getTextureRect();

    CCArray* sprframes = CCArray::create();

    for (int i = 0; i < amoutOfFrames; i++)
    {
        sprframes->addObject(CCSpriteFrame::create(frames[i].c_str(), sprRect));
    }
     
    CCAnimation* sprAnimation = CCAnimation::createWithSpriteFrames(sprframes, speed);

    CCAction* sprAction = CCSequence::create(CCRepeat::create(CCAnimate::create(sprAnimation), 1),CCCallFunc::create(this, callback), nullptr);

    sprAction->setTag(29847);

    sprite->runAction(sprAction);
}

bool CNGameLayer::getHoldOn(CCNode* n){
    if (clicking){
        if (getHover(n)){
            return true;
        }
    }
    return false;
}

void CNGameLayer::changeMusic(){
    FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));

    switch (currMusic)
    {
    case musics::music1:
        currMusic = musics::music2;
        currMusicString = "musicbox2.mp3"_spr;
        break;

    case musics::music2:
        currMusic = musics::music3;
        currMusicString = "musicbox3.mp3"_spr;
        break;

    case musics::music3:
        currMusic = musics::music4;
        currMusicString = "musicbox4.mp3"_spr;
        break;

    case musics::music4:
        currMusic = musics::music1;
        currMusicString = "musicbox.mp3"_spr;
        break;
    }

    if (musicBoxAudio != nullptr){
        musicBoxAudio->changeSound(currMusicString, FMOD_LOOP_NORMAL);
    }
}

CCSprite* CNGameLayer::Jumpscare(CCRepeat* animation, std::string jumpSoundEffect, bool noneLethal, bool dontRemoveMask, bool dontRemoveCams, float scaling, float jumpOpacity, SEL_CallFunc callback, CCObject* CallbackTarget, bool addToCanvas, bool disableShake){
    if (!inJumpscare){
        if (!dontRemoveCams)
        if (InCams){
            InCams = false;
            if (LookingAtCams){
                LookingAtCams = false;
                usageAmount--;
            }
            PlayAnimationOnSprite(Cams, 0, 2, new std::string[]{
                "monitor12.png"_spr,
                "monitor12.png"_spr
            });
            MaskButton->setVisible(true);
            cameraView->setPosition({0, 999});
            CamsButton->setOpacity(255);
            cameraUI->setPosition({0, 999});
            cameraOverallUI->setPosition({0, 999});
            ventUI->setPosition({0, 999});
            ductUI->setPosition({0, 999});
            CamStatic->setVisible(false);
            PlayAnimationOnSprite(Cams, 0.02f, 12, new std::string[]{
                "monitor12.png"_spr,
                "monitor11.png"_spr,
                "monitor10.png"_spr,
                "monitor9.png"_spr,
                "monitor8.png"_spr,
                "monitor7.png"_spr,
                "monitor6.png"_spr,
                "monitor5.png"_spr,
                "monitor4.png"_spr,
                "monitor3.png"_spr,
                "monitor2.png"_spr,
                "monitor1.png"_spr
            });
        }
        if (!dontRemoveMask)
        if (InMask){
            InMask = false;
            CamsButton->setVisible(true);
            PlayAnimationOnSprite(Mask, 0.02f, 9, new std::string[]{
                "mask9.png"_spr,
                "mask8.png"_spr,
                "mask7.png"_spr,
                "mask6.png"_spr,
                "mask5.png"_spr,
                "mask4.png"_spr,
                "mask3.png"_spr,
                "mask2.png"_spr,
                "mask1.png"_spr
            });
        }
        
        CCAction* sprAction;
        if (!noneLethal){
            deathrotationsDisabled = disableShake;
            inJumpscare = true;
            Flashlight->setVisible(false);
            if (callback != NULL){
                sprAction = CCSequence::create(animation, CCCallFunc::create(this, callfunc_selector(CNGameLayer::jumpscareEnded)), CCCallFunc::create(CallbackTarget, callback), nullptr);
            }
            else {
                sprAction = CCSequence::create(animation, CCCallFunc::create(this, callfunc_selector(CNGameLayer::jumpscareEnded)), nullptr);
            }
            if (bgMusic != nullptr){
                bgMusic->CleanUpSound();
            }
            Ambiance->CleanUpSound();
            if (musicBoxAudio != nullptr){
                musicBoxAudio->RemoveMeAndCleanUpSound();
                musicBoxAudio = nullptr;
            }
            fanSound->CleanUpSound();
            NIGHTSTARTED = false;
            for (size_t i = 0; i < jumpscares.size(); i++)
                {
                    if (!jumpscares[i]->getActionByTag(73642)->isDone()){
                        PlayAnimationOnSprite(jumpscares[i], 0.001f, 2, new std::string[]{
                            "bigwEmpty.png"_spr,
                            "bigwEmpty.png"_spr
                        });
                        jumpscares[i]->removeMeAndCleanup();
                        jumpscares.erase(std::next(jumpscares.begin(), i));
                    }
                }
            sprAction->setTag(73641);
            
        }
        else {
            if (callback != NULL){
                sprAction = CCSequence::create(animation, CCCallFunc::create(this, callfunc_selector(CNGameLayer::jumpscareEndedNonLethal)), CCCallFunc::create(CallbackTarget, callback), nullptr);
            }
            else {
                sprAction = CCSequence::create(animation, CCCallFunc::create(this, callfunc_selector(CNGameLayer::jumpscareEndedNonLethal)), nullptr);
            }
            sprAction->setTag(73642);
        }

        

        jumpEmpty = CCSprite::create("bigwEmpty.png"_spr);
        if (addToCanvas){
            jumpEmpty->setZOrder(55);
        }
        jumpEmpty->setOpacity(jumpOpacity);
        jumpEmpty->setScale(scaling);

        jumpscares.insert(jumpscares.begin(), jumpEmpty);

        if (addToCanvas){
            Canvas->addChild(jumpEmpty);
        }

        jumpEmpty->runAction(sprAction);
        if (jumpSoundEffect != ""){
            jumpscaresound = AudioSource::create(jumpSoundEffect, FMOD_DEFAULT, AudioSource::Custom, false, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
            this->addChild(jumpscaresound);
        }

        return jumpEmpty;
    }
    CCSprite* jumpEmptyre = CCSprite::create("bigwEmpty.png"_spr);
    this->addChild(jumpEmptyre);
    return jumpEmptyre;
}

void CNGameLayer::jumpscareEnded(){
    inJumpscare = false;
    DEATHSCREEN = true;
}

void CNGameLayer::jumpscareEndedNonLethal(){
    if (NIGHTSTARTED){
        for (size_t i = 0; i < jumpscares.size(); i++)
        {
            if (jumpscares[i]->getActionByTag(73642)->isDone()){
                PlayAnimationOnSprite(jumpscares[i], 0.001f, 2, new std::string[]{
                    "bigwEmpty.png"_spr,
                    "bigwEmpty.png"_spr
                });
                jumpscares[i]->removeMeAndCleanup();
                jumpscares.erase(std::next(jumpscares.begin(), i));
            }
        }
    }
}

void CNGameLayer::FlashEffects(float time, SEL_CallFunc callbackWhenDone, CCObject* caller){
    flashForTime += time;
    if (callbackWhenDone != NULL && caller != NULL){
        auto callbackWDelay = CCSequence::create(CCDelayTime::create(time), CCCallFunc::create(caller, callbackWhenDone), nullptr);
        effectBlackscreen->runAction(callbackWDelay);
    }
}

void CNGameLayer::removeFromFlashEffects(float time){
    flashForTime -= time;
}

void CNGameLayer::CharacterBlock(){
    FMODAudioEngine::sharedEngine()->playEffect("block.mp3"_spr,1.0f,1.0f, Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    fazCoins++;
}

CCPoint CNGameLayer::getLocationFromDuctPos(ductLocations position){
    switch (position){
        //entrenceleft1
        case ductLocations::entrenceLeft1:
            return topleftContactPoint1->getPosition();
        break;

        //entrenceleft2
        case ductLocations::entrenceLeft2:
            return topleftContactPoint2->getPosition();
        break;

        //entrenceright1
        case ductLocations::entrenceRight1:
            return toprightContactPoint1->getPosition();
        break;

        //entrenceright2
        case ductLocations::entrenceRight2:
            return toprightContactPoint2->getPosition();
        break;

        case ductLocations::topLine1:
            return toplineContactPoint1->getPosition();
        break;

        case ductLocations::topLine2:
            return toplineContactPoint2->getPosition();
        break;

        case ductLocations::topLine3:
            return toplineContactPoint3->getPosition();
        break;

        case ductLocations::topLine4:
            return toplineContactPoint4->getPosition();
        break;

        case ductLocations::topLine5:
            return toplineContactPoint5->getPosition();
        break;

        case ductLocations::topLine6:
            return toplineContactPoint6->getPosition();
        break;

        case ductLocations::topLine7:
            return toplineContactPoint7->getPosition();
        break;

        case ductLocations::topRightTurn_:
            return topRightTurn->getPosition();
        break;

        case ductLocations::topLeftTurn_:
            return topLeftTurn->getPosition();
        break;

        case ductLocations::rightLine1:
            return rightLineContactPoint1->getPosition();
        break;

        case ductLocations::rightLine2:
            return rightLineContactPoint2->getPosition();
        break;

        case ductLocations::rightLine3:
            return rightLineContactPoint3->getPosition();
        break;

        case ductLocations::rightLine4:
            return rightLineContactPoint4->getPosition();
        break;

        case ductLocations::leftLine1:
            return leftLineContactPoint1->getPosition();
        break;

        case ductLocations::leftLine2:
            return leftLineContactPoint2->getPosition();
        break;

        case ductLocations::leftLine3:
            return leftLineContactPoint3->getPosition();
        break;

        case ductLocations::leftLine4:
            return leftLineContactPoint4->getPosition();
        break;

        case ductLocations::bottomRightTurn_:
            return bottomRightTurn->getPosition();
        break;

        case ductLocations::bottomLeftTurn_:
            return bottomLeftTurn->getPosition();
        break;

        case ductLocations::middleLine1:
            return middleLineContactPoint1->getPosition();
        break;

        case ductLocations::middleLine2:
            return middleLineContactPoint2->getPosition();
        break;

        case ductLocations::middleLine3:
            return middleLineContactPoint3->getPosition();
        break;

        case ductLocations::middleLine4:
            return middleLineContactPoint4->getPosition();
        break;

        case ductLocations::middleLine5:
            return middleLineContactPoint5->getPosition();
        break;

        case ductLocations::middleLine6:
            return middleLineContactPoint6->getPosition();
        break;

        case ductLocations::middleLineTurn_:
            return middleLineTurn->getPosition();
        break;

        case ductLocations::rightMiddleTurn_:
            return rightMiddleTurn->getPosition();
        break;

        case ductLocations::leftMiddleTurn_:
            return leftMiddleTurn->getPosition();
        break;

        case ductLocations::middleLineUp1:
            return middleLineUpContactPoint1->getPosition();
        break;

        case ductLocations::middleLineUp2:
            return middleLineUpContactPoint2->getPosition();
        break;

        case ductLocations::bottomRightLine1:
            return bottomRightLineContactPoint1->getPosition();
        break;

        case ductLocations::bottomLeftLine1:
            return bottomLeftLineContactPoint1->getPosition();
        break;

        case ductLocations::bottomLeftToEndTurn_:
            return bottomLeftToEndTurn->getPosition();
        break;

        case ductLocations::bottomRightToEndTurn_:
            return bottomRightToEndTurn->getPosition();
        break;

        case ductLocations::RightEnd:
            return RightEndContactPoint->getPosition();
        break;

        case ductLocations::LeftEnd:
            return LeftEndContactPoint->getPosition();
        break;
    }
    return {0,0};
}

CNGameLayer::ductLocations CNGameLayer::moveDuctPos (ductLocations position){
        int random2Dir = rand() % 3;//for 2 directions
        int random3Dir = rand() % 4;//for 3 directions with 1 prefered path
        int random3DirBigger = rand() % 5;//for 3 directions with 2 prefered paths
        switch (position){
        //entrenceleft1
        case ductLocations::entrenceLeft1:
            if (random2Dir == 0){
                return ductLocations::entrenceLeft1;
            }
            else{
                return ductLocations::entrenceLeft2;
            }
        break;

        //entrenceleft2
        case ductLocations::entrenceLeft2:
            if (random2Dir == 0){
                return ductLocations::entrenceLeft1;
            }
            else{
                return ductLocations::topLine2;
            }
        break;

        //entrenceright1
        case ductLocations::entrenceRight1:
            if (random2Dir == 0){
                return ductLocations::entrenceRight1;
            }
            else{
                return ductLocations::entrenceRight2;
            }
        break;

        //entrenceright2
        case ductLocations::entrenceRight2:
            if (random2Dir == 0){
                return ductLocations::entrenceRight1;
            }
            else{
                return ductLocations::topLine1;
            }
        break;
        
        case ductLocations::topLine1:
            if (random3DirBigger == 0){
                return ductLocations::entrenceRight2;
            }
            else if (random3DirBigger == 1 || random3DirBigger == 2){
                return ductLocations::topLine7;
            }
            else {
                return ductLocations::topLine5;
            }
        break;

        case ductLocations::topLine2:
            if (random3DirBigger == 0){
                return ductLocations::entrenceLeft2;
            }
            else if (random3DirBigger == 1 || random3DirBigger == 2){
                return ductLocations::topLine6;
            }
            else {
                return ductLocations::topLine3;
            }
        break;

        case ductLocations::topLine3:
            if (random2Dir == 0){
                return ductLocations::topLine2;
            }
            else{
                return ductLocations::topLine4;
            }
        break;

        case ductLocations::topLine4:
            if (random3Dir == 0){
                return ductLocations::topLine3;
            }
            else if (random3DirBigger == 1){
                return ductLocations::topLine5;
            }
            else {
                return ductLocations::middleLineUp2;
            }
        break;

        case ductLocations::topLine5:
            if (random2Dir == 0){
                return ductLocations::topLine1;
            }
            else{
                return ductLocations::topLine4;
            }
        break;

        case ductLocations::topLine6:
            if (random2Dir == 0){
                return ductLocations::topLine2;
            }
            else{
                return ductLocations::topLeftTurn_;
            }
        break;

        case ductLocations::topLine7:
            if (random2Dir == 0){
                return ductLocations::topLine1;
            }
            else{
                return ductLocations::topRightTurn_;
            }
        break;
        
        case ductLocations::topRightTurn_:
            if (random2Dir == 0){
                return ductLocations::topLine7;
            }
            else{
                return ductLocations::rightLine1;
            }
        break;
        
        case ductLocations::topLeftTurn_:
            if (random2Dir == 0){
                return ductLocations::topLine6;
            }
            else{
                return ductLocations::leftLine1;
            }
        break;
        
        case ductLocations::rightLine1:
            if (random2Dir == 0){
                return ductLocations::topRightTurn_;
            }
            else{
                return ductLocations::rightLine2;
            }
        break;

        case ductLocations::rightLine2:
            if (random2Dir == 0){
                return ductLocations::rightLine1;
            }
            else{
                return ductLocations::rightMiddleTurn_;
            }
        break;

        case ductLocations::rightLine3:
            if (random2Dir == 0){
                return ductLocations::rightMiddleTurn_;
            }
            else{
                return ductLocations::rightLine4;
            }
        break;

        case ductLocations::rightLine4:
            if (random2Dir == 0){
                return ductLocations::rightLine3;
            }
            else{
                return ductLocations::bottomRightTurn_;
            }
        break;
        
        case ductLocations::leftLine1:
            if (random2Dir == 0){
                return ductLocations::topLeftTurn_;
            }
            else{
                return ductLocations::leftLine2;
            }
        break;

        case ductLocations::leftLine2:
            if (random2Dir == 0){
                return ductLocations::leftLine1;
            }
            else{
                return ductLocations::leftMiddleTurn_;
            }
        break;

        case ductLocations::leftLine3:
            if (random2Dir == 0){
                return ductLocations::leftMiddleTurn_;
            }
            else{
                return ductLocations::leftLine4;
            }
        break;

        case ductLocations::leftLine4:
            if (random2Dir == 0){
                return ductLocations::leftLine3;
            }
            else{
                return ductLocations::bottomLeftTurn_;
            }
        break;

        case ductLocations::rightMiddleTurn_:
            if (random3Dir == 0){
                return ductLocations::rightLine2;
            }
            else if (random3Dir == 1){
                return ductLocations::middleLine6;
            }
            else{
                return ductLocations::rightLine3;
            }
        break;

        case ductLocations::leftMiddleTurn_:
            if (random3Dir == 0){
                return ductLocations::leftLine2;
            }
            else if (random3Dir == 1){
                return ductLocations::middleLine1;
            }
            else{
                return ductLocations::leftLine3;
            }
        break;
        
        case ductLocations::bottomRightTurn_:
            if (random2Dir == 0){
                return ductLocations::rightLine4;
            }
            else{
                return ductLocations::bottomRightLine1;
            }
        break;

        case ductLocations::bottomLeftTurn_:
            if (random2Dir == 0){
                return ductLocations::leftLine4;
            }
            else{
                return ductLocations::bottomLeftLine1;
            }
        break;
        
        case ductLocations::middleLine1:
            if (random2Dir == 0){
                return ductLocations::middleLine2;
            }
            else{
                return ductLocations::leftMiddleTurn_;
            }
        break;

        case ductLocations::middleLine2:
            if (random2Dir == 0){
                return ductLocations::middleLine3;
            }
            else{
                return ductLocations::middleLine1;
            }
        break;

        case ductLocations::middleLine3:
            if (random2Dir == 0){
                return ductLocations::middleLineTurn_;
            }
            else{
                return ductLocations::middleLine2;
            }
        break;

        case ductLocations::middleLine4:
            if (random2Dir == 0){
                return ductLocations::middleLineTurn_;
            }
            else{
                return ductLocations::middleLine5;
            }
        break;

        case ductLocations::middleLine5:
            if (random2Dir == 0){
                return ductLocations::middleLine4;
            }
            else{
                return ductLocations::middleLine6;
            }
        break;

        case ductLocations::middleLine6:
            if (random2Dir == 0){
                return ductLocations::middleLine5;
            }
            else{
                return ductLocations::rightMiddleTurn_;
            }
        break;

        case ductLocations::middleLineTurn_:
            if (random3DirBigger == 0){
                return ductLocations::middleLineUp1;
            }
            else if (random3DirBigger == 1 || random3DirBigger == 2){
                return ductLocations::middleLine4;
            }
            else {
                return ductLocations::middleLine3;
            }
        break;

        case ductLocations::middleLineUp1:
            if (random2Dir == 0){
                return ductLocations::middleLineUp2;
            }
            else{
                return ductLocations::middleLineTurn_;
            }
        break;

        case ductLocations::middleLineUp2:
            if (random2Dir == 0){
                return ductLocations::topLine4;
            }
            else{
                return ductLocations::middleLineUp1;
            }
        break;

        case ductLocations::bottomRightLine1:
            if (random2Dir == 0){
                return ductLocations::bottomRightTurn_;
            }
            else{
                return ductLocations::bottomRightToEndTurn_;
            }
        break;

        case ductLocations::bottomLeftLine1:
            if (random2Dir == 0){
                return ductLocations::bottomLeftTurn_;
            }
            else{
                return ductLocations::bottomLeftToEndTurn_;
            }
        break;

        case ductLocations::bottomLeftToEndTurn_:
            if (random2Dir == 0){
                return ductLocations::bottomLeftLine1;
            }
            else{
                return ductLocations::LeftEnd;
            }
        break;

        case ductLocations::bottomRightToEndTurn_:
            if (random2Dir == 0){
                return ductLocations::bottomRightLine1;
            }
            else{
                return ductLocations::RightEnd;
            }
        break;

        case ductLocations::RightEnd:
            if (random2Dir == 0){
                return ductLocations::bottomRightToEndTurn_;
            }
            else{
                return ductLocations::RightEnd;
            }
        break;

        case ductLocations::LeftEnd:
            if (random2Dir == 0){
                return ductLocations::bottomLeftToEndTurn_;
            }
            else{
                return ductLocations::LeftEnd;
            }
        break;
    }
    return resetDuctPosition();
}

CNGameLayer::ductLocations CNGameLayer::resetDuctPosition(){
    int selection = rand() % 2;

    if (selection == 0){
        return ductLocations::entrenceLeft1;
    }
    else if (selection == 1){
        return ductLocations::entrenceRight1;
    }
    return ductLocations::entrenceLeft1;
}

bool CNGameLayer::isOnClosedDuct(ductLocations position){
    if (position == ductLocations::LeftEnd && RightDuctOpen){
        return true;
    }
    else if (position == ductLocations::RightEnd && !RightDuctOpen){
        return true;
    }
    return false;
}

bool CNGameLayer::hasReachedEndofDucts(ductLocations position){
    if (position == ductLocations::LeftEnd){
        return true;
    }
    else if (position == ductLocations::RightEnd){
        return true;
    }
    return false;
}

bool CNGameLayer::isInAudioLure(ductLocations position){
    CCPoint testpoint = {999, 999};
    if (audioLore->getPosition() != testpoint){

        std::vector<ductLocations> effectedLocations;
        effectedLocations.insert(effectedLocations.begin(), audioLoreLocation);
        switch (audioLoreLocation){
            //entrenceleft1
            case ductLocations::entrenceLeft1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::entrenceLeft2);
            break;

            //entrenceleft2
            case ductLocations::entrenceLeft2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::entrenceLeft1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine2);
            break;

            //entrenceright1
            case ductLocations::entrenceRight1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::entrenceRight2);
            break;

            //entrenceright2
            case ductLocations::entrenceRight2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::entrenceRight1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine1);
            break;

            case ductLocations::topLine1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::entrenceRight2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine7);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine5);
            break;

            case ductLocations::topLine2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::entrenceLeft2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine6);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine3);
            break;

            case ductLocations::topLine3:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine4);
            break;

            case ductLocations::topLine4:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine3);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine5);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineUp2);
            break;

            case ductLocations::topLine5:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine4);
            break;

            case ductLocations::topLine6:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLeftTurn_);
            break;

            case ductLocations::topLine7:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topRightTurn_);
            break;

            case ductLocations::topRightTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine7);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine1);
            break;

            case ductLocations::topLeftTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine6);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine1);
            break;

            case ductLocations::rightLine1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topRightTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine2);
            break;

            case ductLocations::rightLine2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightMiddleTurn_);
            break;

            case ductLocations::rightLine3:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightMiddleTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine4);
            break;

            case ductLocations::rightLine4:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine3);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomRightTurn_);
            break;

            case ductLocations::leftLine1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLeftTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine2);
            break;

            case ductLocations::leftLine2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftMiddleTurn_);
            break;

            case ductLocations::leftLine3:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftMiddleTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine4);
            break;

            case ductLocations::leftLine4:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine3);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomLeftTurn_);
            break;

            case ductLocations::bottomRightTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine4);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomRightLine1);
            break;

            case ductLocations::bottomLeftTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine4);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomLeftLine1);
            break;

            case ductLocations::middleLine1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftMiddleTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine2);
            break;

            case ductLocations::middleLine2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine3);
            break;

            case ductLocations::middleLine3:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineTurn_);
            break;

            case ductLocations::middleLine4:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine5);
            break;

            case ductLocations::middleLine5:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine4);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine6);
            break;

            case ductLocations::middleLine6:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine5);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightMiddleTurn_);
            break;

            case ductLocations::middleLineTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine3);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine4);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineUp1);
            break;

            case ductLocations::rightMiddleTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::rightLine3);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine6);
            break;

            case ductLocations::leftMiddleTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine2);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::leftLine3);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLine1);
            break;

            case ductLocations::middleLineUp1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineUp2);
            break;

            case ductLocations::middleLineUp2:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::topLine4);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::middleLineUp1);
            break;

            case ductLocations::bottomRightLine1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomRightTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomRightToEndTurn_);
            break;

            case ductLocations::bottomLeftLine1:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomLeftTurn_);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomLeftToEndTurn_);
            break;

            case ductLocations::bottomLeftToEndTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomLeftLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::LeftEnd);
            break;

            case ductLocations::bottomRightToEndTurn_:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomRightLine1);
                effectedLocations.insert(effectedLocations.begin(), ductLocations::RightEnd);
            break;

            case ductLocations::RightEnd:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomRightToEndTurn_);
            break;

            case ductLocations::LeftEnd:
                effectedLocations.insert(effectedLocations.begin(), ductLocations::bottomLeftToEndTurn_);
            break;
        }
        for (size_t i = 0; i < effectedLocations.size(); i++)
        {
            if (effectedLocations[i] == position){
                return true;
            }
        }
    }

    return false;
}

CCSprite* CNGameLayer::CreatePoof(){
    CCSprite* poof = CCSprite::create("cloud1.png"_spr);
    PlayAnimationOnSpriteWithCallBack(poof, 0.05f, 11, new std::string[]{
        "cloud1.png"_spr,
        "cloud2.png"_spr,
        "cloud3.png"_spr,
        "cloud4.png"_spr,
        "cloud5.png"_spr,
        "cloud6.png"_spr,
        "cloud7.png"_spr,
        "cloud8.png"_spr,
        "cloud9.png"_spr,
        "cloud10.png"_spr,
        "cloud11.png"_spr,
    }, callfunc_selector(CNGameLayer::endedPoof));
    poofs.insert(poofs.begin(), poof);

    return poof;
}

void CNGameLayer::endedPoof(){
    for (size_t i = 0; i < poofs.size(); i++)
    {
        if (poofs[i]->getActionByTag(29847)->isDone()){
            poofs[i]->removeMeAndCleanup();
            poofs.erase(std::next(poofs.begin(), i));
        }
    }
    
}

void CNGameLayer::PutDownCams(){
    if (InCams){
        InCams = false;
        if (LookingAtCams){
            LookingAtCams = false;
            usageAmount--;
        }
        PlayAnimationOnSprite(Cams, 0, 2, new std::string[]{
            "monitor12.png"_spr,
            "monitor12.png"_spr
        });
        MaskButton->setVisible(true);
        cameraView->setPosition({0, 999});
        CamsButton->setOpacity(255);
        cameraUI->setPosition({0, 999});
        cameraOverallUI->setPosition({0, 999});
        ventUI->setPosition({0, 999});
        ductUI->setPosition({0, 999});
        CamStatic->setVisible(false);
        PlayAnimationOnSprite(Cams, 0.02f, 12, new std::string[]{
            "monitor12.png"_spr,
            "monitor11.png"_spr,
            "monitor10.png"_spr,
            "monitor9.png"_spr,
            "monitor8.png"_spr,
            "monitor7.png"_spr,
            "monitor6.png"_spr,
            "monitor5.png"_spr,
            "monitor4.png"_spr,
            "monitor3.png"_spr,
            "monitor2.png"_spr,
            "monitor1.png"_spr
        });
    }
}

void CNGameLayer::disableFlashlight(){
    if (FlashlightOn){
        Flashlight->setVisible(false);
        usageAmount--;
        FlashlightOn = false;
    }
}

void CNGameLayer::PreloadImages(std::vector<std::string> images){
    for (size_t i = 0; i < images.size(); i++)
    {
        CCSprite* ima = CCSprite::create(images[i].c_str());
        this->addChild(ima);
        ima->removeMeAndCleanup();
    }
}
