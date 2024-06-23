#include "EVW.h"

EVW* EVW::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new EVW();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool EVW::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    wilderman = CCSprite::create("evw.png"_spr);
    wilderman->setVisible(false);
    wilderman->setScale(2.3f);
    mainLayer->Cam03->addChild(wilderman);

    mainLayer->PreloadImages(std::vector<std::string>{
        "evwJ0001.png"_spr,
        "evwJ0002.png"_spr,
        "evwJ0003.png"_spr,
        "evwJ0004.png"_spr,
        "evwJ0005.png"_spr,
        "evwJ0006.png"_spr,
        "evwJ0007.png"_spr,
        "evwJ0008.png"_spr,
        "evwJ0009.png"_spr,
        "evwJ0010.png"_spr,
        "evwJ0011.png"_spr,
        "evwJ0012.png"_spr,
        "evwJ0013.png"_spr,
        "evwJ0014.png"_spr,
        "evwJ0015.png"_spr,
    });

    /*
    
    pos0: 
    invis = true

    pos1: 
    pos -8, 54
    rotation -5, 2
    
    pos2: 
    pos -46, 35
    rotation 0, -29

    pos3: 
    pos 19, 0
    rotation 8, -44
    
    */

    scheduleUpdate();

    return true;
}

void EVW::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::PowerAC){
            progress -= 10 * delta;
        }
        else {
            if (mainLayer->noiseAmount > 1){
                progress += ((mainLayer->noiseAmount - 1) * _AILevel * delta) / 40;
            }

            if (mainLayer->tempreture > 84){
                progress += ((mainLayer->tempreture - 80) * _AILevel * delta) / 100;
            }
        }

        if (progress < 0){
            progress = 0;
        }
        if (progress > 0 && progress <= 25){
            if (pulse){
                pulse = false;
                mainLayer->CamStaticOpacity = 255;
            }
            wilderman->setVisible(false);
        }
        else if (progress > 25 && progress <= 50){
            if (!pulse){
                pulse = true;
                mainLayer->CamStaticOpacity = 255;
            }
            wilderman->setVisible(true);
            wilderman->setPosition({-8, 54});
            wilderman->setRotationX(-5);
            wilderman->setRotationY(2);
        }
        else if (progress > 50 && progress <= 75){
            if (pulse){
                pulse = false;
                mainLayer->CamStaticOpacity = 255;
            }
            wilderman->setVisible(true);
            wilderman->setPosition({-46, 35});
            wilderman->setRotationX(0);
            wilderman->setRotationY(-29);
        }
        else if (progress > 75 && progress <= 100){
            if (!pulse){
                pulse = true;
                mainLayer->CamStaticOpacity = 255;
            }
            wilderman->setVisible(true);
            wilderman->setPosition({19, 0});
            wilderman->setRotationX(8);
            wilderman->setRotationY(-44);
        }
        else if (progress > 100){
            wilderman->setVisible(false);
            if (!killPlayer){
                killPlayer = true;
                mainLayer->CamStaticOpacity = 255;
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    0.03f, 15, new std::string[]{
                        "evwJ0001.png"_spr,
                        "evwJ0002.png"_spr,
                        "evwJ0003.png"_spr,
                        "evwJ0004.png"_spr,
                        "evwJ0005.png"_spr,
                        "evwJ0006.png"_spr,
                        "evwJ0007.png"_spr,
                        "evwJ0008.png"_spr,
                        "evwJ0009.png"_spr,
                        "evwJ0010.png"_spr,
                        "evwJ0011.png"_spr,
                        "evwJ0012.png"_spr,
                        "evwJ0013.png"_spr,
                        "evwJ0014.png"_spr,
                        "evwJ0015.png"_spr,
                    }, 2
                ), "IMMMMMMMPOSSIBLE.mp3"_spr, false, false, false);
            }
        }
    }
}