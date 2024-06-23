#include "gdcube.h"

gdcube* gdcube::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new gdcube();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool gdcube::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    icon = CCSprite::create("cubeIcon.png"_spr);
    icon->setZOrder(1);
    icon->setScale(0.8f);
    mainLayer->ventUI->addChild(icon);

    Position = mainLayer->resetVentPos();

    mainLayer->PreloadImages(std::vector<std::string>{
        "cubeJ0001.png"_spr,
        "cubeJ0002.png"_spr,
        "cubeJ0003.png"_spr,
        "cubeJ0004.png"_spr,
        "cubeJ0005.png"_spr,
        "cubeJ0006.png"_spr,
        "cubeJ0007.png"_spr,
        "cubeJ0008.png"_spr,
        "cubeJ0009.png"_spr,
        "cubeJ0010.png"_spr,
        "cubeJ0011.png"_spr,
        "cubeJ0012.png"_spr,
        "cubeJ0013.png"_spr,
        "cubeJ0014.png"_spr,
        "cubeJ0015.png"_spr,
        "cubeJ0016.png"_spr,
        "cubeJ0017.png"_spr,
        "cubeJ0018.png"_spr,
        "cubeJ0019.png"_spr,
        "cubeJ0020.png"_spr,
        "cubeJ0021.png"_spr,
        "cubeJ0022.png"_spr,
        "cubeJ0023.png"_spr,
        "cubeJ0024.png"_spr,
        "cubeJ0025.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void gdcube::update(float delta){
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
    }

    if (mainLayer->isTouchingVentSnare(Position)){
        Position = mainLayer->resetVentPos();
        icon->setPosition(mainLayer->getVentPointFromPosition(Position));
        mainLayer->CharacterBlock();
    }
    if (mainLayer->hasReachedEndOfVent(Position) && !killplayer){
        killplayer = true;
        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
            0.02f, 25, new std::string[]{
                "cubeJ0001.png"_spr,
                "cubeJ0002.png"_spr,
                "cubeJ0003.png"_spr,
                "cubeJ0004.png"_spr,
                "cubeJ0005.png"_spr,
                "cubeJ0006.png"_spr,
                "cubeJ0007.png"_spr,
                "cubeJ0008.png"_spr,
                "cubeJ0009.png"_spr,
                "cubeJ0010.png"_spr,
                "cubeJ0011.png"_spr,
                "cubeJ0012.png"_spr,
                "cubeJ0013.png"_spr,
                "cubeJ0014.png"_spr,
                "cubeJ0015.png"_spr,
                "cubeJ0016.png"_spr,
                "cubeJ0017.png"_spr,
                "cubeJ0018.png"_spr,
                "cubeJ0019.png"_spr,
                "cubeJ0020.png"_spr,
                "cubeJ0021.png"_spr,
                "cubeJ0022.png"_spr,
                "cubeJ0023.png"_spr,
                "cubeJ0024.png"_spr,
                "cubeJ0025.png"_spr,
            }
        ), "explode_11.mp3"_spr, false, false, false);
    }
    if (_AILevel == 0){
        icon->setVisible(false);
    }
    else{
        icon->setVisible(true);
    }
}

void gdcube::OnOpportunity(){

    Position.progressAmount += 8;

    icon->setPosition(mainLayer->getVentPointFromPosition(Position));
}