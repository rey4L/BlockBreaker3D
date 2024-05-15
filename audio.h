#ifndef AUDIO_CLASS_H
#define AUDIO_CLASS_H

#include <irrKlang/irrKlang.h>

class Audio {
public:
	Audio();
	~Audio();

	void playBackgroundMusic();
	void playCollisionSound();
	void playResponseSound();
	void playGameOverSound();
	void setBackgroundMusicVolume(float volume);
	void setSoundEffectsVolume(float volume);
	void stopBackgroundMusic();

private:
	irrklang::ISoundEngine* engine;
	irrklang::ISound* backgroundMusic;
	float backgroundMusicVolume;
	float soundEffectsVolume;
};

#endif
