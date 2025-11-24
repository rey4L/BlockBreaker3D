#include "audio/audio.h"
#include "ui/interface.h"
#include <iostream>

#ifdef BLOCKBREAKER3D_ENABLE_AUDIO

Audio::Audio() {
    engine = irrklang::createIrrKlangDevice();
    backgroundMusic = nullptr;
    backgroundMusicVolume = 0.25f;
    soundEffectsVolume = 0.40f;
    isBackgroundMusicPlaying = false;
}

Audio::~Audio() {
    if (engine) {
        engine->drop();
    }
}

void Audio::playBackgroundMusic() {
    if (engine) {
        backgroundMusic = engine->play2D("assets/audio/bgm.wav", true, false, true);
        backgroundMusic->setVolume(backgroundMusicVolume);
        isBackgroundMusicPlaying = true;
    }
}

void Audio::playCollisionSound() {
    if (engine) {
        engine->play2D("assets/audio/collision.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playResponseSound() {
    if (engine) {
        engine->play2D("assets/audio/beep.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playPowerUpSound() {
    if (engine) {
        engine->play2D("assets/audio/power-up.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playResetSound() {
    if (engine) {
        engine->play2D("assets/audio/reset.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playGameOverSound() {
    if (engine) {
        engine->play2D("assets/audio/game-over.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::setBackgroundMusicVolume(float volume) {
    backgroundMusicVolume = volume;
    if (backgroundMusic) {
        backgroundMusic->setVolume(backgroundMusicVolume);
    } 
}

void Audio::setSoundEffectsVolume(float volume) {
    soundEffectsVolume = volume;
}

void Audio::stopBackgroundMusic() {
    if (engine && backgroundMusic) {
        backgroundMusic->stop();
        backgroundMusic->drop();
		backgroundMusic = nullptr;
        isBackgroundMusicPlaying = false;
    }
}

#else

Audio::Audio() {
    engine = nullptr;
    backgroundMusic = nullptr;
    backgroundMusicVolume = 0.25f;
    soundEffectsVolume = 0.40f;
    isBackgroundMusicPlaying = false;
}

Audio::~Audio() = default;

void Audio::playBackgroundMusic() {
    isBackgroundMusicPlaying = true;
}

void Audio::playCollisionSound() {}

void Audio::playResponseSound() {}

void Audio::playPowerUpSound() {}

void Audio::playResetSound() {}

void Audio::playGameOverSound() {}

void Audio::setBackgroundMusicVolume(float volume) {
    backgroundMusicVolume = volume;
}

void Audio::setSoundEffectsVolume(float volume) {
    soundEffectsVolume = volume;
}

void Audio::stopBackgroundMusic() {
    isBackgroundMusicPlaying = false;
}

#endif