#ifndef _HUD_H_
#define _HUD_H_

#include <osg/camera>

class Hud
{

public:

	Hud();
	~Hud();

	static osg::Camera* setUpCamera();

};

#endif //_HUD_H_

