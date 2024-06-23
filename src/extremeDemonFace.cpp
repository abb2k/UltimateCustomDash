#include "extremeDemonFace.h"

extremeDemonFace* extremeDemonFace::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new extremeDemonFace();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool extremeDemonFace::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    mainLayer->PreloadImages(std::vector<std::string>{
        "extremeDJu0001.png"_spr,
        "extremeDJu0002.png"_spr,
        "extremeDJu0003.png"_spr,
        "extremeDJu0004.png"_spr,
        "extremeDJu0005.png"_spr,
        "extremeDJu0006.png"_spr,
        "extremeDJu0007.png"_spr,
        "extremeDJu0008.png"_spr,
        "extremeDJu0009.png"_spr,
        "extremeDJu0010.png"_spr,
        "extremeDJu0011.png"_spr,
        "extremeDJu0012.png"_spr,
        "extremeDJu0013.png"_spr,
        "extremeDJu0014.png"_spr,
        "extremeDJu0015.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void extremeDemonFace::update(float delta){
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
        if (killTimer > 0){
            killTimer -= delta;
        }
        else{
            if (!blockOrKill){
                blockOrKill = true;

                if (mainLayer->doorBottomRightClosed){
                    mainLayer->CharacterBlock();
                }
                else{
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.025f, 15, new std::string[]{
                            "extremeDJu0001.png"_spr,
                            "extremeDJu0002.png"_spr,
                            "extremeDJu0003.png"_spr,
                            "extremeDJu0004.png"_spr,
                            "extremeDJu0005.png"_spr,
                            "extremeDJu0006.png"_spr,
                            "extremeDJu0007.png"_spr,
                            "extremeDJu0008.png"_spr,
                            "extremeDJu0009.png"_spr,
                            "extremeDJu0010.png"_spr,
                            "extremeDJu0011.png"_spr,
                            "extremeDJu0012.png"_spr,
                            "extremeDJu0013.png"_spr,
                            "extremeDJu0014.png"_spr,
                            "extremeDJu0015.png"_spr,
                        }, 2
                    ), "explode_11.mp3"_spr, false, false, false);
                }
            }
        }
    }
}

void extremeDemonFace::OnOpportunity(){
    warning = AudioSource::create("ventbang.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
    this->addChild(warning);

    blockOrKill = false;
    mainLayer->FlashEffects(1.4f);
    killTimer = 1.4f;
}