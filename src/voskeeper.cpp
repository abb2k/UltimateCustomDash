#include "voskeeper.h"

voskeeper* voskeeper::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new voskeeper();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool voskeeper::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    Cont = CCNode::create();
    Cont->setZOrder(100);
    Cont->setAnchorPoint({0.5f,0.5f});
    Cont->setVisible(false);
    mainLayer->Canvas->addChild(Cont);

    LockGuy = CCSprite::create("vaultOfSeckeepr.png"_spr);
    LockGuy->setScale(0.3f);
    Cont->addChild(LockGuy);

    Lock = CCSprite::create("vosLock.png"_spr);
    Lock->setScale(0.3f);
    Lock->setZOrder(-1);
    Cont->addChild(Lock);

    

    scheduleUpdate();

    return true;
}

void voskeeper::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (opportunityTimer > 0){
            opportunityTimer -= delta;
            LockGuy->setPosition(Cont->getContentSize() / 2);
            Lock->setPosition({(Cont->getContentSize().width / 2), ((Cont->getContentSize().height / 2) - 12)});

            if (mainLayer->getTouchOn(Cont)){
                clickAmount++;
                FMODAudioEngine::sharedEngine()->playEffect("chestClick.mp3"_spr, 1.0f,1.0f,1.0f);
                LockGuy->runAction(CCSequence::create(CCScaleTo::create(0, 0.4f), CCEaseOut::create(CCScaleTo::create(0.3f, 0.3f), 2), nullptr));
            }
        }
        else{
            opportunityTimer = _opportunity;
            int oppCalc = 1 + (rand() % 22);
            if (_AILevel != 0 && _AILevel >= oppCalc){
                OnOpportunity();
            }
        }
        if (clickAmount >= totalClick){
            clickAmount = 0;
            Cont->setVisible(false);
            FMODAudioEngine::sharedEngine()->playEffect("Pop_Sharp_Quick_Small_Comical.mp3"_spr, 1.0f,1.0f,1.0f);
            Cont->setContentSize({0,0});
            Cont->retain();
            Cont->removeFromParent();
            mainLayer->Canvas->addChild(Cont);
            Cont->release();
        }
    }
}

