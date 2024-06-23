#include "shopkeeper.h"

shopkeeper* shopkeeper::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new shopkeeper();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool shopkeeper::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    asleep = CCSprite::create("shopkAsleep.png"_spr);
    asleep->setZOrder(5);
    asleep->setPosition({407, 117});
    asleep->setScale(3);
    mainLayer->World->addChild(asleep);

    Wake = CCSprite::create("shopkAwake.png"_spr);
    Wake->setZOrder(5);
    Wake->setPosition({407, 117});
    Wake->setScale(3);
    Wake->setVisible(false);
    mainLayer->World->addChild(Wake);

    pay = CCSprite::create("PayCoins.png"_spr);
    pay->setZOrder(5);
    pay->setScale(1.25f);
    pay->setVisible(false);
    pay->setPosition({401, 200});
    mainLayer->World->addChild(pay);

    if (_AILevel == 0){
        asleep->setVisible(false);
    }

    mainLayer->PreloadImages(std::vector<std::string>{
        "skJu0001.png"_spr,
        "skJu0002.png"_spr,
        "skJu0003.png"_spr,
        "skJu0004.png"_spr,
        "skJu0005.png"_spr,
        "skJu0006.png"_spr,
        "skJu0007.png"_spr,
        "skJu0008.png"_spr,
        "skJu0009.png"_spr,
        "skJu0010.png"_spr,
        "skJu0011.png"_spr,
        "skJu0012.png"_spr,
        "skJu0013.png"_spr,
        "skJu0014.png"_spr,
        "skJu0015.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void shopkeeper::dialogClosed(DialogLayer* d){

}

void shopkeeper::update(float delta){
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
        if (awake){
            if (killTimer > 0){
                killTimer -= delta;

                if (killTimer <= ((15 / 4) * 3) && killTimer > ((15 / 4) * 2) && !dialogtest){
                    dialogtest = true;
                    if (mainLayer->currSpacialMode != CNGameLayer::SpacialMode::Heater){
                        removeDialog();
                        createKeeperDialog("Please Deposit 8 Coins.", SKface::calm);
                    }
                }
                else if (killTimer <= ((15 / 4) * 2) && killTimer > ((15 / 4) * 1) && dialogtest){
                    dialogtest = false;
                    if (mainLayer->currSpacialMode != CNGameLayer::SpacialMode::Heater){
                        removeDialog();
                        createKeeperDialog("Please Deposit 8 Coins!", SKface::pissed);
                    }
                }
                else if (killTimer <= ((15 / 4) * 1) && killTimer > ((15 / 4) * 0) && !dialogtest){
                    dialogtest = true;
                    if (mainLayer->currSpacialMode != CNGameLayer::SpacialMode::Heater){
                        removeDialog();
                        createKeeperDialog("Please Deposit 8 Coins!", SKface::pissed);
                    }
                }
            }
            else {
                removeDialog();
                killTimer = 100;
                awake = false;
                asleep->setVisible(false);
                Wake->setVisible(false);
                pay->setVisible(false);
                mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                    0.03f, 15, new std::string[]{
                        "skJu0001.png"_spr,
                        "skJu0002.png"_spr,
                        "skJu0003.png"_spr,
                        "skJu0004.png"_spr,
                        "skJu0005.png"_spr,
                        "skJu0006.png"_spr,
                        "skJu0007.png"_spr,
                        "skJu0008.png"_spr,
                        "skJu0009.png"_spr,
                        "skJu0010.png"_spr,
                        "skJu0011.png"_spr,
                        "skJu0012.png"_spr,
                        "skJu0013.png"_spr,
                        "skJu0014.png"_spr,
                        "skJu0015.png"_spr,
                    }, 3
                ), "magicEx.mp3"_spr, false, false, false);
            }
            if (mainLayer->currSpacialMode == CNGameLayer::SpacialMode::Heater){
                if (!heaterDialogeLock){
                    heaterDialogeLock = true;
                    removeDialog();
                    createKeeperDialog("Yo4 aR3 Tr7Ing to tR1ck me", SKface::pissed);
                }
                if (stopTimer > 0){
                    stopTimer -= delta;

                    if (glitchTimer > 0){
                        glitchTimer -= delta;
                    }
                    else {
                        glitchTimer = mainLayer->randomFloat(0.4f, 1.2f);
                        currGSprite = !currGSprite;
                        asleep->setVisible(currGSprite);
                        Wake->setVisible(!currGSprite);
                    }
                }
                else {
                    stopTimer = 4;
                    awake = false;
                    heaterDialogeLock = false;
                    removeDialog();
                    createKeeperDialog("thank you, for Depositing 8 Coins.", SKface::calm);
                    asleep->runAction(CCSequence::create(CCDelayTime::create(4), CCCallFunc::create(this, callfunc_selector(shopkeeper::removeDialog)), nullptr));
                    asleep->setVisible(true);
                    Wake->setVisible(false);
                    pay->setVisible(false);
                }
            }
            else {
                currGSprite = false;
                if (heaterDialogeLock){
                    heaterDialogeLock = false;
                    if (killTimer <= 15 && killTimer > ((15 / 4) * 2)){
                        removeDialog();
                        createKeeperDialog("Please Deposit 8 Coins.", SKface::calm);
                    }
                    else {
                        removeDialog();
                        createKeeperDialog("Please Deposit 8 Coins!", SKface::pissed);
                    }
                }
                asleep->setVisible(currGSprite);
                Wake->setVisible(!currGSprite);
            }
            if (mainLayer->fazCoins >= 8 && mainLayer->getTouchOn(pay)){
                mainLayer->fazCoins -= 8;
                awake = false;
                removeDialog();
                createKeeperDialog("thank you, for Depositing 8 Coins.", SKface::calm);
                asleep->runAction(CCSequence::create(CCDelayTime::create(4), CCCallFunc::create(this, callfunc_selector(shopkeeper::removeDialog)), nullptr));
                asleep->setVisible(true);
                Wake->setVisible(false);
                pay->setVisible(false);
                FMODAudioEngine::sharedEngine()->playEffect("buyItem03.mp3"_spr, 1.0f,1.0f,1.0f);
            }
        }
    }
}

