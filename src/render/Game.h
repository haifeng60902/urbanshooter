#ifndef _GAME_H_
#define _GAME_H_

#include <osgViewer/Viewer>

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

	/**Run the game */
	int run();

private:

	/** renderer */
	osg::ref_ptr<osgViewer::Viewer> _viewer;


};


#endif //_GAME_H_

