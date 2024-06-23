#include "plushAnimatronics.h"

plushAnimatronics* plushAnimatronics::create(CNGameLayer* gameLayer, float opportunity, int CotAILevel, int MindcapAILevel, int MichiAILevel) {
    auto ret = new plushAnimatronics();
    if (ret && ret->init(gameLayer, opportunity, CotAILevel, MindcapAILevel, MichiAILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool plushAnimatronics::init(CNGameLayer* gameLayer, float opportunity, int CotAILevel, int MindcapAILevel, int MichiAILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _CotAILevel = CotAILevel;
    _MindcapAILevel = MindcapAILevel;
    _MichiAILevel = MichiAILevel;

    cot = CCSprite::create("cotFace.png"_spr);
    cot->setVisible(false);
    cot->setPosition({-104, 23});
    cot->setScale(1.5f);
    cot->setRotationX(1);
    cot->setRotationY(-10);
    mainLayer->Cam02->addChild(cot);

    michi = CCSprite::create("michigun.png"_spr);
    michi->setVisible(false);
    mainLayer->Cam02->addChild(michi);

    mindcap = CCSprite::create("mindcap.png"_spr);
    mindcap->setVisible(false);
    mainLayer->Cam02->addChild(mindcap);

    ElderECost = CotAILevel * 2;
    MindcapPlushCost = MindcapAILevel * 2;
    TripleCost = MichiAILevel * 2;

    int randomNum = rand() % 3;
    int rand1 = rand() % 2;
    int rand2 = 0;

    order.insert(order.begin(), (plushes)randomNum);

    if (randomNum <= rand1){
        rand1++;
    }

    order.insert(order.begin(), (plushes)rand1);

    bool foundFirst = false;
    if (randomNum <= rand2){
        rand2++;
        foundFirst = true;
    }

    if (rand1 <= rand2){
        rand2++;
    }

    if (randomNum <= rand2 && !foundFirst){
        rand2++;
    }

    order.insert(order.begin(), (plushes)rand2);

    if (MindcapAILevel != 0){
        mindcapPlushText = CCLabelBMFont::create(std::to_string(MindcapPlushCost).c_str(), "clickteamMedium.fnt"_spr);
        mindcapPlushText->setPosition({-109.5f, -44});
        mindcapPlushText->setColor({ 35, 35, 35 });
        mainLayer->Cam07->addChild(mindcapPlushText);

        mindcapPlushTextBuyButtton = CCSprite::create("buyButton.png"_spr);
        mindcapPlushTextBuyButtton->setPosition({-111, -61});
        mainLayer->Cam07->addChild(mindcapPlushTextBuyButtton);
    }

    if (CotAILevel != 0){
        boughtElderEText = CCLabelBMFont::create(std::to_string(ElderECost).c_str(), "clickteamMedium.fnt"_spr);
        boughtElderEText->setPosition({-153, 47});
        boughtElderEText->setColor({ 35, 35, 35 });
        mainLayer->Cam07->addChild(boughtElderEText);

        boughtElderETextBuyButtton = CCSprite::create("buyButton.png"_spr);
        boughtElderETextBuyButtton->setPosition({-154, 30});
        mainLayer->Cam07->addChild(boughtElderETextBuyButtton);
    }

    if (MichiAILevel != 0){
        boughtTripleText = CCLabelBMFont::create(std::to_string(TripleCost).c_str(), "clickteamMedium.fnt"_spr);
        boughtTripleText->setPosition({-70, 46});
        boughtTripleText->setColor({ 35, 35, 35 });
        mainLayer->Cam07->addChild(boughtTripleText);

        boughtTripleTextBuyButtton = CCSprite::create("buyButton.png"_spr);
        boughtTripleTextBuyButtton->setPosition({-72, 29});
        mainLayer->Cam07->addChild(boughtTripleTextBuyButtton);
    }

    mainLayer->PreloadImages(std::vector<std::string>{
        "cotKJ0001.png"_spr,
        "cotKJ0002.png"_spr,
        "cotKJ0003.png"_spr,
        "cotKJ0004.png"_spr,
        "cotKJ0005.png"_spr,
        "cotKJ0006.png"_spr,
        "cotKJ0007.png"_spr,
        "cotKJ0008.png"_spr,
        "cotKJ0009.png"_spr,
        "cotKJ0010.png"_spr,
        "cotKJ0011.png"_spr,
        "cotKJ0012.png"_spr,
        "cotKJ0013.png"_spr,
        "cotKJ0014.png"_spr,
        "cotKJ0015.png"_spr,
        "cotKJ0016.png"_spr,
        "cotKJ0017.png"_spr,
        "cotKJ0018.png"_spr,
        "cotKJ0019.png"_spr,
        "cotKJ0020.png"_spr,
        "cotKJ0021.png"_spr,
        "cotKJ0022.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void plushAnimatronics::update(float delta){
    if (mainLayer->NIGHTSTARTED){
        if (opportunityTimer > 0){
            opportunityTimer -= delta;
        }
        else{
            opportunityTimer = _opportunity;
            OnOpportunity();
        }

        if (_MindcapAILevel != 0 && !boughtMindcapPlush){
            if (mainLayer->getTouchOn(mindcapPlushTextBuyButtton)){
                if (mainLayer->fazCoins >= MindcapPlushCost){
                    mainLayer->fazCoins -= MindcapPlushCost;
                    boughtMindcapPlush = true;
                    mindcapPlushTextBuyButtton->setVisible(false);
                    FMODAudioEngine::sharedEngine()->playEffect("reg2.mp3"_spr, 1.0f,1.0f,1.0f);
                }
            }
        }
        if (_CotAILevel != 0 && !boughtElderE){
            if (mainLayer->getTouchOn(boughtElderETextBuyButtton)){
                if (mainLayer->fazCoins >= ElderECost){
                    mainLayer->fazCoins -= ElderECost;
                    boughtElderE = true;
                    boughtElderETextBuyButtton->setVisible(false);
                    FMODAudioEngine::sharedEngine()->playEffect("reg2.mp3"_spr, 1.0f,1.0f,1.0f);
                }
            }
        }
        if (_MichiAILevel != 0 && !boughtTriple){
            if (mainLayer->getTouchOn(boughtTripleTextBuyButtton)){
                if (mainLayer->fazCoins >= TripleCost){
                    mainLayer->fazCoins -= TripleCost;
                    boughtTriple = true;
                    boughtTripleTextBuyButtton->setVisible(false);
                    FMODAudioEngine::sharedEngine()->playEffect("reg2.mp3"_spr, 1.0f,1.0f,1.0f);
                }
            }
        }

        if (saftyTimer > 0){
            saftyTimer -= delta;
        }
        else {
            if (!saftyLock){
                saftyLock = true;
                if (cotAppeared && !boughtElderE){
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.03f, 22, new std::string[]{
                            "cotKJ0001.png"_spr,
                            "cotKJ0002.png"_spr,
                            "cotKJ0003.png"_spr,
                            "cotKJ0004.png"_spr,
                            "cotKJ0005.png"_spr,
                            "cotKJ0006.png"_spr,
                            "cotKJ0007.png"_spr,
                            "cotKJ0008.png"_spr,
                            "cotKJ0009.png"_spr,
                            "cotKJ0010.png"_spr,
                            "cotKJ0011.png"_spr,
                            "cotKJ0012.png"_spr,
                            "cotKJ0013.png"_spr,
                            "cotKJ0014.png"_spr,
                            "cotKJ0015.png"_spr,
                            "cotKJ0016.png"_spr,
                            "cotKJ0017.png"_spr,
                            "cotKJ0018.png"_spr,
                            "cotKJ0019.png"_spr,
                            "cotKJ0020.png"_spr,
                            "cotKJ0021.png"_spr,
                            "cotKJ0022.png"_spr,
                        }, 2
                    ), "explode_11.mp3"_spr, false, false, false);
                }

                if (mindcapAppeard && !boughtMindcapPlush){
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "mindcap.png"_spr,
                            "mindcap.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }

                if (michiAppeared && !boughtTriple){
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        1, 2, new std::string[]{
                            "michigun.png"_spr,
                            "michigun.png"_spr,
                        }
                    ), "", false, false, false, 7);
                }
            }
        }
    }
}

void plushAnimatronics::OnOpportunity(){
    if (cot->isVisible()){
        cot->setVisible(false);
        if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
            mainLayer->CamStaticOpacity = 255;
        }
    }
    if (mindcap->isVisible()){
        mindcap->setVisible(false);
        if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
            mainLayer->CamStaticOpacity = 255;
        }
    }
    if (michi->isVisible()){
        michi->setVisible(false);
        if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
            mainLayer->CamStaticOpacity = 255;
        }
    }
    if (order.size() > 0){
        plushes oppCalc = order[0];

        order.erase(order.begin());

        if (oppCalc == plushes::cot_ && !cotAppeared && _CotAILevel != 0){
            cotAppeared = true;
            saftyTimer = 20 / (_CotAILevel / 10);
            saftyLock = false;
            cot->setVisible(true);
            if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
                mainLayer->CamStaticOpacity = 255;
            }
            //spawn cot
        }
        if (oppCalc == plushes::mindcap_ && !mindcapAppeard && _MindcapAILevel != 0){
            mindcapAppeard = true;
            saftyTimer = 20 / (_MindcapAILevel / 10);
            saftyLock = false;
            mindcap->setVisible(true);
            if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
                mainLayer->CamStaticOpacity = 255;
            }
            //spawn midcap
        }
        if (oppCalc == plushes::michi_ && !michiAppeared && _MichiAILevel != 0){
            michiAppeared = true;
            saftyTimer = 20 / (_MichiAILevel / 10);
            saftyLock = false;
            michi->setVisible(true);
            if (mainLayer->currentCamSelected == CNGameLayer::Cameras::Camera02){
                mainLayer->CamStaticOpacity = 255;
            }
            //spawn michi
        }
        else{
            //spawn nobody
        }
    }
    
}