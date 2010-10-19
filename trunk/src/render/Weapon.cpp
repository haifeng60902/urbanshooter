#include <render/Weapon.h>

#include <osgDB/ReadFile>

Weapon::Weapon(unsigned int nb_balles, unsigned int capacite_chargeur)
{
	_capacite_chargeur = capacite_chargeur;
	_nb_balles = nb_balles;
}


Weapon::~Weapon()
{
}


unsigned int Weapon::GetNbChargeur()
{
	return _nb_balles/_capacite_chargeur + 1;
}


unsigned int Weapon::GetNbBallesDansChageur()
{
	return _nb_balles % _capacite_chargeur;
}

unsigned int Weapon::GetNbBalles()
{
	return _nb_balles;
}


void Weapon::Tire()
{
	_nb_balles--;
	osg::notify(osg::ALWAYS) << "PAN !! " << std::endl; //play sound

	osg::notify(osg::NOTICE) << "Reste " << GetNbBalles() << " dans " << GetNbChargeur() << " chargeurs" << std::endl;

}


bool Weapon::LoadModel(std::string filename)
{
	osg::ref_ptr< osg::Node > model = osgDB::readNodeFile(filename);
	
	if(model.valid())
		return this->addChild(model);
	else
		return false;
}