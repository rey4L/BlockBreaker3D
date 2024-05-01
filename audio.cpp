#include "audio.h"

Audio::Audio() {
    engine = irrklang::createIrrKlangDevice();
}

// Destructor that will trigger when the local instance goes out of scoper
Audio::~Audio() {
    if (engine) {
        engine->drop();
    }
}

void Audio::playBackgroundMusic() {
    if (engine) {
        engine->play2D("media/J.ogg", true);
    }
}

void Audio::playCollisionSound() {
    if (engine) {
        engine->play2D("media/collision.wav", false);
    }
}