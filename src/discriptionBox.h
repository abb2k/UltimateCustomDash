#pragma once
#include <include.h>

class discriptionBox : public cocos2d::CCLayer {
protected:
    virtual bool init(std::string _name, std::string _discription);
public:
    static discriptionBox* create(std::string _name, std::string _discription);

    std::string discription;
    std::string Name;
};