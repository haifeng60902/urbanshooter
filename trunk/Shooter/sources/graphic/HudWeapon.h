#ifndef _HUD_WEAPON_H_
#define _HUD_WEAPON_H_

#include <osg/Camera>
#include <osg/PositionAttitudeTransform>

//hud to attach the weapon to the camera
class HudWeapon : public osg::Camera
{
public:
	HudWeapon();
	~HudWeapon();

	void setWeaponRoot( osg::PositionAttitudeTransform * pat );

private:
	osg::ref_ptr<osg::Group> _weaponRoot;
};


#endif //_HUD_WEAPON_H_
