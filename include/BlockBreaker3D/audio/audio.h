#ifndef AUDIO_CLASS_H
#define AUDIO_CLASS_H

#ifdef BLOCKBREAKER3D_ENABLE_AUDIO
#include <irrKlang/irrKlang.h>
#endif

class Audio {
public:
	Audio();
	~Audio();

	void playBackgroundMusic();
	void playCollisionSound();
	void playResponseSound();
	void playPowerUpSound();
	void playResetSound();
	void playGameOverSound();
	void setBackgroundMusicVolume(float volume);
	void setSoundEffectsVolume(float volume);
	void stopBackgroundMusic();
	bool isBackgroundMusicPlaying;

private:
#ifdef BLOCKBREAKER3D_ENABLE_AUDIO
	irrklang::ISoundEngine* engine;
	irrklang::ISound* backgroundMusic;
#else
	void* engine;
	void* backgroundMusic;
#endif
	float backgroundMusicVolume;
	float soundEffectsVolume;
};

#endif
