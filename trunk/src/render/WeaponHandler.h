#ifndef _WEAPON_HANDLER_H_
#define _WEAPON_HANDLER_H_


#include <osgGA/GUIEventHandler>

class WeaponManager;


class WeaponHandler : public osgGA::GUIEventHandler 
{
public:

	WeaponHandler();
	~WeaponHandler();

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:

	WeaponManager* _wm;


};





#endif //_WEAPON_HANDLER_H_

