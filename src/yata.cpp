#include "yata.h"

yata* yata::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new yata();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool yata::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    yataS = CCSprite::create("birdddddd.png"_spr);
    yataS->setPosition({720, (150 + posMoved)});
    yataS->setScale(0.65f);
    yataS->setZOrder(7);
    mainLayer->World->addChild(yataS);

    CCRepeatForever* r = CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(1, {0, (posMoved * 2)}), 2), CCEaseInOut::create(CCMoveBy::create(1, {0, (-posMoved * 2)}), 2), nullptr));
    yataS->runAction(r);

    CCSize res = CCDirector::sharedDirector()->getWinSize();

    renderTexture = CCRenderTexture::create(res.width + 1, res.height + 1, yataS->getTexture()->getPixelFormat());
    renderTexture->setVisible(false);
    this->addChild(renderTexture);

    scheduleUpdate();

    return true;
}

void yata::update(float delta){
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

        if (mainLayer->getTouchOnSprite(yataS, renderTexture)){
            if (yataS->getColor().r == 255){
                //red
                yataS->setVisible(false);
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    1, 2, new std::string[]{
                        "birdddddd.png"_spr,
                        "birdddddd.png"_spr,
                    }
                ), "explode_11.ogg"_spr, false, false, false, 3);
            }
            else {
                //green
                yataS->setVisible(false);
                clickedGreen = true;
            }
        }
    }
}

void yata::OnOpportunity(){
    int randomcol = rand() % 2;
    if (randomcol == 0){
        yataS->setColor({255, 0, 0});
    }
    else if (randomcol == 1){
        yataS->setColor({0, 255, 0});
    }

    int randomdir = rand() % 2;
    if (randomdir == 0){
        flyToRight = true;
    }
    else if (randomdir == 1){
        flyToRight = false;
    }

    if (flyToRight){
        yataS->setScaleX(-0.65f);

        yataS->setPosition({-140, (150 + posMoved)});
        CCPoint p = {720, (150 + posMoved)};
        auto c = CCSequence::create(CCMoveTo::create(6, p), CCCallFunc::create(this, callfunc_selector(yata::reahcedEnd)), nullptr);
        yataS->runAction(c);
        
    }
    else {
        yataS->setScaleX(0.65f);

        yataS->setPosition({720, (150 + posMoved)});
        CCPoint p = {-140, (150 + posMoved)};
        auto c = CCSequence::create(CCMoveTo::create(6, p), CCCallFunc::create(this, callfunc_selector(yata::reahcedEnd)), nullptr);
        yataS->runAction(c);
    }
}

void yata::reahcedEnd(){
    if (yataS->getColor().g == 255) {
        //green
        yataS->setVisible(true);
        if (!clickedGreen){
            //kill
            mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                1, 2, new std::string[]{
                    "birdddddd.png"_spr,
                    "birdddddd.png"_spr,
                }
            ), "explode_11.ogg"_spr, false, false, false, 3);
        }
    }
    clickedGreen = false;
}