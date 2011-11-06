#ifndef _STATE_HUD_H_
#define _STATE_HUD_H_

#include <osg/Camera>
#include <osgText/Text>

class Weapon;

//class for amo hud and scores
class StateHud : public osg::Camera
{

public:
	StateHud();
	~StateHud();

private:

	void createAmoGeometry();

	Weapon * _weapon; //use a setter that will rebuild/refresh the 

	//text for amo total
	//callback de MAJ ou alors une notification directe

	osg::ref_ptr<osgText::Text> _totalBullet;
};

#endif //_STATE_HUD_H_
