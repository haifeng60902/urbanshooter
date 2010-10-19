#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <render/WeaponManager.h>

class GameManager
{
public:

	static GameManager* instance()
	{
		if(!_gm)
			_gm = new GameManager();
		return _gm;
	}

	static void deleteInstance()
	{
		if(_gm)
			delete _gm;
		_gm = NULL;
	}


	WeaponManager * getWeaponManager()
	{
		return _wm;
	}

	void setView(osgViewer::Viewer* v)
	{ 
		_view = v;
	}

	osgViewer::Viewer * getView()
	{
		return _view;
	}

private:

	GameManager()
	{
		_wm = new WeaponManager();
	}

	~GameManager();

	static GameManager* _gm;



	WeaponManager* _wm;
	osgViewer::Viewer* _view;


};


#endif //_GAME_MANAGER_H_