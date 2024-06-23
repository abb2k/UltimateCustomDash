
#include <customNightLayer.h>
#include <AnimatronicCellContainer.h>

customNightLayer* customNightLayer::create() {
    auto ret = new customNightLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool customNightLayer::init() {
    _AnimatronicCellContainer = AnimatronicCellContainer::create(std::vector<AnimatronicCell*>{
        //row1
        AnimatronicCell::create("default_gd_cube.png", "Cube", "He will climb through the vents, and he won't be stopped by the front vent door, only from the vent snares. He will not be affected by the silent ventilation."),
        AnimatronicCell::create("spike.png", "Spike", "He goes through the ducts. He will sometimes listen to the audio lure, and will be pushed back by the heater."),
        AnimatronicCell::create("shopkeeper.png", "Shopkeeper", "He sits in your office. He will sometimes wake up asking you for 8 coins, you can either make him stop by paying, or by using the heater."),
        AnimatronicCell::create("clubstepMonster.png", "Clubstep Monster", "He will sometimes start closing his teeth on your head, to stop him you will need to use the Heater."),
        AnimatronicCell::create("voskeeper.png", "The Keymaster", "He will randomly pick a button and lock it, making it unusable. You will need to click him 5 times for him to go away."),
        AnimatronicCell::create("basementDemon.png", "Demon Gurdian", "He will sometimes appear in your office, when he does his eyes will have 2 different colors (blue, green, or orange). You will need to look in the cameras for the differently colored key."),
        AnimatronicCell::create("secretShopkeeper.png", "Scratch", "He will go through the ducts. He can be fooled using the audio lure, or you can use the heater to push him back."),
        AnimatronicCell::create("customShopkeeper.png", "Potbor", "He sits in cam04. His shop theme will play whenever he is calm, and when the theme stops playing, he will come to kill you. To calm him down again, change the music playing on the music box. If you do that while he isn't angry he will kill you."),
        AnimatronicCell::create("demonFace.png", "Demon", "He will sometimes climb into the bottom right vent, and if he manages to enter the room, he will disable your flashlight."),
        AnimatronicCell::create("cotKeeper.png", "The Gate Keeper", "He will sometimes stand in cam02. To stop him, you will need to buy the elder emerald from the shop."),
        //row2
        AnimatronicCell::create("theVaultKeeper.png", "Spooky", "He will go through the duct system and he won't be fooled by the audio lure, you can use the heater to push him back."),
        AnimatronicCell::create("nSwish.png", "nSwish", "She stands behind you in the office. If you make a lot of noise he will get angrier and kill you. The angrier he gets, the more sounds he makes."),
        AnimatronicCell::create("TMMonster.png", "Time Machine Dinosaur", "He will sometimes appear on the cameras obstructing your view."),
        AnimatronicCell::create("deadlockedCube.png", "Deadlocked Cubes", "They will sometimes appear on your screen, moving up and down to distract you."),
        AnimatronicCell::create("TOE2Monster.png", "Theory of Everything II Monster", "He will go through the duct system. He won't always be fooled by the audio lure, you can use the heater to push them back."),
        AnimatronicCell::create("extremeFace.png", "Extreme Demon", "Before approaching, he will make lots of noise and flash the lights. If you don't close the bottom right vent in time he will kill you."),
        AnimatronicCell::create("aeonair.png", "Aeon Air", "Aeon is always in Cam01 and will slowly come closer to the door. You need to close the door before he gets to you. He gets faster the warmer it is."),
        AnimatronicCell::create("npesta.png", "Npesta", "He will appear in your office occasionally. Put on your mask quickly to make him dissapear."),
        AnimatronicCell::create("technical.png", "Technical", "He slowly comes at you from the left side of the screen. Put on your mask before he gets too close."),
        AnimatronicCell::create("deadlockedMonsters.png", "Deadlocked Monsters", "A small minigame will sometimes appear on your screen, in which you will need to catch 3 monsters. To do so, press C whenever one is on the + sign in the middle. If you miss 3 times or don't complete the game in time, they will disable your doors for a short while."),
        //row 3
        AnimatronicCell::create("zoink.png", "Zoink", "He will sometimes place a fixed hitbox spike on the screen. Don’t linger your mouse over it for too long or else he will hack your computer, killing you in the process."),
        AnimatronicCell::create("evw.png", "EricVanWilderman", "He sits in cam03. If you make too much noise or the office gets too hot, he will get angry and will kill you. You can calm him down using the power AC."),
        AnimatronicCell::create("dorami.png", "Dorami", "He climbs through the vents, and he will not be stopped by the vent snare, but he will be stopped by the front vent door. Silent ventilation slows him down."),
        AnimatronicCell::create("robtop.png", "RobTop", "He resides in cam04. You need to wind up the music box to keep him calm. you can go to cam04 to wind up the music box, or alternatively use the Global Music Box to wind up the music box."),
        AnimatronicCell::create("doggie.png", "Doggie", "You will find him at cam05. He will slowly open the curtains, and when he fully opens them, he will sprint towards your left door. If you dont close it in time he will kill you."),
        AnimatronicCell::create("bloodbath.png", "Bloodbath", "It appears inactive in your office. The longer you open the cameras for, the more active it gets, eventually killing you. You can soothe it by activating silent ventilation."),
        AnimatronicCell::create("astralDevinity.png", "Astral Devinity", "It will sometimes slowly come at you from the right side of the screen. Put on your mask before it gets too close."),
        AnimatronicCell::create("reqcube.png", "Requiem Cube", "He will sometimes appear in your office. When he does, make sure you click on him before he disappears! Or else he disables your cameras for a few seconds."),
        AnimatronicCell::create("fireworkSkull.png", "Firework Skull", "He will go through the ducts. He does not listen to the audio lure but will be pushed back by the heater. The Global Music Box speeds him up."),
        AnimatronicCell::create("B.png", "B", "Small bees will slowly appear in your room. Use your flashlight to get them away. If too many appear, they will kill you."),
        //row 4
        AnimatronicCell::create("pressStartSkull.png", "Press Start Skull", "He will sometimes enter your office. Put on your mask to make him go away."),
        AnimatronicCell::create("Peaceful.png", "Peaceful Silly Guys", "They will sometimes appear on your screen trying to scare you. Press enter to remove them."),
        AnimatronicCell::create("Clown.png", "Crazy III Clown", "He will go through the vents. He is invisible to the cameras but will make a sound when he is next to the front door. You need to close the vent when he makes the sound. The silent ventilation slows him down, and the powerAC speeds him up."),
        AnimatronicCell::create("animMonster.png", "Animation Monster", "He will climb through the vents. He can be avoided using the front vent door and vent snares. Unlike the other vent animatronics, the silent ventilation does not slow him down"),
        AnimatronicCell::create("yata.png", "Yatagarasu Bird", "He will sometimes fly across your office. If his eye is green click him, and if his eye is red, don't."),
        AnimatronicCell::create("bloodlust.png", "Bloodlust Monster", "He will go through the duct system. He can be fooled using the audio lure."),
        AnimatronicCell::create("wulzy.png", "Wulzy", "You will sometimes hear his signature WOAH from either side. Close the door that you heard the sound come from before it's too late."),
        AnimatronicCell::create("solarFlareSun.png", "Solar Flare Sun", "He will manifest more the higher the temperature is, and if he fully appear he will kill you."),
        AnimatronicCell::create("mindcap.png", "Mindcap", "He will wait at the cam02 corridor. If you don't buy his plushy from the store in time, he will kill you."),
        AnimatronicCell::create("magmaBound.png", "Magma Bound", "He will climb through the vents. He can't be stopped by the vent snare. When he gets out of the vent you will see his face in the top vent. Close the vent to avoid death. He gets faster the hotter the office is, and will slow down if silent ventilation or powerAC is on."),
        //row 5
        AnimatronicCell::create("theEschaton.png", "The Eschaton", "He will sit in your office deactivated. If he gets activated, press him to deactivate him again. If you click him while he is inactive he will instantly kill you."),
        AnimatronicCell::create("karmaL.png", "KarmaL", "He will sleep on the right side of the office. If he wakes up, flash your light on him. If you flash the light on him while he is asleep, he will instantly kill you."),
        AnimatronicCell::create("viprin.png", "Viprin", "He will crawl through the vents. Only the vent snare can stop him. Silent ventilation slows him a little."),
        AnimatronicCell::create("loochi.png", "Loochi", "He will sometimes appear in your cameras. If you look at him for too long, he will disable the cameras and cause a lot of noise."),
        AnimatronicCell::create("michigun.png", "Muchigun", "He will appear in the hallway on cam02. You need to buy the triple spike in the shop to avoid him. ∆∆∆"),
        AnimatronicCell::create("riot.png", "Riot", "He will be on cam06. On cam06, he will slowly open the curtain. Before he fully exits you need to go to his camera and click “close curtains” to reset him. If you attempt to reset him when the curtains are fully closed, he will get angry and kill you. The Global Music Box slows him down."),
        AnimatronicCell::create("spaceUK.png", "SpaceUK", "He sits in Cam08, playing “Five Nights At ZBot” on his PC. You need to help him survive within the game or else he will throw a temper tantrum and kill you."),
        AnimatronicCell::create("grandpaDemon.png", "Grandpa Demon", "He will stand next to the right or left door. You need to move the floor sign to the side where he is standing to stop him from killing you."),
        AnimatronicCell::create("SHSnowman.png", "Slaughterhouse Snowman", "He will sometimes appear on cameras, blocking your view. If you look at him for too long, he will disable the cameras."),
        AnimatronicCell::create("Killbot.png", "Killbot", "When killbot tries to download itself, you will quickly have to stop it from downloading. If you fail to do so in time, it will flash your screen, making lots of noise in the process.")
    },
    50,
    10,
    2);
    _AnimatronicCellContainer->setPosition({28, 285});
    _AnimatronicCellContainer->setScale(1.2f);
    _AnimatronicCellContainer->dad = this;
    this->addChild(_AnimatronicCellContainer);

    _MenuSideBar = MenuSideBar::create();
    _MenuSideBar->setPosition({524, 157});
    _MenuSideBar->dad = this;

    CCLabelTTF* version = CCTextFieldTTF::create("Ultimate Custom Dash v1.0.5 - beta", "chatFont.fnt", 7, {200, 200}, CCTextAlignment::kCCTextAlignmentLeft);

    version->setPosition({72,-62});
    version->setScale(0.675f);
    version->setZOrder(50);
    this->addChild(version);

    CCNode* BGContainer = CCNode::create();

    int CurrRow = 0;
    int currSqare = 0;

    for (int i = 0; i < 200; i++)
    {
        int spriteGotten = rand() % 5;
        
        if (spriteGotten == 0 || spriteGotten == 3){
            CCSprite* bgTileBlue = CreateAnimatedSprite(0.2f, 9, new std::string[]{
            "abb2k.UltimateCustomDash/bgtilesBlue1.png",
            "abb2k.UltimateCustomDash/bgtilesBlue2.png",
            "abb2k.UltimateCustomDash/bgtilesBlue3.png",
            "abb2k.UltimateCustomDash/bgtilesBlue4.png",
            "abb2k.UltimateCustomDash/bgtilesBlue5.png",
            "abb2k.UltimateCustomDash/bgtilesBlue6.png",
            "abb2k.UltimateCustomDash/bgtilesBlue7.png",
            "abb2k.UltimateCustomDash/bgtilesBlue8.png",
            "abb2k.UltimateCustomDash/bgtilesBlue9.png"
            });

            CCSize cs = bgTileBlue->getContentSize();

            bgTileBlue->setPosition({(float)((24 * currSqare) - (24 * 20 / 2) + (cs.width / 2)), (float)((26.75f * CurrRow) - (26.75f * 10 / 2) + (cs.height / 2))});

            bgTileBlue->setOpacity(130);

            BGContainer->addChild(bgTileBlue);
        }
        else if (spriteGotten == 1 || spriteGotten == 4){
            CCSprite* bgTileRed = CreateAnimatedSprite(0.15f, 13, new std::string[]{
            "abb2k.UltimateCustomDash/bgtilesRed1.png",
            "abb2k.UltimateCustomDash/bgtilesRed2.png",
            "abb2k.UltimateCustomDash/bgtilesRed3.png",
            "abb2k.UltimateCustomDash/bgtilesRed4.png",
            "abb2k.UltimateCustomDash/bgtilesRed5.png",
            "abb2k.UltimateCustomDash/bgtilesRed6.png",
            "abb2k.UltimateCustomDash/bgtilesRed7.png",
            "abb2k.UltimateCustomDash/bgtilesRed8.png",
            "abb2k.UltimateCustomDash/bgtilesRed9.png",
            "abb2k.UltimateCustomDash/bgtilesRed10.png",
            "abb2k.UltimateCustomDash/bgtilesRed11.png",
            "abb2k.UltimateCustomDash/bgtilesRed12.png",
            "abb2k.UltimateCustomDash/bgtilesRed13.png"
            });

            CCSize css = bgTileRed->getContentSize();

            bgTileRed->setPosition({(float)((24 * currSqare) - (24 * 20 / 2) + (css.width / 2)), (float)((26.75f * CurrRow) - (26.75f * 10 / 2) + (css.height / 2))});

            bgTileRed->setOpacity(130);

            BGContainer->addChild(bgTileRed);
        }

        if (currSqare != 19){
            currSqare++;
        }
        else {
            CurrRow++;
            currSqare = 0;
        }
    }

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    BGContainer->setPosition({winSize / 2});

    BGContainer->setZOrder(-50);
    BGContainer->setScale(1.21f);
    BGContainer->setRotation(1);

    this->addChild(BGContainer);
    this->addChild(_MenuSideBar);

    faceScreen = CCSprite::create("blackscreen.png"_spr);
    faceScreen->setScale(5);
    faceScreen->setZOrder(100);
    faceScreen->setOpacity((int)fadeScreenOpacity);
    this->addChild(faceScreen);

    //_MenuSideBar->setVisible(false);
    //_AnimatronicCellContainer->setVisible(false);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    setKeypadEnabled(true);

    scheduleUpdate();

    return true;
}

void customNightLayer::keyBackClicked() {
    if (_officeLayer == nullptr || _PowerUpsLayer == nullptr || _challenges == nullptr){
        CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);

        FMODAudioEngine::sharedEngine()->stopAllMusic();

        if (bgMusic != nullptr){
            bgMusic->RemoveMeAndCleanUpSound();
            bgMusic = nullptr;
        }

        audioSources.clear();

        GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
    }
}

