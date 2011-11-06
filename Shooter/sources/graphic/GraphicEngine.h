#ifndef _GRAPHIC_ENGINE_H_
#define _GRAPHIC_ENGINE_H_

#include <manager/Engine.h>

#include <osgViewer/Viewer>
#include <osg/Group>
#include <graphic/StateHud.h>
#include <graphic/FPSManipulator.h>

class Weapon;
class HudWeapon;

class GraphicEngine : public Engine
{
public:
	GraphicEngine();
	~GraphicEngine();


	void frame();

	bool isValid();

	void initialize();

	void setActiveWeapon( Weapon * w ); 

	void setBulletNum(int num);
	void setScore(int score);
	void setRemainingTime(int time);
	void setCurrentLoaderBulletNum(int num);

	void animateManipulator();

private:

	osg::ref_ptr<osgViewer::Viewer> _viewer;
	osg::ref_ptr<osg::Group> _root;

	osg::ref_ptr<osg::PositionAttitudeTransform> _activeWeapon;

	osg::ref_ptr<HudWeapon> _hudWeapon;
	osg::ref_ptr<StateHud>	_stateHud;

	osg::ref_ptr<FPSManipulator> _fps;
};

#endif