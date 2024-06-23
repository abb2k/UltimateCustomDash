
#include "killbot.h"

killbot* killbot::create(CNGameLayer* gameLayer, float opportunity, int AILevel) {
    auto ret = new killbot();
    if (ret && ret->init(gameLayer, opportunity, AILevel)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool killbot::init(CNGameLayer* gameLayer, float opportunity, int AILevel){

    mainLayer = gameLayer;
    _opportunity = opportunity;
    opportunityTimer = opportunity;
    _AILevel = AILevel;

    dtext = CCTextFieldTTF::create("blip.mp3"_spr, "chatFont.fnt", 4);
    dtext->setVisible(false);
    this->addChild(dtext);

    mainLayer->PreloadImages(std::vector<std::string>{
        "killbot1.png"_spr,
        "killbot2.png"_spr,
        "killbot3.png"_spr,
        "killbot6.png"_spr,
        "killbot5.png"_spr,
        "killbot4.png"_spr,
    });

    mainLayer->PreloadImages(std::vector<std::string>{
        "killbotText1.png"_spr,
        "killbotText2.png"_spr,
        "killbotText3.png"_spr,
        "killbotText4.png"_spr,
        "killbotText5.png"_spr,
        "killbotText6.png"_spr,
        "killbotText7.png"_spr,
    });

    scheduleUpdate();

    return true;
}

void killbot::update(float delta){
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
    if (doingThing){
        if (!rermoveNotiffi){
            if (mainLayer->getTouchOn(button)){
                doingThing = false;
                notifiCont->removeMeAndCleanup();
                jumpscareTimer = 3.5f;
                delayTimer = 2;
                source->RemoveMeAndCleanUpSound();
                source = nullptr;
                loadingText = nullptr;
                FMODAudioEngine::sharedEngine()->playEffect("blip.mp3"_spr, 1.0f,1.0f,1.0f);
            }
        }
        if (jumpscareTimer > 0){
            jumpscareTimer -= delta;
            float jumpscareTimerTo100 = 100 - (jumpscareTimer * (100 / 3.5f));

            std::string loadingTextS = std::to_string((int)jumpscareTimerTo100) + "%";
            if (loadingText != nullptr){
                loadingText->setString(loadingTextS.c_str());
            }
        }
        else {
            if (delayTimer > 0){
                delayTimer -= delta;
                if (!rermoveNotiffi){
                    rermoveNotiffi = true;
                    notifiCont->removeMeAndCleanup();
                    loadingText = nullptr;
                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.15f, 14, new std::string[]{
                            "killbotText1.png"_spr,
                            "killbotText1.png"_spr,
                            "killbotText1.png"_spr,
                            "killbotText1.png"_spr,
                            "killbotText2.png"_spr,
                            "killbotText3.png"_spr,
                            "killbotText4.png"_spr,
                            "killbotText5.png"_spr,
                            "killbotText6.png"_spr,
                            "killbotText6.png"_spr,
                            "killbotText7.png"_spr,
                            "killbotText7.png"_spr,
                            "killbotText7.png"_spr,
                            "killbotText7.png"_spr,
                        }
                    ),
                    "", true, true, true,4.75f);
                }
            }
            else{
                if (!playJumpscare){
                    playJumpscare = true;

                    mainLayer->noiseAmount++;

                    mainLayer->Jumpscare(mainLayer->CreateAnimAction(
                        0.1f, 20, new std::string[]{
                            "killbot1.png"_spr,
                            "killbot2.png"_spr,
                            "killbot3.png"_spr,
                            "killbot6.png"_spr,
                            "killbot2.png"_spr,
                            "killbot5.png"_spr,
                            "killbot4.png"_spr,
                            "killbot5.png"_spr,
                            "killbot1.png"_spr,
                            "killbot6.png"_spr,
                            "killbot4.png"_spr,
                            "killbot2.png"_spr,
                            "killbot4.png"_spr,
                            "killbot1.png"_spr,
                            "killbot5.png"_spr,
                            "killbot6.png"_spr,
                            "killbot3.png"_spr,
                            "killbot2.png"_spr,
                            "killbot3.png"_spr,
                            "killbot6.png"_spr,
                        }, 3
                    ),
                    "", true, true, true, 4.75f, 170, callfunc_selector(killbot::jumpEnded), this);
                }
            }
        }
        
    }
    if (source != nullptr && mainLayer->nightComplete || source != nullptr && mainLayer->DEATHSCREEN){
        source->RemoveMeAndCleanUpSound();
        source = nullptr;
    }
}

void killbot::OnOpportunity(){
    if (!doingThing){
        doingThing = true;
        notifiCont = CCNode::create();
        notifiCont->setScale(0.9f);
        notifiCont->setPosition({(mainLayer->randomFloat(-278,278)), (mainLayer->randomFloat(-105,170))});

        source = AudioSource::create("killbot.mp3"_spr, FMOD_DEFAULT, AudioSource::SFX);
        this->addChild(source);

        button = CCSprite::create("closeSmallDoor.png"_spr);
        button->setPosition({0, -20});
        button->setScale(1.45f);
        notifiCont->addChild(button);

        loadingText = CCLabelBMFont::create("0%", "gjFont04.fnt");
        loadingText->setPosition({2, 1});
        loadingText->setScale(0.3f);
        notifiCont->addChild(loadingText);

        CCLabelBMFont* txt = CCLabelBMFont::create("DOWNLOADING\nKILLBOT.EXE", "gjFont04.fnt");
        txt->setPosition({1, 14});
        txt->setScale(0.3f);
        notifiCont->addChild(txt);

        CCSprite* progressbar = mainLayer->CreateAnimatedSprite(0.05f, 8, new std::string[]{
            "killbotLoading1.png"_spr,
            "killbotLoading2.png"_spr,
            "killbotLoading3.png"_spr,
            "killbotLoading4.png"_spr,
            "killbotLoading5.png"_spr,
            "killbotLoading6.png"_spr,
            "killbotLoading7.png"_spr,
            "killbotLoading8.png"_spr,
        });
        progressbar->setPosition({0, -10});
        progressbar->setScale(0.175f);
        notifiCont->addChild(progressbar);

        notifiCont->setZOrder(41);
        mainLayer->Canvas->addChild(notifiCont);
    }
}

void killbot::jumpEnded(){
    rermoveNotiffi = false;
    doingThing = false;
    playJumpscare = false;
    loadingText = nullptr;
    jumpscareTimer = 3.5f;
    delayTimer = 2;
    source->RemoveMeAndCleanUpSound();
    source = nullptr;
    mainLayer->noiseAmount--;
}





