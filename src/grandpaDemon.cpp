#include "grandpaDemon.h"

grandpaDemon* grandpaDemon::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new grandpaDemon();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool grandpaDemon::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    faceLeft = CCSprite::create("grandpaFace.png"_spr);
    faceLeft->setPosition({51, -67});
    faceLeft->setScale(5.075f);
    faceLeft->setRotationX(-3);
    faceLeft->setRotationY(-29);
    mainLayer->Cam01->addChild(faceLeft);

    faceRight = CCSprite::create("grandpaFace.png"_spr);
    faceRight->setPosition({-104, -47});
    faceRight->setScale(5.075f);
    faceRight->setRotationX(-2);
    faceRight->setRotationY(37);
    mainLayer->Cam02->addChild(faceRight);

    pauseTime = 12.5f / (_AILevel / 15);

    int randomside = rand() % 2;

    if (randomside == 0){
        move(true);
    }
    else if (randomside == 1){
        move(false);
    }

    if (_AILevel == 0){
        faceRight->setVisible(false);
        faceLeft->setVisible(false);
    }

    scheduleUpdate();

    return true;
}

void grandpaDemon::update(float delta){
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
    if (mainLayer->NIGHTSTARTED){
        if (pauseTime > 0){
            pauseTime -= delta;
        }
    }
}

void grandpaDemon::OnOpportunity(){
    if (pauseTime <= 0){
        if (Onleft){
            if (mainLayer->floorSignOnLeft){
                block();
            }
            else{
                kill();
            }
        }
        // on right
        else{
            if (!mainLayer->floorSignOnLeft){
                block();
            }
            else{
                kill();
            }
        }
    }
}

void grandpaDemon::block(){
    int randomside = rand() % 2;

    pauseTime = 12.5f / (_AILevel / 15);

    if (randomside == 0){
        if (!Onleft){
            move(true);
        }
    }
    else if (randomside == 1){
        if (Onleft){
            move(false);
        }
    }
}

void grandpaDemon::kill(){
    if (!killplayer){
        killplayer = true;
        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
            1, 2, new std::string[]{
                "grandpaFace.png"_spr,
                "grandpaFace.png"_spr,
            }
        ), "grandpa.mp3"_spr, false, false, false, 4.5f);
    }
}

void grandpaDemon::move(bool toLeft){
    if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera01 || mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
        mainLayer->CamStaticOpacity = 255;
    }
    if (toLeft){
        Onleft = true;
        faceLeft->setVisible(true);
        faceRight->setVisible(false);
    }
    else{
        Onleft = false;
        faceLeft->setVisible(false);
        faceRight->setVisible(true);
    }
}