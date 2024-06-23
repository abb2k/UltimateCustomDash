#include "BB.h"

BB* BB::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new BB();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool BB::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    Face = CCSprite::create("bbFace.png"_spr);
    Face->setZOrder(5);
    Face->setPosition({140, 201});
    Face->setRotation(-13);
    Face->setScale(0.475f);
    mainLayer->World->addChild(Face);

    if (_AILevel == 0){
        Face->setVisible(false);
    }

    scheduleUpdate();

    return true;
}

void BB::update(float delta){
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
}

void BB::OnOpportunity(){
    if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::SilentVentelation){
        if (anger > 0){
            anger -= 0.05f * 20;
            if (anger <= 0){
                anger = 0;
            }
        }
    }
    if (mainLayer->LookingAtCams){
        if (anger < 100){
            anger += 0.025f * _AILevel;

            if (anger >= 100){
                anger = 100;
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    0.7f, 2, new std::string[]{
                        "bbFace.png"_spr,
                        "bbFace.png"_spr,
                    }
                ), "", false, false, false, 6);
            }
        }
    }

    GLubyte color = (GLubyte)(anger * 2.55f);

    Face->setColor({color, 0, 0});
}