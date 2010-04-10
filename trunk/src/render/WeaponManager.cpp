#include <WeaponManager.h>

#include <WeaponHandler.h>

WeaponManager::WeaponManager(osgViewer::Viewer* v)
{
	_weapon = NULL;
	setHandler(v);
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::setHandler(osgViewer::Viewer* v)
{
	if(v)
		v->addEventHandler(new WeaponHandler());
		
}