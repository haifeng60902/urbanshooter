#ifndef _SNIPER_H_
#define _SNIPER_H_

#include <game/Weapon.h>

class Sniper : public Weapon
{
public:

	//15 balles, 5 par chargeur
	Sniper() : Weapon("./datas/Dragunov.osg",15, 5)
	{}

	~Sniper(){};
};

#endif //_SNIPER_H_

