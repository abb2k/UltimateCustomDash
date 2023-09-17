
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
    
    _AnimatronicCellContainer = AnimatronicCellContainer::create(new AnimatronicCell*[]{
        AnimatronicCell::create("Freddy_Fazbear.png", "Freddy Fazbear", "He approaches from  the left hall. Keep track of him on the monitor and shut the door when he is standing in the doorway. He moves faster as the building gets warmer"),
        AnimatronicCell::create("Bonnie.png", "Bonnie", "He now shares Pirate Cove with Foxy, but whereas Foxy will hide from himself when viewed on camera, Bonnie will do the opposite, and become more agitated. View the figurine on the desk to see who is active in Pirate's Cove."),
        AnimatronicCell::create("Chica.png", "Chica", "While Chica doesn't care if the music box is wound up, she can grow tired of the selection playing. When the sound of pots and pans stops, you only have a short amount of time to change the music. The Global Music Box can also soothe her."),
        AnimatronicCell::create("Foxy.png", "Foxy", "He will gradually leave Pirate's Cove if you don't check on him regularly. Once he is out, he will enter your office piece by piece."),
        AnimatronicCell::create("Toy_Freddy.png", "Toy Freddy", "He sits in the Parts and Service room playing Five Nights With Mr. Hugs on his big screen TV. Click the cams on Toy Freddy's monitor, then be sure that the appropriate door is closed to prevent Mr. Hugs from jumpscaring him."),
        AnimatronicCell::create("Toy_Bonnie.png", "Toy Bonnie", "Put on your Freddy Fazbear mask quickly when he sneaks into your room to fool him and make him go away."),
        AnimatronicCell::create("Toy_Chica.png", "Toy Chica", "Put on your Freddy Fazbear mask quickly when she sneaks into your room to fool her and make her go away."),
        AnimatronicCell::create("Mangle.png", "Mangle", "Unlike the other animatronics in the vents, once Mangle reaches the vent opening he will never leave. Use the vent-snare to prevent her from making it that far."),
        AnimatronicCell::create("BB.png", "BB", "He will try to sneak in through the side vent. Close the side vent and wait until you hear a thud indicating he is gone. If BB slips in, he will temporarily disable your flashlight."),
        AnimatronicCell::create("JJ.png", "JJ", "She will try to sneak in through the side vent. Close the side vent and wait until you hear a thud indicating she is gone. If JJ slips in, she will disable door controls temporarily."),
        AnimatronicCell::create("Witherd_Chica.png", "Withered Chica", "She climbs through the air vents, but may get stuck when trying to enter your office. Use the vent-snare to prevent her from reaching the opening."),
        AnimatronicCell::create("Toilet_Bonnie.png", "Withered Bonnie", "He will appear in your office poised to attack! Throw on your Freddy mask to make him leave again."),
        AnimatronicCell::create("Puppet.png", "The Puppet", "Keep his music box wound or he will come to get you! The global music box also works against him."),
        AnimatronicCell::create("Golden_Freddy.png", "Golden Freddy", "He will occasionally appear in your office. Throw on your Freddy mask or pull up your monitor quickly to cause him to disappear."),
        AnimatronicCell::create("Springtrap.png", "Springtrap", "He makes his way toward the vent opening embedded in the wall in front of you. When he is poised to attack you will see his face looking down at you. Close the vent door to send him away."),
        AnimatronicCell::create("Phantom_Mangle.png", "Phantom Mangle", "When you see him on your monitor, quickly close it, or he will appear in your office and create an audio disturbance."),
        AnimatronicCell::create("Phantom_Freddy.png", "Phantom Freddy", "Shine your flashlight on him to cause him to fade away. If you don't, he will jumpscare you, giving time for enemies in the vents to sneak into your office. Heat causes him to appear faster."),
        AnimatronicCell::create("Phantom_BB.png", "Phantom BB", "When he appears on your monitor, quickly close it or change the cam to avoid his jumpscare."),
        AnimatronicCell::create("Nightmare_Freddy.png", "Nightmare Freddy", "When the Freddles begin to accumulate in your office, shine your flashlight on them before Freddy appears!"),
        AnimatronicCell::create("Nightmare_Bonnie.png", "Nightmare Bonnie", "Buy his plush from the Prize Counter when he appears in the hallway to avoid his jumpscare. He can't be stopped by the office door."),
        AnimatronicCell::create("Nightmare_Freadbear.png", "Nightmare Fredbear", "He is invisible to the cameras and can only be seen when he reaches your left doorway. Close the door on his face to send him back into the darkness!"),
        AnimatronicCell::create("Nightmare.png", "Nightmare", "He is invisible to the cameras and can only be seen when he reaches your right doorway. Close the door on his face to send him back into the darkness!"),
        AnimatronicCell::create("Jack_O_Chica.png", "Jack-O-Chica", "When the office heats up, she will appear in both halls at the same time. Close both doors to make her vanish. This won't work if the office is 100 degrees or more."),
        AnimatronicCell::create("Nightmare_Mangle.png", "Nightmare Mangle", "Purchase his plush toy from the Prize Counter when he appears in the right hall to avoid his attack! He can't be stopped by the office door."),
        AnimatronicCell::create("Nighmarione.png", "Nightmarionne", "Don't let your mouse cursor linger over Nightmarionne for too long!"),
        AnimatronicCell::create("Nightmare_BB.png", "Nightmare BB", "When he is slumped over in your office, do not shine your light on him. When he is sitting up however, you must use your flashlight to reset him."),
        AnimatronicCell::create("Old_Man_Conseqances.png", "Old Man Consequences", "Use the C button to catch a fish when his mini-game appears, otherwise he will lock your monitor for a short time."),
        AnimatronicCell::create("Baby.png", "Circus Baby", "Purchase her plush toy from the Prize Counter when she appears in the right hall to avoid her attack! The office door can't stop her."),
        AnimatronicCell::create("ballora.png", "Ballora", "She will approach from the one of the hallways. Listen for which hall she is in and shut the appropriate door."),
        AnimatronicCell::create("Funtime_Foxy.png", "Funtime Foxy", "Check his curtain to see when his show is set to begin, then be sure to watch his cam at that exact time to postpone the show, otherwise that is when your game will end."),
        AnimatronicCell::create("Ennerd.png", "Ennard", "Difficult to see on the vent radar, he will make his way toward your office. Listen for the sound cue of squeaking metal, then close the vent."),
        AnimatronicCell::create("Trash_And_The_Gand.png", "Trash and the Gang", "???*"),
        AnimatronicCell::create("Helpy.png", "Helpy", "When you see him sitting in your office, click on him quickly, otherwise he will get in your face with an airhorn, agitating sound-sensitive animatronics."),
        AnimatronicCell::create("HappyFrog.png", "Happy Frog", "She moves through the air ducts making her way toward you. Use the audio-lure to keep her in place. She is immune to the heater."),
        AnimatronicCell::create("mr.Hippo.png", "Mr. Hippo", "He makes his way toward your office using the air ducts. Use the audio-lure to hold him in place, or the heater to push him back."),
        AnimatronicCell::create("Pigpatch.png", "Pigpatch", "He makes his way toward your office using the air ducts. Use the audio-lure to hold him in place, or the heater to push him back."),
        AnimatronicCell::create("neddbear.png", "Nedd Bear", "He climbs through the vent system making his way toward you. Use the audio-lure or the heater to keep him at bay."),
        AnimatronicCell::create("Orvil.png", "Orville Elephant", "He makes his way toward your office through the air ducts. He isn't often fooled by the audio-lure, but can be pushed back with the heater."),
        AnimatronicCell::create("Rockstar_Freddy.png", "Rockstar Freddy", "He will occassionally activate and ask for five Faz-Coins. You can alternatively use the heater to cause him to malfunction."),
        AnimatronicCell::create("Rockstar_Bonnie.png", "Rockstar Bonnie", "When he appears in your office, search the cameras to find his guitar. Click the guitar to send him away."),
        AnimatronicCell::create("Rockstar_Chica.png", "Rockstar Chica", "Check the left and right hallways, then double-click the wet-floor sign to place it on the same side as Rockstar Chica. She won't enter if the sign is in place."),
        AnimatronicCell::create("Rockstar_Foxy.png", "Rockstar Foxy", "When you see his parrot, click it, and Rockstar Foxy may offer you some help. This comes with risk, however."),
        AnimatronicCell::create("MusicMan.png", "Music Man", "Keep the noise down, or you'll begin to hear his cymbals crashing faster and faster eventually leading to a jumpscare."),
        AnimatronicCell::create("El_Chip.png", "El Chip", "He's just here to promote his new restaurant. Close the ad when it appears."),
        AnimatronicCell::create("Funtime_Chica.png", "Funtime Chica", "She will appear at random to distract you. There is no way to avoid her."),
        AnimatronicCell::create("Molten_Freddy.png", "Molten Freddy", "He climbs in the vents, but can avoid the vent snare. Listen for his voice, then shut the vent door before he gets through."),
        AnimatronicCell::create("ScrapBaby.png", "Scrap Baby", "She will appear on the opposite side of your office desk. When she moves, use a controlled shock!"),
        AnimatronicCell::create("Afton.png", "Afton", "He will attack once per night, making a lot of noise and causing the lights to flicker before attacking. Close the right vent door to block him."),
        AnimatronicCell::create("Lefty.png", "Lefty", "He becomes active from noise and heat. He is too far away from the music box to be soothed by it, but the global music box can calm him down."),
        AnimatronicCell::create("Phone_Guy.png", "Phone Guy", "When he calls, quickly mute him, otherwise it will create a lengthy audio disturbance. The mute button will appear in different places each time.")
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

    CCLabelTTF* version = CCTextFieldTTF::create("Ultimate Custom Dash v0.1.0", "chatFont.fnt", 7);

    version->setPosition({31,2});
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

    //_MenuSideBar->setVisible(false);
    //_AnimatronicCellContainer->setVisible(false);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    setKeypadEnabled(true);

    return true;
}

void customNightLayer::keyBackClicked() {
    if (_officeLayer == nullptr || _PowerUpsLayer == nullptr || _challenges == nullptr){
        CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);

        GameSoundManager::sharedManager()->stopBackgroundMusic();

        GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
    }
}

void customNightLayer::EnterLayer() {
    auto layer = customNightLayer::create();
    auto scene = CCScene::create();

    scene->addChild(layer);
    auto transition = CCTransitionFade::create(0.5f, scene);

    GameSoundManager::sharedManager()->stopBackgroundMusic();

    GameManager::sharedState()->fadeInMusic("abb2k.UltimateCustomDash/Eisoptrophobia.wav");

    CCDirector::sharedDirector()->pushScene(transition);
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