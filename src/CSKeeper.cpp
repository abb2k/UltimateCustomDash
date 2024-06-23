#include "CSKeeper.h"

CSKeeper* CSKeeper::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new CSKeeper();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool CSKeeper::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    if (_AILevel != 0){
        music = AudioSource::create("shoptheme.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::VolumeChannel::Music);
        this->addChild(music);
    }

    mainLayer->PreloadImages(std::vector<std::string>{
        "CSKJ0001.png"_spr,
        "CSKJ0002.png"_spr,
        "CSKJ0003.png"_spr,
        "CSKJ0004.png"_spr,
        "CSKJ0005.png"_spr,
        "CSKJ0006.png"_spr,
        "CSKJ0007.png"_spr,
        "CSKJ0008.png"_spr,
        "CSKJ0009.png"_spr,
        "CSKJ0010.png"_spr,
        "CSKJ0011.png"_spr,
        "CSKJ0012.png"_spr,
        "CSKJ0013.png"_spr,
        "CSKJ0014.png"_spr,
        "CSKJ0015.png"_spr,
        "CSKJ0016.png"_spr,
        "CSKJ0017.png"_spr,
        "CSKJ0018.png"_spr,
        "CSKJ0019.png"_spr,
        "CSKJ0020.png"_spr,
        "CSKJ0021.png"_spr,
        "CSKJ0022.png"_spr,
        "CSKJ0023.png"_spr,
        "CSKJ0024.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void CSKeeper::update(float delta){
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

        if (mainLayer->ChangeMusicButton->getChildrenCount() == 0){
            if (mainLayer->getTouchOn(mainLayer->ChangeMusicButton)){
                if (_AILevel != 0){
                    if (attacking){
                        attacking = false;
                        music->Paused(false);
                    }
                    else {
                        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                            0.03f, 24, new std::string[]{
                                "CSKJ0001.png"_spr,
                                "CSKJ0002.png"_spr,
                                "CSKJ0003.png"_spr,
                                "CSKJ0004.png"_spr,
                                "CSKJ0005.png"_spr,
                                "CSKJ0006.png"_spr,
                                "CSKJ0007.png"_spr,
                                "CSKJ0008.png"_spr,
                                "CSKJ0009.png"_spr,
                                "CSKJ0010.png"_spr,
                                "CSKJ0011.png"_spr,
                                "CSKJ0012.png"_spr,
                                "CSKJ0013.png"_spr,
                                "CSKJ0014.png"_spr,
                                "CSKJ0015.png"_spr,
                                "CSKJ0016.png"_spr,
                                "CSKJ0017.png"_spr,
                                "CSKJ0018.png"_spr,
                                "CSKJ0019.png"_spr,
                                "CSKJ0020.png"_spr,
                                "CSKJ0021.png"_spr,
                                "CSKJ0022.png"_spr,
                                "CSKJ0023.png"_spr,
                                "CSKJ0024.png"_spr,
                            }, 2
                        ), "magicEx.mp3"_spr, false, false, false);
                        music->CleanUpSound();
                    }
                }
                mainLayer->changeMusic();
            }
        }

        if (attacking){
            killtimer -= delta;

            if (killtimer <= 0){
                killtimer = 0;
                if (!kill){
                    kill = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.03f, 24, new std::string[]{
                            "CSKJ0001.png"_spr,
                            "CSKJ0002.png"_spr,
                            "CSKJ0003.png"_spr,
                            "CSKJ0004.png"_spr,
                            "CSKJ0005.png"_spr,
                            "CSKJ0006.png"_spr,
                            "CSKJ0007.png"_spr,
                            "CSKJ0008.png"_spr,
                            "CSKJ0009.png"_spr,
                            "CSKJ0010.png"_spr,
                            "CSKJ0011.png"_spr,
                            "CSKJ0012.png"_spr,
                            "CSKJ0013.png"_spr,
                            "CSKJ0014.png"_spr,
                            "CSKJ0015.png"_spr,
                            "CSKJ0016.png"_spr,
                            "CSKJ0017.png"_spr,
                            "CSKJ0018.png"_spr,
                            "CSKJ0019.png"_spr,
                            "CSKJ0020.png"_spr,
                            "CSKJ0021.png"_spr,
                            "CSKJ0022.png"_spr,
                            "CSKJ0023.png"_spr,
                            "CSKJ0024.png"_spr,
                        }, 2
                    ), "magicEx.mp3"_spr, false, false, false);
                    music->CleanUpSound();
                }
            }
        }
    }
    if (mainLayer->DEATHSCREEN) {
        if (!removemusic && music != nullptr){
            removemusic = true;
            music->CleanUpSound();
        }
    }
    if (mainLayer->nightComplete) {
        if (!removemusic && music != nullptr){
            removemusic = true;
            music->CleanUpSound();
        }
    }
    if (mainLayer->escaped) {
        if (!removemusic && music != nullptr){
            removemusic = true;
            music->CleanUpSound();
        }
    }
}

void CSKeeper::OnOpportunity(){
    killtimer = 5;
    attacking = true;
    music->Paused(true);
}