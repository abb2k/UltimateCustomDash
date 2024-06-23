#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class AudioSource : public cocos2d::CCLayer {
public:
    typedef enum VolumeChannel{
        Music,
        SFX,
        Custom
    } VolumeChannel;

    void OnEffectRemoved();

protected:
    virtual bool init(std::string soundFile, FMOD_MODE mode, VolumeChannel volumeChannel, bool startPaused, float _CustomVolume, bool usesGeodeResourcesPath, bool isEffect, float deleteTime);

    virtual void onExit();

    virtual void onEnter();

    bool Muted = false;

    bool StartPaused;

    virtual void update(float delta);
public:
    static AudioSource* create(std::string soundFile, FMOD_MODE mode, VolumeChannel volumeChannel, bool startPaused = false, float _CustomVolume = 1, bool usesGeodeResourcesPath = true);

    static AudioSource* createEffect(std::string soundFile, VolumeChannel volumeChannel, float deleteTime, float _CustomVolume = 1, bool usesGeodeResourcesPath = true);

    void changeSound(std::string Sound, FMOD_MODE mode, bool startPaused = false, bool usesGeodeResourcesPath = true);

    void Paused(bool isPaused);

    void RemoveMeAndCleanUpSound();

    void CleanUpSound();

    void setCustomVolume(float Volume);

    void MuteAudio(bool Mute);

    void UpdateAudio();

    FMOD::Sound* sound = nullptr;
    FMOD::Channel* channel = nullptr;

    FMODAudioEngine* engin;

    GameManager* gm;

    FMOD::ChannelGroup* channelGroup = nullptr;

    VolumeChannel volType;

    float CustomVolume;

    bool pausedState;

    bool _isEffect;

    float _deleteTime;

    void deleteMeFromList();

    void ChangePriority(int priority);
};

extern std::vector<AudioSource*> audioSources;