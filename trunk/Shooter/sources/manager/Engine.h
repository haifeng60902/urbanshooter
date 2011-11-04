#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdio.h> //for NULL definition

class GameEngine;
class GraphicEngine;
class SoundEngine;

//base class for engines
class Engine
{
public :
	Engine() : 
	   _game ( NULL ),
	   _graphic ( NULL ),
	   _sound( NULL )
	{}

	~Engine()
	{}

	//called each frame
	virtual void frame()=0;


	inline GameEngine * getGameEngine(){ return _game; }
	void setGameEngine(GameEngine * game){ _game = game; }

	inline GraphicEngine * getGraphicEngine(){ return _graphic; }
	void setGraphicEngine(GraphicEngine * graphic){ _graphic = graphic; }

	inline SoundEngine * getSoundEngine(){ return _sound; }
	void setSoundEngine(SoundEngine * sound){ _sound = sound; }


private:

	GameEngine *	_game;
	GraphicEngine * _graphic;
	SoundEngine *	_sound;

};

#endif //_ENGINE_H_
