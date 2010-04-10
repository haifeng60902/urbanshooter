#ifndef _WEAPON_HANDLER_H_
#define _WEAPON_HANDLER_H_


#include <osgGA/GUIEventHandler>



class WeaponHandler : public osgGA::GUIEventHandler 
{
public:

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);



};





#endif //_WEAPON_HANDLER_H_

