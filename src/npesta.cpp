#include "npesta.h"

npesta* npesta::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new npesta();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool npesta::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    officeIcon = CCSprite::create("npestaIcon.png"_spr);
    officeIcon->setZOrder(2);
    officeIcon->setScale(2.25f);
    officeIcon->setPosition({139, 77});
    officeIcon->setVisible(false);
    mainLayer->World->addChild(officeIcon);

    std::vector<std::string> jumps;

    for (int i = 0; i < 65; i++)
    {
        if (i < 9){
            jumps.insert(jumps.end(), "creepypasta000"_spr + std::to_string((i + 1)) +".png");
        }
        else {
            jumps.insert(jumps.end(), "creepypasta00"_spr + std::to_string((i + 1)) +".png");
        }
    }

    mainLayer->PreloadImages(jumps);
    
    scheduleUpdate();

    return true;
}

void npesta::update(float delta){
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
        if (mainLayer->InMask){
            inOffice = false;
            officeIcon->setVisible(false);
        }
        if (inOffice && !mainLayer->LookingAtCams){
            if (jumpscareTime > 0){
                jumpscareTime -= delta;
            }
            else{
                if (!killp){
                    killp = true;
                    std::vector<std::string> jumps;
                    for (int i = 0; i < 65; i++)
                    {
                        if (i < 9){
                            jumps.insert(jumps.end(), "creepypasta000"_spr + std::to_string((i + 1)) +".png");
                        }
                        else {
                            jumps.insert(jumps.end(), "creepypasta00"_spr + std::to_string((i + 1)) +".png");
                        }
                    }

                    std::string arr[65];
                    std::copy(jumps.begin(),jumps.end(),arr);

                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.0325f, 65, arr
                    ), "creepyPasta.mp3"_spr, false, false, false, 4.75f, 255, NULL, nullptr, true, true);
                    officeIcon->setVisible(false);
                }
            }
        }
    }
}

void npesta::OnOpportunity(){
    if (mainLayer->LookingAtCams){
        inOffice = true;
        jumpscareTime = 3 - (0.1f * _AILevel);
        officeIcon->setVisible(true);
    }
}