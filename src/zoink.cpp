#include "zoink.h"

zoink* zoink::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new zoink();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool zoink::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    dtext = CCTextFieldTTF::create("blip.mp3"_spr, "chatFont.fnt", 10);
    dtext->setVisible(false);
    this->addChild(dtext);

    spike = CCSprite::create("FIXEDSPIKE.png"_spr);
    mainLayer->World->addChild(spike);
    spike->setOpacity(0);
    spike->setZOrder(15);

    CCSize res = CCDirector::sharedDirector()->getWinSize();

    renderTexture = CCRenderTexture::create(res.width + 1, res.height + 1, spike->getTexture()->getPixelFormat());
    renderTexture->setVisible(false);
    this->addChild(renderTexture);

    movePosition();

    scheduleUpdate();

    return true;
}

void zoink::update(float delta){
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
        bool isHitting = false;

        if (mainLayer->getHoverSprite(spike, renderTexture)){
            isHitting = true;
        }

        if (isHitting){
            if (spikeOpacity < 255 && !mainLayer->LookingAtCams){
                spikeOpacity += delta * _AILevel * 20;
                if (spikeOpacity > 255 && !jumped){
                    spikeOpacity = 0;
                    jumped = true;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.02f, 8, new std::string[]{
                            "zoinkj1.png"_spr,
                            "zoinkj2.png"_spr,
                            "zoinkj3.png"_spr,
                            "zoinkj4.png"_spr,
                            "zoinkj5.png"_spr,
                            "zoinkj6.png"_spr,
                            "zoinkj7.png"_spr,
                            "zoinkj8.png"_spr,
                        }, 3),
                        "ibeattidalwave.mp3"_spr, false, false, false
                    );

                }
            }
        }
        else {
            if (spikeOpacity > 1){
                spikeOpacity -= delta * 50;
                if (spikeOpacity < 1){
                    spikeOpacity = 1;
                }
            }
        }

        spike->setOpacity((int)spikeOpacity);
    }
}

void zoink::OnOpportunity(){
    if (spikeOpacity <= 1){
        movePosition();
    }
}

void zoink::movePosition(){
    int posGotten = rand() % 6;

    positions oldPosition = currentPos;
    positions recevedPos = positions::pos1;

    switch (posGotten)
    {
    case 0:
        recevedPos = positions::pos1;
        spike->setPosition({-18, 129});
        spike->setRotation(0);
        spike->setScale(9.15f);
        break;

    case 1:
        recevedPos = positions::pos2;
        spike->setPosition({65, 276});
        spike->setRotation(74);
        spike->setScale(10.15f);
        break;

    case 2:
        recevedPos = positions::pos3;
        spike->setPosition({356, 228});
        spike->setRotation(278);
        spike->setScale(11.325f);
        break;

    case 3:
        recevedPos = positions::pos4;
        spike->setPosition({548, 269});
        spike->setRotation(-60);
        spike->setScale(9.25f);
        break;

    case 4:
        recevedPos = positions::pos5;
        spike->setPosition({608, 67});
        spike->setRotation(23);
        spike->setScale(11.125f);
        break;

    case 5:
        recevedPos = positions::pos6;
        spike->setPosition({278, 124});
        spike->setRotation(0);
        spike->setScale(11.125f);
        break;
    }
    currentPos = recevedPos;

    // pos1 - position: x: -18 y: 129 , rotation: 0, scale: 9.15f
    // pos2 - position: x: 65 y: 276, rotation: 74, scale: 10.15f
    // pos3 - position: x: 356 y: 228 , rotation: 278 , scale: 11.325f
    // pos4 - position: x: 548 y: 269 , rotation: -60 , scale: 9.25f
    // pos5 - position: x: 608 y: 67 , rotation: 23 , scale: 11.125f
    // pos6 - position: x: 278 y: 124 , rotation: 0 , scale: 11.125f
}