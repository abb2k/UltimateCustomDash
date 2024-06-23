#include <include.h>

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "Geode/modify/AppDelegate.hpp"

#include "customNightLayer.h"

class $modify(MenuLayer){
    void onMoreGames(CCObject* o){
        customNightLayer::create()->EnterLayer(0.5f);
    }
    bool init() {
        if (!MenuLayer::init()) return false;

        return true;
    }
    
};

class $modify(AppDelegate){
    void applicationDidEnterBackground(){
        AppDelegate::applicationDidEnterBackground();

        for (size_t i = 0; i < audioSources.size(); i++)
        {
            if (audioSources[i] != nullptr){
                audioSources[i]->channel->setPaused(true);
            }
        }
        
    }
    void applicationWillEnterForeground(){
        AppDelegate::applicationWillEnterForeground();

        for (size_t i = 0; i < audioSources.size(); i++)
        {
            if (audioSources[i] != nullptr){
                audioSources[i]->channel->setPaused(audioSources[i]->pausedState);
            }
        }
    }
};