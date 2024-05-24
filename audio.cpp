#include "audio.h"
#include "interface.h"
#include <iostream>

Audio::Audio() {
    engine = irrklang::createIrrKlangDevice();
    backgroundMusic = nullptr;
    backgroundMusicVolume = 0.25f;
    soundEffectsVolume = 0.40f;
    isBackgroundMusicPlaying = false;
}

// Destructor that will trigger when the local instance goes out of scope
Audio::~Audio() {
    if (engine) {
        engine->drop();
    }
}

void Audio::playBackgroundMusic() {
    if (engine) {
        backgroundMusic = engine->play2D("media/bgm.wav", true, false, true);
        backgroundMusic->setVolume(backgroundMusicVolume);
        isBackgroundMusicPlaying = true;
    }
}

void Audio::playCollisionSound() {
    if (engine) {
        engine->play2D("media/collision.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playResponseSound() {
    if (engine) {
        engine->play2D("media/beep.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playPowerUpSound() {
    if (engine) {
        engine->play2D("media/power-up.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playResetSound() {
    if (engine) {
        engine->play2D("media/reset.wav", false, false, true)->setVolume(soundEffectsVolume);
    }
}

void Audio::playGameOverSound() {
    if (engine) {
        engine->play2D("media/game-over.wav", false, false, true)->setVolume(soundEffectsVolume);
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