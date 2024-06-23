#include "nSwish.h"

nSwish* nSwish::create(CNGameLayer* gameLayer, int AILevel) {
    auto ret = new nSwish();
    if (ret && ret->init(gameLayer, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool nSwish::init(CNGameLayer* gameLayer, int AILevel){

    mainLayer = gameLayer;
    _AILevel = AILevel;

    mainLayer->PreloadImages(std::vector<std::string>{
        "NSJu0001.png"_spr,
        "NSJu0002.png"_spr,
        "NSJu0003.png"_spr,
        "NSJu0004.png"_spr,
        "NSJu0005.png"_spr,
        "NSJu0006.png"_spr,
        "NSJu0007.png"_spr,
        "NSJu0008.png"_spr,
        "NSJu0009.png"_spr,
        "NSJu0010.png"_spr,
        "NSJu0011.png"_spr,
        "NSJu0012.png"_spr,
        "NSJu0013.png"_spr,
        "NSJu0014.png"_spr,
        "NSJu0015.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void nSwish::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        anger += delta * (mainLayer->noiseAmount / 4.5f) * (_AILevel / 4);

        if (mainLayer->noiseAmount == 0){
            if (anger > 0){
                anger -= delta * 2;

                if (anger <= 0){
                    anger = 0;
                }
            }
        }

        if (anger >= 100){
            anger = 0;
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                0.03f, 15, new std::string[]{
                    "NSJu0001.png"_spr,
                    "NSJu0002.png"_spr,
                    "NSJu0003.png"_spr,
                    "NSJu0004.png"_spr,
                    "NSJu0005.png"_spr,
                    "NSJu0006.png"_spr,
                    "NSJu0007.png"_spr,
                    "NSJu0008.png"_spr,
                    "NSJu0009.png"_spr,
                    "NSJu0010.png"_spr,
                    "NSJu0011.png"_spr,
                    "NSJu0012.png"_spr,
                    "NSJu0013.png"_spr,
                    "NSJu0014.png"_spr,
                    "NSJu0015.png"_spr,
                }, 2
            ), "nswishXO.mp3"_spr, false, false, false);
        }

        if (anger > 20){
            if (clickTimer > 0){
                clickTimer -= delta;
            }
            else {
                if (anger < 90){
                    clickTimer = (100 - anger) / 26.666666666666666666666666666667f;
                }
                else {
                    clickTimer = 10 / 26.666666666666666666666666666667f;
                }
                FMODAudioEngine::sharedEngine()->playEffect("nSwishClick.mp3"_spr, 1.0f,1.0f,1.0f);
            }
        }
    }
}