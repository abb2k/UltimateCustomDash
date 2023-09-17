#include <challenges.h>

#include "customNightLayer.h"
#include "challengeCell.h"
#include "animatronic.h"

challenges* challenges::create(CCNode* _mainlayer) {
    auto ret = new challenges();
    if (ret && ret->init(_mainlayer)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool challenges::init(CCNode* _mainlayer){

    dad = _mainlayer;
    customNightLayer* mainLayer = (customNightLayer*)dad;

    CCSprite* bg = CCSprite::create("abb2k.UltimateCustomDash/sidebarBG.png");
    bg->setPosition({526, 161});
    bg->setScaleX(1.175f);
    bg->setScaleY(1.21f);

    smallGo = CCSprite::create("abb2k.UltimateCustomDash/goSmall.png");
    smallGo->setPosition({33,23});
    bg->addChild(smallGo);

    Cancel = CCSprite::create("abb2k.UltimateCustomDash/Cancel.png");
    Cancel->setPosition({33,9});
    bg->addChild(Cancel);

    mainLayer->_AnimatronicCellContainer->SetAll(0);

    BearsAttack1 = challengeCell::create("Bears Attack 1", std::vector<animatronic*>{
        new animatronic("Freddy Fazbear", 10),
        new animatronic("Golden Freddy", 1),
        new animatronic("Phantom Freddy", 1),
        new animatronic("Nightmare Fredbear", 10),
        new animatronic("Nightmare", 10),
        new animatronic("Helpy", 5),
        new animatronic("Nedd Bear", 1),
        new animatronic("Rockstar Freddy", 5),
        new animatronic("Molten Freddy", 1),
        new animatronic("Lefty", 1)
    });
    BearsAttack1->dad = this;
    BearsAttack1->setPosition({33,247});

    challengeCell* BearsAttack2 = challengeCell::create("Bears Attack 2", std::vector<animatronic*>{
        new animatronic("Freddy Fazbear", 10),
        new animatronic("Toy Freddy", 1),
        new animatronic("Golden Freddy", 10),
        new animatronic("Phantom Freddy", 5),
        new animatronic("Nightmare Freddy", 5),
        new animatronic("Nightmare Fredbear", 10),
        new animatronic("Nightmare", 10),
        new animatronic("Helpy", 10),
        new animatronic("Nedd Bear", 10),
        new animatronic("Rockstar Freddy", 10),
        new animatronic("Molten Freddy", 10),
        new animatronic("Lefty", 10)
    });
    BearsAttack2->dad = this;
    BearsAttack2->setPosition({33,233.5f});

    challengeCell* BearsAttack3 = challengeCell::create("Bears Attack 3", std::vector<animatronic*>{
        new animatronic("Freddy Fazbear", 20),
        new animatronic("Toy Freddy", 5),
        new animatronic("Golden Freddy", 10),
        new animatronic("Phantom Freddy", 10),
        new animatronic("Nightmare Freddy", 10),
        new animatronic("Nightmare Fredbear", 20),
        new animatronic("Nightmare", 20),
        new animatronic("Helpy", 5),
        new animatronic("Nedd Bear", 10),
        new animatronic("Rockstar Freddy", 10),
        new animatronic("Molten Freddy", 10),
        new animatronic("Lefty", 10)
    });
    BearsAttack3->dad = this;
    BearsAttack3->setPosition({33,220});

    challengeCell* PayAttention1 = challengeCell::create("Pay Attention 1", std::vector<animatronic*>{
        new animatronic("BB", 5),
        new animatronic("JJ", 5),
        new animatronic("The Puppet", 5),
        new animatronic("Nightmare BB", 5),
        new animatronic("Old Man Consequences", 5),
        new animatronic("Funtime Foxy", 5),
        new animatronic("Helpy", 10),
        new animatronic("Music Man", 10),
        new animatronic("El Chip", 5),
        new animatronic("Funtime Chica", 10),
        new animatronic("Afton", 5),
        new animatronic("Phone Guy", 10)
    });
    PayAttention1->dad = this;
    PayAttention1->setPosition({33,206.5f});

    challengeCell* PayAttention2 = challengeCell::create("Pay Attention 2", std::vector<animatronic*>{
        new animatronic("BB", 20),
        new animatronic("JJ", 20),
        new animatronic("The Puppet", 10),
        new animatronic("Nightmare BB", 20),
        new animatronic("Old Man Consequences", 10),
        new animatronic("Funtime Foxy", 10),
        new animatronic("Helpy", 20),
        new animatronic("Music Man", 20),
        new animatronic("El Chip", 10),
        new animatronic("Funtime Chica", 20),
        new animatronic("Afton", 20),
        new animatronic("Phone Guy", 20)
    });
    PayAttention2->dad = this;
    PayAttention2->setPosition({33,193});

    challengeCell* LadiesNight1 = challengeCell::create("Ladies Night 1", std::vector<animatronic*>{
        new animatronic("Chica", 5),
        new animatronic("Toy Chica", 5),
        new animatronic("Mangle", 5),
        new animatronic("JJ", 1),
        new animatronic("Withered Chica", 5),
        new animatronic("Jack-O-Chica", 5),
        new animatronic("Circus Baby", 1),
        new animatronic("Ballora", 1),
        new animatronic("Happy Frog", 5),
        new animatronic("Rockstar Chica", 1),
        new animatronic("Funtime Chica", 1),
        new animatronic("Scrap Baby", 1)
    });
    LadiesNight1->dad = this;
    LadiesNight1->setPosition({33,179.5f});

    challengeCell* LadiesNight2 = challengeCell::create("Ladies Night 2", std::vector<animatronic*>{
        new animatronic("Chica", 5),
        new animatronic("Toy Chica", 10),
        new animatronic("Mangle", 5),
        new animatronic("JJ", 5),
        new animatronic("Withered Chica", 10),
        new animatronic("Jack-O-Chica", 10),
        new animatronic("Nightmare Mangle", 1),
        new animatronic("Circus Baby", 5),
        new animatronic("Ballora", 5),
        new animatronic("Happy Frog", 10),
        new animatronic("Rockstar Chica", 5),
        new animatronic("Funtime Chica", 5),
        new animatronic("Scrap Baby", 5)
    });
    LadiesNight2->dad = this;
    LadiesNight2->setPosition({33,166});

    challengeCell* LadiesNight3 = challengeCell::create("Ladies Night 3", std::vector<animatronic*>{
        new animatronic("Chica", 10),
        new animatronic("Toy Chica", 20),
        new animatronic("Mangle", 10),
        new animatronic("JJ", 10),
        new animatronic("Withered Chica", 20),
        new animatronic("Jack-O-Chica", 20),
        new animatronic("Nightmare Mangle", 10),
        new animatronic("Circus Baby", 10),
        new animatronic("Ballora", 10),
        new animatronic("Funtime Foxy", 10),
        new animatronic("Happy Frog", 20),
        new animatronic("Rockstar Chica", 10),
        new animatronic("Funtime Chica", 10),
        new animatronic("Scrap Baby", 10)
    });
    LadiesNight3->dad = this;
    LadiesNight3->setPosition({33,152.5f});

    challengeCell* CreepyCrawlies1 = challengeCell::create("Creepy Crawlies 1", std::vector<animatronic*>{
        new animatronic("Mangle", 10),
        new animatronic("Withered Chica", 5),
        new animatronic("Withered Bonnie", 10),
        new animatronic("The Puppet", 5),
        new animatronic("Springtrap", 10),
        new animatronic("Phantom Mangle", 5),
        new animatronic("Ennard", 10),
        new animatronic("Happy Frog", 5),
        new animatronic("Mr. Hippo", 5),
        new animatronic("Pigpatch", 5),
        new animatronic("Nedd Bear", 5),
        new animatronic("Orville Elephant", 5),
        new animatronic("Music Man", 5),
        new animatronic("Molten Freddy", 5)
    });
    CreepyCrawlies1->dad = this;
    CreepyCrawlies1->setPosition({33,139});

    challengeCell* CreepyCrawlies2 = challengeCell::create("Creepy Crawlies 2", std::vector<animatronic*>{
        new animatronic("Mangle", 20),
        new animatronic("Withered Chica", 20),
        new animatronic("Withered Bonnie", 20),
        new animatronic("The Puppet", 10),
        new animatronic("Springtrap", 20),
        new animatronic("Phantom Mangle", 10),
        new animatronic("Ennard", 20),
        new animatronic("Happy Frog", 20),
        new animatronic("Mr. Hippo", 20),
        new animatronic("Pigpatch", 20),
        new animatronic("Nedd Bear", 20),
        new animatronic("Orville Elephant", 20),
        new animatronic("Music Man", 10),
        new animatronic("Molten Freddy", 20),
        new animatronic("Afton", 1)
    });
    CreepyCrawlies2->dad = this;
    CreepyCrawlies2->setPosition({33,125.5f});

    challengeCell* NightmaresAttack = challengeCell::create("Nightmares Attack", std::vector<animatronic*>{
        new animatronic("Withered Bonnie", 20),
        new animatronic("Golden Freddy", 20),
        new animatronic("Nightmare Freddy", 20),
        new animatronic("Nightmare Bonnie", 20),
        new animatronic("Nightmare Fredbear", 20),
        new animatronic("Nightmare", 20),
        new animatronic("Jack-O-Chica", 20),
        new animatronic("Nightmare Mangle", 20),
        new animatronic("Nightmarionne", 20),
        new animatronic("Nightmare BB", 20),
        new animatronic("Music Man", 20),
        new animatronic("Molten Freddy", 20),
        new animatronic("Scrap Baby", 20),
        new animatronic("Lefty", 20)
    });
    NightmaresAttack->dad = this;
    NightmaresAttack->setPosition({33,112});

    challengeCell* Springtrapped = challengeCell::create("Springtrapped", std::vector<animatronic*>{
        new animatronic("JJ", 20),
        new animatronic("Springtrap", 20),
        new animatronic("Phantom Mangle", 20),
        new animatronic("Phantom Freddy", 20),
        new animatronic("Phantom BB", 20),
        new animatronic("Nightmarionne", 10),
        new animatronic("Trash and the Gang", 10),
        new animatronic("Rockstar Foxy", 20),
        new animatronic("Afton", 20),
        new animatronic("Lefty", 20)
    });
    Springtrapped->dad = this;
    Springtrapped->setPosition({33,98.5f});

    challengeCell* OldFriends = challengeCell::create("Old Friends", std::vector<animatronic*>{
        new animatronic("Freddy Fazbear", 20),
        new animatronic("Bonnie", 20),
        new animatronic("Chica", 20),
        new animatronic("Foxy", 20),
        new animatronic("Toy Freddy", 20),
        new animatronic("Toy Bonnie", 20),
        new animatronic("Toy Chica", 20),
        new animatronic("Mangle", 20),
        new animatronic("BB", 20),
        new animatronic("The Puppet", 20),
        new animatronic("Springtrap", 20),
        new animatronic("Circus Baby", 20),
        new animatronic("Phone Guy", 20)
    });
    OldFriends->dad = this;
    OldFriends->setPosition({33,85});

    challengeCell* Chaos1 = challengeCell::create("Chaos 1", std::vector<animatronic*>{
        new animatronic("Toy Freddy", 5),
        new animatronic("Withered Bonnie", 5),
        new animatronic("The Puppet", 5),
        new animatronic("Nightmare Fredbear", 10),
        new animatronic("Nightmare", 10),
        new animatronic("Jack-O-Chica", 5),
        new animatronic("Old Man Consequences", 5),
        new animatronic("Ballora", 5),
        new animatronic("Trash and the Gang", 1),
        new animatronic("Helpy", 5),
        new animatronic("Happy Frog", 1),
        new animatronic("Mr. Hippo", 1),
        new animatronic("Pigpatch", 1),
        new animatronic("Rockstar Freddy", 5),
        new animatronic("Rockstar Bonnie", 5),
        new animatronic("Rockstar Foxy", 5),
        new animatronic("Music Man", 5),
        new animatronic("El Chip", 5),
        new animatronic("Funtime Chica", 5),
        new animatronic("Afton", 5)
    });
    Chaos1->dad = this;
    Chaos1->setPosition({33,71.5f});

    challengeCell* Chaos2 = challengeCell::create("Chaos 2", std::vector<animatronic*>{
        new animatronic("Freddy Fazbear", 5),
        new animatronic("Toy Bonnie", 5),
        new animatronic("Toy Chica", 5),
        new animatronic("The Puppet", 10),
        new animatronic("Golden Freddy", 10),
        new animatronic("Phantom Freddy", 20),
        new animatronic("Phantom BB", 10),
        new animatronic("Nightmare Bonnie", 10),
        new animatronic("Nightmare Mangle", 5),
        new animatronic("Old Man Consequences", 10),
        new animatronic("Circus Baby", 5),
        new animatronic("Trash and the Gang", 10),
        new animatronic("Helpy", 10),
        new animatronic("Happy Frog", 5),
        new animatronic("Mr. Hippo", 5),
        new animatronic("Pigpatch", 5),
        new animatronic("Rockstar Freddy", 5),
        new animatronic("Rockstar Chica", 5),
        new animatronic("Rockstar Foxy", 10),
        new animatronic("Music Man", 20),
        new animatronic("El Chip", 10),
        new animatronic("Funtime Chica", 10),
        new animatronic("Scrap Baby", 20),
        new animatronic("Afton", 20),
        new animatronic("Phone Guy", 10)
    });
    Chaos2->dad = this;
    Chaos2->setPosition({33,58});

    challengeCell* Chaos3 = challengeCell::create("Chaos 3", std::vector<animatronic*>{
        new animatronic("Bonnie", 20),
        new animatronic("Foxy", 20),
        new animatronic("Toy Bonnie", 5),
        new animatronic("Toy Chica", 5),
        new animatronic("Mangle", 5),
        new animatronic("BB", 5),
        new animatronic("JJ", 5),
        new animatronic("Withered Chica", 5),
        new animatronic("Withered Bonnie", 20),
        new animatronic("Phantom Mangle", 20),
        new animatronic("Phantom BB", 20),
        new animatronic("Nightmare Bonnie", 20),
        new animatronic("Nightmarionne", 20),
        new animatronic("Nightmare BB", 20),
        new animatronic("Old Man Consequences", 20),
        new animatronic("Ennard", 20),
        new animatronic("Trash and the Gang", 20),
        new animatronic("Helpy", 20),
        new animatronic("Happy Frog", 10),
        new animatronic("Mr. Hippo", 10),
        new animatronic("Pigpatch", 10),
        new animatronic("Nedd Bear", 20),
        new animatronic("Orville Elephant", 20),
        new animatronic("Rockstar Freddy", 10),
        new animatronic("Rockstar Bonnie", 20),
        new animatronic("Rockstar Chica", 20),
        new animatronic("Rockstar Foxy", 20),
        new animatronic("Music Man", 20),
        new animatronic("El Chip", 20),
        new animatronic("Funtime Chica", 20),
        new animatronic("Lefty", 20),
        new animatronic("Phone Guy", 10)
    });
    Chaos3->dad = this;
    Chaos3->setPosition({33,44.5f});

    bg->addChild(BearsAttack1);
    bg->addChild(BearsAttack2);
    bg->addChild(BearsAttack3);
    bg->addChild(PayAttention1);
    bg->addChild(PayAttention2);
    bg->addChild(LadiesNight1);
    bg->addChild(LadiesNight2);
    bg->addChild(LadiesNight3);
    bg->addChild(CreepyCrawlies1);
    bg->addChild(CreepyCrawlies2);
    bg->addChild(NightmaresAttack);
    bg->addChild(Springtrapped);
    bg->addChild(OldFriends);
    bg->addChild(Chaos1);
    bg->addChild(Chaos2);
    bg->addChild(Chaos3);
    this->addChild(bg);

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    this->setTouchPriority(1);
    setKeypadEnabled(true);

    scheduleUpdate();

    return true;
}

void challenges::update(float delta){

    if (getTouchOn(Cancel)){
        keyBackClicked();
    }
}

void challenges::setChallenge(animatronic animatronics[]){
    customNightLayer* mainLayer = (customNightLayer*)dad;
    for (int i = 0; i < sizeof(animatronics); i++)
    {
        mainLayer->_AnimatronicCellContainer->SetSpecific(animatronics[i].name, animatronics[i].difficulty);

    }
}

void challenges::keyBackClicked() {
    customNightLayer* mainLayer = (customNightLayer*)dad;
    mainLayer->_challenges = nullptr;
    GameSoundManager::sharedManager()->playEffect("abb2k.UltimateCustomDash/blip.wav", 1.0f,1.0f,1.0f);
    mainLayer->_AnimatronicCellContainer->SetAll(0);

    this->removeMeAndCleanup();
}

bool challenges::ccTouchBegan(CCTouch* touch, CCEvent* e){
    clicking = true;

    return true;
}

void challenges::ccTouchMoved(CCTouch* touch, CCEvent* e){
    clicking = true;
}

void challenges::ccTouchEnded(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

void challenges::ccTouchCancelled(CCTouch* touch, CCEvent* e){
    clicking = false;
    oneTimeClick = false;
}

bool challenges::getHover(CCNode* node){
    //size
    auto contentSize = node->getContentSize();

    //get all parents (to multiply width and height with scale of them)
    bool HasreachedEndOfParentCheck = false;

    CCNode* LastParent = node->getParent();

    CCNode* Scene = nullptr;

    float multiplyX = node->getScaleX();

    float multiplyY = node->getScaleY();

    while(!HasreachedEndOfParentCheck){

        if (LastParent != nullptr){
            multiplyX = multiplyX * LastParent->getScaleX();
            multiplyY = multiplyY * LastParent->getScaleY();

            Scene = LastParent;
            LastParent = LastParent->getParent();
        }
        else {
            HasreachedEndOfParentCheck = true;
        }
    }

    //pos
    auto pos = node->convertToWorldSpace({0,0});

    auto mousePos = getMousePos();

    CCRect* rect = new CCRect(pos.x, pos.y, contentSize.width * multiplyX, contentSize.height * multiplyY);

    //check
    if (rect->containsPoint(mousePos)){
        return true;
    }

    return false;
}

bool challenges::getTouchOn(CCNode* node, CCTouch* touch){
    //size
    auto contentSize = node->getContentSize();

    //get all parents (to multiply width and height with scale of them)
    bool HasreachedEndOfParentCheck = false;

    CCNode* LastParent = node->getParent();

    CCNode* Scene = nullptr;

    float multiplyX = node->getScaleX();

    float multiplyY = node->getScaleY();

    while(!HasreachedEndOfParentCheck){

        if (LastParent != nullptr){
            multiplyX = multiplyX * LastParent->getScaleX();
            multiplyY = multiplyY * LastParent->getScaleY();

            Scene = LastParent;
            LastParent = LastParent->getParent();
        }
        else {
            HasreachedEndOfParentCheck = true;
        }
    }

    //pos
    auto pos = node->convertToWorldSpace({0,0});

    auto mousePos = touch;

    CCRect* rect = new CCRect(pos.x, pos.y, contentSize.width * multiplyX, contentSize.height * multiplyY);

    //check
    if (rect->containsPoint(mousePos->m_point)){
        return true;
    }

    return false;
}

bool challenges::getTouchOn(CCNode* node){

    if (clicking && !oneTimeClick){
        if (getHover(node)){
            oneTimeClick = true;
            return true;
        }
    }
    return false;
}