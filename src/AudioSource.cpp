#include "AudioSource.h"

std::vector<AudioSource*> audioSources;

AudioSource* AudioSource::create(std::string soundFile, FMOD_MODE mode, VolumeChannel volumeChannel, bool startPaused, float _CustomVolume, bool usesGeodeResourcesPath) {
    auto ret = new AudioSource();
    if (ret && ret->init(soundFile, mode, volumeChannel, startPaused, _CustomVolume, usesGeodeResourcesPath, false, 0)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

AudioSource* AudioSource::createEffect(std::string soundFile, VolumeChannel volumeChannel, float deleteTime, float _CustomVolume, bool usesGeodeResourcesPath){
    auto ret = new AudioSource();
    if (ret && ret->init(soundFile, FMOD_DEFAULT, volumeChannel, false, _CustomVolume, usesGeodeResourcesPath, true, deleteTime)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool AudioSource::init(std::string soundFile, FMOD_MODE mode, VolumeChannel volumeChannel, bool startPaused, float _CustomVolume, bool usesGeodeResourcesPath, bool isEffect, float deleteTime){
    engin = FMODAudioEngine::sharedEngine();

    gm = GameManager::sharedState();

    StartPaused = startPaused;

    pausedState = startPaused;

    CustomVolume = _CustomVolume;

    volType = volumeChannel;

    if (usesGeodeResourcesPath){
        std::string modid = "resources/"_spr;
        std::string p = "geode/unzipped/" + modid + soundFile;
        engin->m_system->createSound(p.c_str(), mode, nullptr, &sound);
    }
    else {
        std::string p = "Resources/" + soundFile;
        engin->m_system->createSound(p.c_str(), mode, nullptr, &sound);
    }

    _isEffect = isEffect;
    _deleteTime = deleteTime;

    engin->m_system->createChannelGroup("UCDMUsic", &channelGroup);

    audioSources.insert(audioSources.end(), this);

    UpdateAudio();

    CCScheduler::get()->resumeTarget(this);

    return true;
}

void AudioSource::onEnter(){
    CCLayer::onEnter();

    engin->m_system->playSound(sound, nullptr, StartPaused, &channel);

    if (!_isEffect){
        //channel->setChannelGroup(channelGroup);
    }

    if (_isEffect){
        runAction(CCSequence::create(CCDelayTime::create(_deleteTime), CCCallFunc::create(this, callfunc_selector(AudioSource::OnEffectRemoved)), nullptr));
    }

    UpdateAudio();
}

void AudioSource::changeSound(std::string Sound, FMOD_MODE mode, bool startPaused, bool usesGeodeResourcesPath){
    channel->stop();

    if (usesGeodeResourcesPath){
        std::string modid = "resources/"_spr;
        std::string p = "geode/unzipped/" + modid + Sound;
        engin->m_system->createSound(p.c_str(), mode, nullptr, &sound);
    }
    else {
        std::string p = "Resources/" + Sound;
        engin->m_system->createSound(p.c_str(), mode, nullptr, &sound);
    }

    engin->m_system->playSound(sound, nullptr, startPaused, &channel);

    UpdateAudio();
}

void AudioSource::onExit(){
    CCLayer::onExit();
    CleanUpSound();
    deleteMeFromList();
}

void AudioSource::Paused(bool isPaused){
    bool pause;
    channel->getPaused(&pause);
    if (pause != isPaused){
        channel->setPaused(isPaused);
        pausedState = isPaused;
    }
    UpdateAudio();
}

void AudioSource::RemoveMeAndCleanUpSound(){
    channel->stop();

    sound->release();

    deleteMeFromList();

    removeMeAndCleanup();
}

void AudioSource::CleanUpSound(){
    channel->stop();

    sound->release();
}

void AudioSource::setCustomVolume(float Volume){
    CustomVolume = Volume;
    UpdateAudio();
}

void AudioSource::MuteAudio(bool Mute){
    Muted = Mute;
}

void AudioSource::UpdateAudio(){
    if (!Muted){
        switch (volType)
        {
        case Music:
            channel->setVolume(engin->m_musicVolume);
            break;
        case SFX:
            channel->setVolume(engin->m_sfxVolume);
            break;
        case Custom:
            channel->setVolume(CustomVolume);
            break;
        }
    }
    else {
        channel->setVolume(0);
    }
    //engin->m_system->update();
}

void AudioSource::OnEffectRemoved(){
    RemoveMeAndCleanUpSound();
}

void AudioSource::deleteMeFromList(){
    for (size_t i = 0; i < audioSources.size(); i++)
    {
        if (audioSources[i] == this){
            audioSources.erase(std::next(audioSources.begin(), i));
        }
    }
}

void AudioSource::ChangePriority(int priority){
    channel->setPriority(priority);
}

void AudioSource::update(float delta){

}