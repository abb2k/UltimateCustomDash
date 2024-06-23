#include "riot.h"

riot* riot::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new riot();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool riot::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    Cam06S1 = CCSprite::create("riotStage1.png"_spr);
    Cam06S1->setScale(2.275f);
    Cam06S1->setZOrder(3);
    Cam06S1->setVisible(false);
    mainLayer->Cam06->addChild(Cam06S1);

    Cam06Sbg = CCSprite::create("blackscreen.png"_spr);
    Cam06Sbg->setScale(2.5f);
    Cam06Sbg->setZOrder(1);
    Cam06Sbg->setVisible(false);
    mainLayer->Cam06->addChild(Cam06Sbg);

    Cam06S2 = CCSprite::create("riotStage2.png"_spr);
    Cam06S2->setScale(2.275f);
    Cam06S2->setZOrder(3);
    Cam06S2->setVisible(false);
    mainLayer->Cam06->addChild(Cam06S2);

    Cam06S3 = CCSprite::create("riotStage3.png"_spr);
    Cam06S3->setScale(2.275f);
    Cam06S3->setZOrder(3);
    Cam06S3->setVisible(false);
    mainLayer->Cam06->addChild(Cam06S3);

    _riot = CCSprite::create("riot.png"_spr);
    _riot->setScale(2);
    _riot->setVisible(false);
    mainLayer->Cam06->addChild(_riot);

    originalCSize = mainLayer->closeCurtainsB->getContentSize();

    scheduleUpdate();

    return true;
}

void riot::update(float delta){
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
        if (progression < 100){
            if (!pulse){
                pulse = true;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam06S1->setVisible(false);
            Cam06Sbg->setVisible(false);
            Cam06S2->setVisible(false);
            Cam06S3->setVisible(false);
            _riot->setVisible(false);
        }
        else if (progression >= 100 && progression < 200){
            if (pulse){
                pulse = false;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam06S1->setVisible(true);
            Cam06Sbg->setVisible(true);
            _riot->setVisible(true);
        }
        else if (progression >= 200 && progression < 300){
            if (!pulse){
                pulse = true;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam06S2->setVisible(true);
            Cam06S1->setVisible(false);
        }
        else if (progression >= 300 && progression < 400){
            if (pulse){
                pulse = false;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    mainLayer->CamStaticOpacity = 255;
                }
            }
            Cam06S2->setVisible(false);
            Cam06S3->setVisible(true);
        }
        else if (progression >= 400){
            if (!pulse){
                pulse = true;
                if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    mainLayer->CamStaticOpacity = 255;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.7f, 2, new std::string[]{
                            "riot.png"_spr,
                            "riot.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }
            }
            _riot->setVisible(false);
        }

        if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
            mainLayer->closeCurtainsB->setContentSize(originalCSize);
        }
        else{
            mainLayer->closeCurtainsB->setContentSize({0,0});
        }

        if (progression < 100){
            if (mainLayer->closeCurtainsB->getChildrenCount() == 0){
                if (mainLayer->getTouchOn(mainLayer->closeCurtainsB) && mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);
                    if (_AILevel != 0){
                        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                            0.7f, 2, new std::string[]{
                                "riot.png"_spr,
                                "riot.png"_spr,
                            }
                        ), "", false, false, false, 7);
                    }
                }
            }
            
        }
        else{
            if (mainLayer->closeCurtainsB->getChildrenCount() == 0){
                if (mainLayer->getTouchOn(mainLayer->closeCurtainsB) && mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera06){
                    progression = 0;
                    pulse = false;
                    FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);
                }
            }

        }
    }
}

void riot::OnOpportunity(){
    progression++;
}