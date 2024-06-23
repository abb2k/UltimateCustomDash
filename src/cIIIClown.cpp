#include "cIIIClown.h"

cIIIClown* cIIIClown::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new cIIIClown();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool cIIIClown::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    Position = mainLayer->resetVentPos();

    indicateor = AudioSource::create("silence.mp3"_spr, FMOD_DEFAULT, AudioSource::VolumeChannel::SFX);
    this->addChild(indicateor);
    
    scheduleUpdate();

    return true;
}

void cIIIClown::update(float delta){
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

    if (mainLayer->hasReachedEndOfVent(Position)){
        if (!playsound){
            playsound = true;
            indicateor->changeSound("CLOWN.mp3"_spr, FMOD_DEFAULT);
        }
        jumptimer -= delta;

        if (mainLayer->doorUpClosed){
            avoidTimer -= delta;

            if (avoidTimer <= 0){
                avoidTimer = 0.5f;
                jumptimer = 4;
                playsound = false;
                Position = mainLayer->resetVentPos();
                mainLayer->CharacterBlock();
            }
            
        }
        else if (!killplayer){
            if (jumptimer <= 0){
                jumptimer = 0;
                killplayer = true;
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    1, 2, new std::string[]{
                        "Clown.png"_spr,
                        "Clown.png"_spr,
                    }
                ), "", false, false, false, 7);
            }
        }
    }
}

void cIIIClown::OnOpportunity(){
    if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::SilentVentelation){
        Position.progressAmount += 8;
    }
    else if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::PowerAC){
        Position.progressAmount += 12;
    }
    else{
        Position.progressAmount += 10;
    }
}