#include "SFSun.h"

SFSun* SFSun::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new SFSun();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SFSun::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    sun = CCSprite::create("sfSun.png"_spr);
    sun->setZOrder(1);
    sun->setPosition({0, 215});
    sun->setScale(2.925f);
    sun->setRotation(95);
    mainLayer->Canvas->addChild(sun);

    scheduleUpdate();

    return true;
}

void SFSun::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (mainLayer->tempreture < 79){
            //remove
            progress -= delta * 25;
        }
        else {
            //add
            progress += delta * _AILevel * ((mainLayer->tempreture - 70) / 50);
        }

        if (progress < 0){
            progress = 0;
        }

        if (progress >= 255){
            progress = 255;
            if (!kill){
                kill = true;
                sun->setVisible(false);
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    0.7f, 2, new std::string[]{
                        "sfSun.png"_spr,
                        "sfSun.png"_spr,
                    }
                ), "", false, false, false, 1.5f);
            }
        }

        sun->setOpacity(progress);
    }
}