void shopkeeper::OnOpportunity(){
    if (!awake){
        awake = true;
        asleep->setVisible(false);
        Wake->setVisible(true);
        pay->setVisible(true);
        killTimer = 15;
        if (mainLayer->currSpacialMode != CNGameLayer::SpacialMode::Heater){
            createKeeperDialog("Please Deposit 8 Coins.", SKface::calm);
        }
    }
}

void shopkeeper::createKeeperDialog(std::string text, SKface emotion){
    int portrait = -1;
    if (emotion == SKface::calm){
        portrait = 5;
    }
    else {
        portrait = 6;
    }
    std::string title = "Shopkeeper";

    CCArray* arr = CCArray::create();
        
    AttemptAtReversingDialogObject* d = AttemptAtReversingDialogObject::create(title, text, portrait, 1.0f, true, {255,255,255});
    arr->addObject(d);
    Dialog = DialogLayer::createDialogLayer(nullptr, arr, 1);
    Dialog->setZOrder(44);
    Dialog->setPosition({-395, -265});
    Dialog->setScale(0.45f);
    Dialog->setOpacity(0);
    Dialog->setTouchEnabled(false);
    Dialog->setKeyboardEnabled(false);
    Dialog->setKeypadEnabled(false);
    mainLayer->Canvas->addChild(Dialog);
    Dialog->animateInRandomSide();
}

void shopkeeper::removeDialog(){
    if (Dialog != nullptr){
        Dialog->removeMeAndCleanup();
        Dialog = nullptr;
    }
}