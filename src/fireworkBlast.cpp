#include "fireworkBlast.h"
#include "CNGameLayer.h"

fireworkBlast* fireworkBlast::create(CCNode* dad) {
    auto ret = new fireworkBlast();

    if (ret && ret->init(dad)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool fireworkBlast::init(CCNode* dad) { 

    yellowGlow = CCSprite::create("yellowGlow.png"_spr);
    yellowGlow->setZOrder(-1);
    yellowGlow->setScale(0.4f);
    this->addChild(yellowGlow);

    int randomSound = rand() % 2;

    switch (randomSound)
    {
    case 0:
        FMODAudioEngine::sharedEngine()->playEffect("pop1.mp3"_spr, 1.0f,1.0f,1.0f);
        break;
    case 1:
        FMODAudioEngine::sharedEngine()->playEffect("pop2.mp3"_spr, 1.0f,1.0f,1.0f);
        break;
    
    default:
        break;
    }

    int startsAmount = 10 + (rand() % 31);

    for (int i = 0; i < startsAmount; i++)
    {
        CNGameLayer* main = (CNGameLayer*)dad;

        Star* s = new Star();
        s->direction.x = main->randomFloat(-1, 1);
        s->direction.y = main->randomFloat(-1, 1);

        int starSelected = rand() % 6;

        CCSprite* starSprite;

        switch (starSelected)
        {
        case 0:
            starSprite = CCSprite::create("starBlue.png"_spr);
            break;

        case 1:
            starSprite = CCSprite::create("starGreen.png"_spr);
            break;

        case 2:
            starSprite = CCSprite::create("starPink.png"_spr);
            break;

        case 3:
            starSprite = CCSprite::create("starRed.png"_spr);
            break;

        case 4:
            starSprite = CCSprite::create("starSmall.png"_spr);
            break;

        case 5:
            starSprite = CCSprite::create("starYellow.png"_spr);
            break;
        }

        s->sprite = starSprite;

        this->addChild(s->sprite);

        stars.insert(stars.begin(), s);
    }
    

    scheduleUpdate();

    return true;
}

void fireworkBlast::update(float delta){

    for (size_t i = 0; i < stars.size(); i++)
    {
        stars[i]->sprite->setPosition((stars[i]->sprite->getPosition() + (stars[i]->direction * speed * delta)));
        stars[i]->sprite->setOpacity((int)opaci);
        stars[i]->sprite->setPosition({stars[i]->sprite->getPositionX(), stars[i]->sprite->getPositionY() - 15 * delta});
    }
    if (speed > 0){
        speed -= delta * 275;

        if (speed <= 0){
            speed = 0;
        }
    }
    if (speed <= 0){
        speed = 0;

        if (opaci > 0){
            opaci -= delta * 700;

            if (opaci <= 0){
                opaci = 0;
            }
        }
        if (opaci <= 0){
            opaci = 0;
            this->removeMeAndCleanup();
        }

    }

    if (yellowGlowOpaci > 0){
        yellowGlowOpaci -= delta * 700;

        if (yellowGlowOpaci <= 0){
            yellowGlowOpaci = 0;
        }
    }
    if (yellowGlowOpaci <= 0){
        yellowGlowOpaci = 0;

    }
    yellowGlow->setOpacity((int)yellowGlowOpaci);
}