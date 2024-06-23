#include "timeMachineDinosaur.h"

timeMachineDinosaur* timeMachineDinosaur::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new timeMachineDinosaur();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool timeMachineDinosaur::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    Dinosaur = CCSprite::create("dino.png"_spr);
    Dinosaur->setZOrder(2);
    Dinosaur->setPosition({66, 2});
    Dinosaur->setScale(1.15f);
    Dinosaur->setVisible(false);
    mainLayer->CamViewStatic->addChild(Dinosaur);

    scheduleUpdate();

    return true;
}

void timeMachineDinosaur::update(float delta){
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

    if (mainLayer->currentCamSelected != cam){
        Dinosaur->setVisible(false);
        appeared = false;
    }
}

void timeMachineDinosaur::OnOpportunity(){
    if (!appeared){
        appeared = true;
        cam = mainLayer->currentCamSelected;
        mainLayer->CamStaticOpacity = 255;
        Dinosaur->setVisible(true);
    }
}