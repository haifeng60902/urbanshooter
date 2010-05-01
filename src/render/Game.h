#ifndef _GAME_H_
#define _GAME_H_

#include <osgViewer/Viewer>


class WeaponHandler;

/** Entry point*/
class Game
{
public :

	/** Constructor */
	Game();

	/**Destructor */
	~Game();

	/** Initialize the scene */
	bool init();

	/** Loading data*/
	bool loadDatas();

	/**Run the game */
	int run();

private:

	/** renderer */
	osg::ref_ptr<osgViewer::Viewer> _viewer;

	
	WeaponHandler* _weaponHandler;


};


#endif //_GAME_H_

