#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <manager/Engine.h>

class WeaponManager;

//manage the game
class GameEngine : public Engine
{
public:

	GameEngine();
	~GameEngine();

	void frame();
	bool isValid();
	void initialize();

	void onLeftClic();

private:

	WeaponManager* _weaponManager;
};


#endif //_GAME_ENGINE_H_
