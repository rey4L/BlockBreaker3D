#include "audio.h"
#include "interface.h"

Audio::Audio() {
    engine = irrklang::createIrrKlangDevice();
    backgroundMusic = nullptr;
    backgroundMusicVolume = 0.025f;
    soundEffectsVolume = 1.0f;
}

// Destructor that will trigger when the local instance goes out of scope
Audio::~Audio() {
    if (engine) {
        engine->drop();
    }
}

void Audio::playBackgroundMusic() {
    if (engine) {
        backgroundMusic = engine->play2D("media/J.ogg", true, false, true);
        backgroundMusic->setVolume(backgroundMusicVolume);
    }
}

void Audio::playCollisionSound() {
    if (engine) {
        engine->play2D("media/collision.wav", false, false, true)->setVolume(soundEffectsVolume);
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