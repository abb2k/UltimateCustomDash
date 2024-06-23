#include "aeonair.h"

aeonair* aeonair::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new aeonair();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool aeonair::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    aeon = CCSprite::create("aeonReqFace.png"_spr);
    aeon->setVisible(false);
    mainLayer->Cam01->addChild(aeon);

    /*
    
    pos 0:
    invis = true;

    pos 1:
    invis = false;
    pos 55, 30
    scale 1
    rotation -2, 10
    
    pos 2:
    invis = false;
    pos 22, -8
    scale 1.2f
    rotation -2, 2

    pos 3:
    invis = false;
    pos 3, -28
    scale 1.6f
    rotation 4, -12

    pos 4:
    invis = false;
    pos 37, -60
    scale 2.425f
    rotation 8, -44
    
    */

    scheduleUpdate();

    return true;
}

void aeonair::update(float delta){
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

        if (progress >= 0 && progress <= 100){
            if (pulse){
                pulse = false;
                mainLayer->CamStaticOpacity = 255;
            }
            aeon->setVisible(false);
        }
        else if (progress > 100 && progress <= 200){
            if (!pulse){
                pulse = true;
                mainLayer->CamStaticOpacity = 255;
            }
            aeon->setVisible(true);
            aeon->setPosition({55, 30});
            aeon->setScale(1);
            aeon->setRotationX(-2);
            aeon->setRotationY(10);
        }
        else if (progress > 200 && progress <= 300){
            if (pulse){
                pulse = false;
                mainLayer->CamStaticOpacity = 255;
            }
            aeon->setVisible(true);
            aeon->setPosition({22, -8});
            aeon->setScale(1.2f);
            aeon->setRotationX(-2);
            aeon->setRotationY(2);
        }
        else if (progress > 300 && progress <= 400){
            if (!pulse){
                pulse = true;
                mainLayer->CamStaticOpacity = 255;
            }
            aeon->setVisible(true);
            aeon->setPosition({3, -28});
            aeon->setScale(1.6f);
            aeon->setRotationX(4);
            aeon->setRotationY(-12);
        }
        else if (progress > 400 && progress <= 500){
            if (pulse){
                pulse = false;
                mainLayer->CamStaticOpacity = 255;
            }
            aeon->setVisible(true);
            aeon->setPosition({37, -60});
            aeon->setScale(2.425f);
            aeon->setRotationX(8);
            aeon->setRotationY(-44);
        }
        else if (progress > 500){
            if (!pulse){
                pulse = true;
                mainLayer->CamStaticOpacity = 255;
            }
            aeon->setVisible(false);
            if (mainLayer->doorLeftClosed){
                progress = 0;
                mainLayer->CharacterBlock();
            }
            else {
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    0.03f, 14, new std::string[]{
                        "aeonJ0001.png"_spr,
                        "aeonJ0002.png"_spr,
                        "aeonJ0003.png"_spr,
                        "aeonJ0004.png"_spr,
                        "aeonJ0005.png"_spr,
                        "aeonJ0006.png"_spr,
                        "aeonJ0007.png"_spr,
                        "aeonJ0008.png"_spr,
                        "aeonJ0009.png"_spr,
                        "aeonJ0010.png"_spr,
                        "aeonJ0011.png"_spr,
                        "aeonJ0012.png"_spr,
                        "aeonJ0013.png"_spr,
                        "aeonJ0014.png"_spr,
                    }, 2
                ), "aeonAir.mp3"_spr, false, false, false);
            }
        }
    }
}

void aeonair::OnOpportunity(){
    if (mainLayer->tempreture < 79){
        progress += 0.5f;
    }
    else {
        progress += 0.5f * ((mainLayer->tempreture - 79) / 10);
    }
}