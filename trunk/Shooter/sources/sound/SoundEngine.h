#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <manager/Engine.h>

#include <fmod.hpp>

class SoundEngine : public Engine
{
public:
	SoundEngine();
	~SoundEngine();

	void frame();
	bool isValid();
	void initialize();

	void playFire();
	void playReload();
	void playEmpty();

private:
	FMOD::System    *system;

	FMOD::Sound* _fireSound;
	FMOD::Sound* _reloadSound;
	FMOD::Sound* _emptySound;
	
};

#endif //_SOUND_ENGINE_H_

