#ifndef _SNIPER_H_
#define _SNIPER_H_



class Sniper : public Weapon
{
public:

	//15 balles, 5 par chargeur
	Sniper() : Weapon(15, 5)
	{}

	~Sniper(){};

};


#endif //_SNIPER_H_

