#include "basementMonster.h"

basementMonster* basementMonster::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new basementMonster();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool basementMonster::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    monster = CCSprite::create("basementMBody.png"_spr);
    monster->setPosition({457, 94});
    monster->setVisible(false);
    mainLayer->World->addChild(monster);

    eyesContainer = CCNode::create();
    eyesContainer->setPosition({62, 53});
    monster->addChild(eyesContainer);

    eyeLeft = CCSprite::create("basementMEyeLeft.png"_spr);
    eyesContainer->addChild(eyeLeft);

    eyeRight = CCSprite::create("basementMEyeRight.png"_spr);
    eyesContainer->addChild(eyeRight);

    /*
    --locations--
    (layout: posX, PosY - RotX, RotY. scale is always 1. at least half of the cams and every cam has to have at least 2 locations)

    -Cam02-
    108, -100 - 22, 36
    -176, -92 - 58, 66

    -Cam03-
    -7, -146 - 56, 43
    34, 91 - -70, -56

    -Cam05-
    64, -120 - -27, -45
    -264, 146 - -243, -265

    -Cam06-
    -267, -109 - 25, 34
    262, 112 - 22, 27

    -Cam08-
    17, -54 - 55, 23
    -286, -107 - -29, -35
    
    */

    scheduleUpdate();

    return true;
}

void basementMonster::update(float delta){
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

        if (InOffice){
            if (mainLayer->getTouchOnSprite(KeyBlue, keyBlueTex) && KeyBlue->isVisible()){
                bool hasBlue = false;
                for (int i = 0; i < 2; i++)
                {
                    if (eyesColors[i] == eyeColor::blue){
                        hasBlue = true;
                    }
                }

                if (hasBlue){
                    keysFound++;
                    KeyBlue->setVisible(false);
                    mainLayer->CamStaticOpacity = 255;
                }
                else{
                    kill();
                }
                
            }

            if (mainLayer->getTouchOnSprite(KeyGreen, keyGreenTex) && KeyGreen->isVisible()){
                bool hasGreen = false;
                for (int i = 0; i < 2; i++)
                {
                    if (eyesColors[i] == eyeColor::green){
                        hasGreen = true;
                    }
                }

                if (hasGreen){
                    keysFound++;
                    KeyGreen->setVisible(false);
                    mainLayer->CamStaticOpacity = 255;
                }
                else{
                    kill();
                }
            }

            if (mainLayer->getTouchOnSprite(KeyOrange, keyOrangeTex) && KeyOrange->isVisible()){
                bool hasOrange = false;
                for (int i = 0; i < 2; i++)
                {
                    if (eyesColors[i] == eyeColor::orange){
                        hasOrange = true;
                    }
                }

                if (hasOrange){
                    keysFound++;
                    KeyOrange->setVisible(false);
                    mainLayer->CamStaticOpacity = 255;
                }
                else{
                    kill();
                }
            }

            if (keysFound == 2){
                keysFound = 0;
                InOffice = false;
                monster->setVisible(false);
                KeyBlue->removeMeAndCleanup();
                keyBlueTex->removeMeAndCleanup();
                KeyGreen->removeMeAndCleanup();
                keyGreenTex->removeMeAndCleanup();
                KeyOrange->removeMeAndCleanup();
                keyOrangeTex->removeMeAndCleanup();
            }
        }
    }
}

