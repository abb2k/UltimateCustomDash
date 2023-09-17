
#include <discriptionBox.h>

discriptionBox* discriptionBox::create(std::string _name, std::string _discription) {
    auto ret = new discriptionBox();

    if (ret && ret->init(_name, _discription)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}


bool discriptionBox::init(std::string _name, std::string _discription) { 

    Name = _name;
    discription = _discription;

    CCSprite* box = CCSprite::create("abb2k.UltimateCustomDash/discriptionBox.png");
    box->setPosition({1, 0});
    box->setScaleX(0.65f);
    box->setOpacity(230);

    this->setScaleX(1.35f);
    this->setScaleY(1.2f);

    std::string textFull = _name + ": " + _discription;

    CCLabelTTF* text = CCTextFieldTTF::create(textFull.c_str(), "chatFont.fnt", 15, {225,225}, CCTextAlignment::kCCTextAlignmentLeft);

    text->setPosition({0,-7.5f});
    text->setScale(0.21f);
    text->setZOrder(1);

    this->addChild(text);
    this->addChild(box);

    return true;
}