void customNightLayer::EnterLayer(float transitionSpeed) {
    auto layer = customNightLayer::create();
    auto scene = CCScene::create();

    if (bgMusic == nullptr){
        bgMusic = AudioSource::create("Eisoptrophobia.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::VolumeChannel::Custom);
        this->addChild(bgMusic);
    }

    scene->addChild(layer);
    auto transition = CCTransitionFade::create(transitionSpeed, scene);

    FMODAudioEngine::sharedEngine()->stopAllMusic();

    CCDirector::sharedDirector()->pushScene(transition);
}

void customNightLayer::onEnterTransitionDidFinish(){
    FadeActive = true;
    if (bgMusic == nullptr){
        bgMusic = AudioSource::create("Eisoptrophobia.mp3"_spr, FMOD_LOOP_NORMAL, AudioSource::VolumeChannel::Custom);
        this->addChild(bgMusic);
    }
}

bool customNightLayer::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void customNightLayer::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void customNightLayer::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void customNightLayer::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

CCSprite* customNightLayer::CreateAnimatedSprite(float speed, int amoutOfFrames, std::string frames[]){
    CCSprite* spr = CCSprite::create(frames[0].c_str());

    CCRect sprRect = spr->getTextureRect();

    CCArray* sprframes = CCArray::create();

    for (int i = 0; i < amoutOfFrames; i++)
    {
        sprframes->addObject(CCSpriteFrame::create(frames[i].c_str(), sprRect));
    }
     
    CCAnimation* sprAnimation = CCAnimation::createWithSpriteFrames(sprframes, speed);

    CCAction* sprAction = CCRepeatForever::create(CCAnimate::create(sprAnimation));

    spr->runAction(sprAction);

    return spr;
}

void customNightLayer::update(float delta){
    if (doubleClickTimer > 0){
        doubleClickTimer -= delta;

        if (doubleClickTimer <= 0){
            doubleClickTimer = 0;
        }
    }

    if (FadeActive){
        if (fadeScreenOpacity > 0){
            fadeScreenOpacity -= delta * FadeSpeed;

            if (fadeScreenOpacity <= 0){
                fadeScreenOpacity = 0;
            }
        }
        else {
            fadeScreenOpacity = 0;
        }
    }
    else {
        if (fadeScreenOpacity < 255){
            fadeScreenOpacity += delta * FadeSpeed;

            if (fadeScreenOpacity >= 255){
                fadeScreenOpacity = 255;
            }
        }
        else {
            fadeScreenOpacity = 255;
        }
    }
    faceScreen->setOpacity((int)fadeScreenOpacity);

    if (fadeScreenOpacity == 255){
        isTransitionReady = true;
    }
    else {
        isTransitionReady = false;
    }

    if (bgMusic != nullptr){
        bgMusic->setCustomVolume(Mod::get()->getSavedValue<float>("Game_Volume", 0.5f));
    }
}