void basementMonster::OnOpportunity(){
    if (!InOffice){
        InOffice = true;

        if (!mainLayer->LookingAtCams){
            mainLayer->effectBlackscreenOpacity = 255;
        }

        //randomize eye colors
        int randomColor = rand() % 3;

        eyesColors[0] = (eyeColor)randomColor;

        int randomColor2 = -1;

        if (randomColor == 0){
            randomColor2 = 1 + (rand() % 2);
        }
        else if (randomColor == 1){
            randomColor2 = rand() % 2;

            if (randomColor2 == 1){
                randomColor2 = 2;
            }
        }
        else if (randomColor == 2){
            randomColor2 = rand() % 2;
        }

        eyesColors[1] = (eyeColor)randomColor2;

        for (int i = 0; i < 2; i++)
        {
            if (i == 0){
                switch (eyesColors[i])
                {
                case eyeColor::blue:
                    //blue
                    eyeLeft->setColor({0, 187, 255});
                    break;

                case eyeColor::green:
                    //green
                    eyeLeft->setColor({0, 238, 0});
                    break;

                case eyeColor::orange:
                    //orange
                    eyeLeft->setColor({255, 170, 0});
                    break;
                }
            }
            else if (i == 1){
                switch (eyesColors[i])
                {
                case eyeColor::blue:
                    //blue
                    eyeRight->setColor({0, 187, 255});
                    break;

                case eyeColor::green:
                    //green
                    eyeRight->setColor({0, 238, 0});
                    break;

                case eyeColor::orange:
                    //orange
                    eyeRight->setColor({255, 170, 0});
                    break;
                }
            }
        }

        monster->setVisible(true);

        //randomize key positions

        int randomPositionBlue = rand() % 10;

        int randomPositionGreen = rand() % 9;

        int randomPositionOrange = rand() % 8;

        if (randomPositionGreen >= randomPositionBlue){
            randomPositionGreen++;
        }
        if (randomPositionOrange >= randomPositionGreen){
            randomPositionOrange++;
        }
        if (randomPositionOrange >= randomPositionBlue){
            randomPositionOrange++;
        }

        KeyBlue = CCSprite::create("demonKeyBlue.png"_spr);
        switch (randomPositionBlue){
            case 0:
                KeyBlue->setPosition({108, -100});
                KeyBlue->setRotationX(22);
                KeyBlue->setRotationY(36);
                mainLayer->Cam02->addChild(KeyBlue);
                break;

            case 1:
                KeyBlue->setPosition({-176, -92});
                KeyBlue->setRotationX(58);
                KeyBlue->setRotationY(66);
                mainLayer->Cam02->addChild(KeyBlue);
                break;

            case 2:
                KeyBlue->setPosition({-7, -146});
                KeyBlue->setRotationX(56);
                KeyBlue->setRotationY(43);
                mainLayer->Cam03->addChild(KeyBlue);
                break;

            case 3:
                KeyBlue->setPosition({34, 91});
                KeyBlue->setRotationX(-70);
                KeyBlue->setRotationY(-56);
                mainLayer->Cam03->addChild(KeyBlue);
                break;

            case 4:
                KeyBlue->setPosition({64, -120});
                KeyBlue->setRotationX(-27);
                KeyBlue->setRotationY(-45);
                mainLayer->Cam05->addChild(KeyBlue);
                break;

            case 5:
                KeyBlue->setPosition({-264, 146});
                KeyBlue->setRotationX(-243);
                KeyBlue->setRotationY(-265);
                mainLayer->Cam05->addChild(KeyBlue);
                break;

            case 6:
                KeyBlue->setPosition({-267, -109});
                KeyBlue->setRotationX(25);
                KeyBlue->setRotationY(34);
                mainLayer->Cam06->addChild(KeyBlue);
                break;

            case 7:
                KeyBlue->setPosition({262, 112});
                KeyBlue->setRotationX(22);
                KeyBlue->setRotationY(27);
                mainLayer->Cam06->addChild(KeyBlue);
                break;

            case 8:
                KeyBlue->setPosition({17, -54});
                KeyBlue->setRotationX(55);
                KeyBlue->setRotationY(23);
                mainLayer->Cam08->addChild(KeyBlue);
                break;

            case 9:
                KeyBlue->setPosition({-286, -107});
                KeyBlue->setRotationX(-29);
                KeyBlue->setRotationY(-35);
                mainLayer->Cam08->addChild(KeyBlue);
                break;
        }

        KeyGreen = CCSprite::create("demonKeyGreen.png"_spr);
        switch (randomPositionGreen){
            case 0:
                KeyGreen->setPosition({108, -100});
                KeyGreen->setRotationX(22);
                KeyGreen->setRotationY(36);
                mainLayer->Cam02->addChild(KeyGreen);
                break;

            case 1:
                KeyGreen->setPosition({-176, -92});
                KeyGreen->setRotationX(58);
                KeyGreen->setRotationY(66);
                mainLayer->Cam02->addChild(KeyGreen);
                break;

            case 2:
                KeyGreen->setPosition({-7, -146});
                KeyGreen->setRotationX(56);
                KeyGreen->setRotationY(43);
                mainLayer->Cam03->addChild(KeyGreen);
                break;

            case 3:
                KeyGreen->setPosition({34, 91});
                KeyGreen->setRotationX(-70);
                KeyGreen->setRotationY(-56);
                mainLayer->Cam03->addChild(KeyGreen);
                break;

            case 4:
                KeyGreen->setPosition({64, -120});
                KeyGreen->setRotationX(-27);
                KeyGreen->setRotationY(-45);
                mainLayer->Cam05->addChild(KeyGreen);
                break;

            case 5:
                KeyGreen->setPosition({-264, 146});
                KeyGreen->setRotationX(-243);
                KeyGreen->setRotationY(-265);
                mainLayer->Cam05->addChild(KeyGreen);
                break;

            case 6:
                KeyGreen->setPosition({-267, -109});
                KeyGreen->setRotationX(25);
                KeyGreen->setRotationY(34);
                mainLayer->Cam06->addChild(KeyGreen);
                break;

            case 7:
                KeyGreen->setPosition({262, 112});
                KeyGreen->setRotationX(22);
                KeyGreen->setRotationY(27);
                mainLayer->Cam06->addChild(KeyGreen);
                break;

            case 8:
                KeyGreen->setPosition({17, -54});
                KeyGreen->setRotationX(55);
                KeyGreen->setRotationY(23);
                mainLayer->Cam08->addChild(KeyGreen);
                break;

            case 9:
                KeyGreen->setPosition({-286, -107});
                KeyGreen->setRotationX(-29);
                KeyGreen->setRotationY(-35);
                mainLayer->Cam08->addChild(KeyGreen);
                break;
        }

        KeyOrange = CCSprite::create("demonKeyOrange.png"_spr);
        switch (randomPositionOrange){
            case 0:
                KeyOrange->setPosition({108, -100});
                KeyOrange->setRotationX(22);
                KeyOrange->setRotationY(36);
                mainLayer->Cam02->addChild(KeyOrange);
                break;

            case 1:
                KeyOrange->setPosition({-176, -92});
                KeyOrange->setRotationX(58);
                KeyOrange->setRotationY(66);
                mainLayer->Cam02->addChild(KeyOrange);
                break;

            case 2:
                KeyOrange->setPosition({-7, -146});
                KeyOrange->setRotationX(56);
                KeyOrange->setRotationY(43);
                mainLayer->Cam03->addChild(KeyOrange);
                break;

            case 3:
                KeyOrange->setPosition({34, 91});
                KeyOrange->setRotationX(-70);
                KeyOrange->setRotationY(-56);
                mainLayer->Cam03->addChild(KeyOrange);
                break;

            case 4:
                KeyOrange->setPosition({64, -120});
                KeyOrange->setRotationX(-27);
                KeyOrange->setRotationY(-45);
                mainLayer->Cam05->addChild(KeyOrange);
                break;

            case 5:
                KeyOrange->setPosition({-264, 146});
                KeyOrange->setRotationX(-243);
                KeyOrange->setRotationY(-265);
                mainLayer->Cam05->addChild(KeyOrange);
                break;

            case 6:
                KeyOrange->setPosition({-267, -109});
                KeyOrange->setRotationX(25);
                KeyOrange->setRotationY(34);
                mainLayer->Cam06->addChild(KeyOrange);
                break;

            case 7:
                KeyOrange->setPosition({262, 112});
                KeyOrange->setRotationX(22);
                KeyOrange->setRotationY(27);
                mainLayer->Cam06->addChild(KeyOrange);
                break;

            case 8:
                KeyOrange->setPosition({17, -54});
                KeyOrange->setRotationX(55);
                KeyOrange->setRotationY(23);
                mainLayer->Cam08->addChild(KeyOrange);
                break;

            case 9:
                KeyOrange->setPosition({-286, -107});
                KeyOrange->setRotationX(-29);
                KeyOrange->setRotationY(-35);
                mainLayer->Cam08->addChild(KeyOrange);
                break;
        }
    
        CCSize res = CCDirector::sharedDirector()->getWinSize();

        keyBlueTex = CCRenderTexture::create(res.width + 1, res.height + 1, KeyBlue->getTexture()->getPixelFormat());
        keyBlueTex->setVisible(false);
        this->addChild(keyBlueTex);

        keyGreenTex = CCRenderTexture::create(res.width + 1, res.height + 1, KeyGreen->getTexture()->getPixelFormat());
        keyGreenTex->setVisible(false);
        this->addChild(keyGreenTex);

        keyOrangeTex = CCRenderTexture::create(res.width + 1, res.height + 1, KeyOrange->getTexture()->getPixelFormat());
        keyOrangeTex->setVisible(false);
        this->addChild(keyOrangeTex);
    }
    else {
        kill();
    }
}

void basementMonster::kill(){
    if (!killp){
        killp = true;

        mainLayer->Jumpscare(mainLayer->CreateAnimAction(
            0.025f, 15, new std::string[]{
                "bmJ0001.png"_spr,
                "bmJ0002.png"_spr,
                "bmJ0003.png"_spr,
                "bmJ0004.png"_spr,
                "bmJ0005.png"_spr,
                "bmJ0006.png"_spr,
                "bmJ0007.png"_spr,
                "bmJ0008.png"_spr,
                "bmJ0009.png"_spr,
                "bmJ0010.png"_spr,
                "bmJ0011.png"_spr,
                "bmJ0012.png"_spr,
                "bmJ0013.png"_spr,
                "bmJ0014.png"_spr,
                "bmJ0015.png"_spr,
            }, 3
        ), "explode_11.mp3"_spr, false, false, false);
    }
}