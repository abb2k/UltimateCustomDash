#include <include.h>

#include <Geode/modify/MenuLayer.hpp>

#include "customNightLayer.h"
class $modify(MenuLayer){
    void onMoreGames(CCObject* o){
        customNightLayer::create()->EnterLayer();
    }
    bool init() {
        if (!MenuLayer::init()) return false;

        return true;
    }
    
};
