#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <manager/Engine.h>

class SoundEngine : public Engine
{
public:
	SoundEngine();
	~SoundEngine();

	void frame();
	bool isValid();
	void initialize();
};

#endif //_SOUND_ENGINE_H_

