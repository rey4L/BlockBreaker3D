#ifndef AUDIO_CLASS_H
#define AUDIO_CLASS_H

#include <irrKlang/irrKlang.h>

class Audio {
public:
	Audio();
	~Audio();

	void playBackgroundMusic();
	void playCollisionSound();

private:
	irrklang::ISoundEngine* engine;
};

#endif
