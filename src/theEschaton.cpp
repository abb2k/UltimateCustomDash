#include "theEschaton.h"

theEschaton* theEschaton::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new theEschaton();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool theEschaton::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    turnedOff = CCSprite::create("echatonAsleep.png"_spr);
    turnedOff->setZOrder(9);
    turnedOff->setScale(1.3f);
    turnedOff->setVisible(false);
    mainLayer->World->addChild(turnedOff);

    turnedOn = CCSprite::create("echatonAwake.png"_spr);
    turnedOn->setZOrder(9);
    turnedOn->setScale(1.3f);
    turnedOn->setVisible(false);
    mainLayer->World->addChild(turnedOn);

    CCSize res = CCDirector::sharedDirector()->getWinSize();

    turnedOffTex = CCRenderTexture::create(res.width + 1, res.height + 1, turnedOff->getTexture()->getPixelFormat());
    turnedOffTex->setVisible(false);
    this->addChild(turnedOffTex);

    turnedOnTex = CCRenderTexture::create(res.width + 1, res.height + 1, turnedOn->getTexture()->getPixelFormat());
    turnedOnTex->setVisible(false);
    this->addChild(turnedOnTex);

    scheduleUpdate();

    return true;
}

void theEschaton::update(float delta){
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
        turnedOff->setPosition({mainLayer->desk->getPositionX(), mainLayer->desk->getPositionY() + 20});
        turnedOn->setPosition({mainLayer->desk->getPositionX(), mainLayer->desk->getPositionY() + 20});

        if (mainLayer->clicking && !mainLayer->oneTimeClick){
            if (inOffice && !mainLayer->LookingAtCams){
                if (!isTurnedOn){
                    if (mainLayer->getHoverSprite(turnedOff, turnedOffTex)){
                        mainLayer->oneTimeClick = true;
                        //if clicked while sleeping
                        turnedOff->setVisible(false);
                        if (!killplayer){
                            killplayer = true;
                            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                                1, 2, new std::string[]{
                                    "echatonAwake.png"_spr,
                                    "echatonAwake.png"_spr,
                                }
                            ), "explode_11.ogg"_spr, false, false, false, 2);
                        }
                    }
                }
                else{
                    if (mainLayer->getHoverSprite(turnedOn, turnedOnTex) && !avoiding){
                        mainLayer->oneTimeClick = true;
                        //if clicked while awake
                        mainLayer->FlashEffects(0.5f, callfunc_selector(theEschaton::avoded), this);
                        avoiding = true;
                    }
                }
            }
        }
    }
}

void theEschaton::avoded(){
    avoiding = false;
    turnedOn->setVisible(false);
    inOffice = false;
    isTurnedOn = false;
}

void theEschaton::OnOpportunity(){
    if (!inOffice){
        turnedOff->setVisible(true);
        if (!mainLayer->LookingAtCams){
            mainLayer->effectBlackscreenOpacity = 255;
        }
        inOffice = true;
    }
    else {
        if (!isTurnedOn){
            turnedOff->setVisible(false);
            turnedOn->setVisible(true);
            if (!mainLayer->LookingAtCams){
                mainLayer->effectBlackscreenOpacity = 255;
            }
            isTurnedOn = true;
        }
        else if (isTurnedOn && !avoiding){
            turnedOn->setVisible(false);
            if (!killplayer){
                killplayer = true;
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    1, 2, new std::string[]{
                        "echatonAwake.png"_spr,
                        "echatonAwake.png"_spr,
                    }
                ), "explode_11.ogg"_spr, false, false, false, 2);
            }
        }
    }
}