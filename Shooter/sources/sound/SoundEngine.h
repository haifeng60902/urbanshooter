#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <manager/Engine.h>

class SoundEngine : public Engine
{
public:
	SoundEngine();
	~SoundEngine();

	void frame();
};

#endif //_SOUND_ENGINE_H_