void voskeeper::OnOpportunity(){
    int randomButton = rand() % 20;

    Cont->retain();
    Cont->removeFromParent();
    clickAmount = 0;
    switch (randomButton)
    {
        //cam01button
    case 0:
        mainLayer->Cam01ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam01ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam01ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam01ButtonOn->getScaleY());
        break;
        //cam02button
    case 1:
        mainLayer->Cam02ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam02ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam02ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam02ButtonOn->getScaleY());
        break;
        //cam03button
    case 2:
        mainLayer->Cam03ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam03ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam03ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam03ButtonOn->getScaleY());
        break;
        //cam04button
    case 3:
        mainLayer->Cam04ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam04ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam04ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam04ButtonOn->getScaleY());
        break;
        //cam05button
    case 4:
        mainLayer->Cam05ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam05ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam05ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam05ButtonOn->getScaleY());
        break;
        //cam06button
    case 5:
        mainLayer->Cam06ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam06ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam06ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam06ButtonOn->getScaleY());
        break;
        //cam07button
    case 6:
        mainLayer->Cam07ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam07ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam07ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam07ButtonOn->getScaleY());
        break;
        //cam08button
    case 7:
        mainLayer->Cam08ButtonCont->addChild(Cont);
        Cont->release();

        Cont->setPosition({0,0});
        Cont->setContentSize(mainLayer->Cam08ButtonOn->getContentSize());
        Cont->setScaleX(mainLayer->Cam08ButtonOn->getScaleX());
        Cont->setScaleY(mainLayer->Cam08ButtonOn->getScaleY());
        break;

    case 8:
        mainLayer->camSystem->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->camSystem->getContentSize() / 2);
        Cont->setContentSize(mainLayer->camSystem->getContentSize());
        Cont->setScaleX(mainLayer->camSystem->getScaleX());
        Cont->setScaleY(mainLayer->camSystem->getScaleY());
        break;

    case 9:
        mainLayer->ventSystem->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->ventSystem->getContentSize() / 2);
        Cont->setContentSize(mainLayer->ventSystem->getContentSize());
        Cont->setScaleX(mainLayer->ventSystem->getScaleX());
        Cont->setScaleY(mainLayer->ventSystem->getScaleY());
        break;

    case 10:
        mainLayer->ductSystem->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->ductSystem->getContentSize() / 2);
        Cont->setContentSize(mainLayer->ductSystem->getContentSize());
        Cont->setScaleX(mainLayer->ductSystem->getScaleX());
        Cont->setScaleY(mainLayer->ductSystem->getScaleY());
        break;

    case 11:
        mainLayer->cameraOverallUI->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->resetVentelation->getPosition());
        Cont->setContentSize(mainLayer->resetVentelation->getContentSize());
        Cont->setScaleX(mainLayer->resetVentelation->getScaleX());
        Cont->setScaleY(mainLayer->resetVentelation->getScaleY());
        break;

    case 12:
        mainLayer->musicBoxCont->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->windBoxOff->getPosition());
        Cont->setContentSize(mainLayer->windBoxOff->getContentSize());
        Cont->setScaleX(mainLayer->windBoxOff->getScaleX());
        Cont->setScaleY(mainLayer->windBoxOff->getScaleY());
        break;

    case 13:
        mainLayer->ChangeMusicButton->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->ChangeMusicButton->getContentSize() / 2);
        Cont->setContentSize(mainLayer->ChangeMusicButton->getContentSize());
        Cont->setScaleX(mainLayer->ChangeMusicButton->getScaleX());
        Cont->setScaleY(mainLayer->ChangeMusicButton->getScaleY());
        break;

    case 14:
        mainLayer->closeCurtainsB->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->closeCurtainsB->getContentSize() / 2);
        Cont->setContentSize(mainLayer->closeCurtainsB->getContentSize());
        Cont->setScaleX(mainLayer->closeCurtainsB->getScaleX());
        Cont->setScaleY(mainLayer->closeCurtainsB->getScaleY());
        break;

    case 15:
        mainLayer->ventSnareEmptyLeft->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->ventSnareEmptyLeft->getContentSize() / 2);
        Cont->setContentSize(mainLayer->ventSnareEmptyLeft->getContentSize());
        Cont->setScaleX(mainLayer->ventSnareEmptyLeft->getScaleX());
        Cont->setScaleY(mainLayer->ventSnareEmptyLeft->getScaleY());
        break;

    case 16:
        mainLayer->ventSnareEmptyTop->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->ventSnareEmptyTop->getContentSize() / 2);
        Cont->setContentSize(mainLayer->ventSnareEmptyTop->getContentSize());
        Cont->setScaleX(mainLayer->ventSnareEmptyTop->getScaleX());
        Cont->setScaleY(mainLayer->ventSnareEmptyTop->getScaleY());
        break;

    case 17:
        mainLayer->ventSnareEmptyRight->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->ventSnareEmptyRight->getContentSize() / 2);
        Cont->setContentSize(mainLayer->ventSnareEmptyRight->getContentSize());
        Cont->setScaleX(mainLayer->ventSnareEmptyRight->getScaleX());
        Cont->setScaleY(mainLayer->ventSnareEmptyRight->getScaleY());
        break;

    case 18:
        mainLayer->OpenDuctLeftB->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->OpenDuctLeftB->getContentSize() / 2);
        Cont->setContentSize(mainLayer->OpenDuctLeftB->getContentSize());
        Cont->setScaleX(mainLayer->OpenDuctLeftB->getScaleX());
        Cont->setScaleY(mainLayer->OpenDuctLeftB->getScaleY());
        break;

    case 19:
        mainLayer->OpenDuctRightB->addChild(Cont);
        Cont->release();

        Cont->setPosition(mainLayer->OpenDuctRightB->getContentSize() / 2);
        Cont->setContentSize(mainLayer->OpenDuctRightB->getContentSize());
        Cont->setScaleX(mainLayer->OpenDuctRightB->getScaleX());
        Cont->setScaleY(mainLayer->OpenDuctRightB->getScaleY());
        break;
        
    }

    Cont->setVisible(true);
}