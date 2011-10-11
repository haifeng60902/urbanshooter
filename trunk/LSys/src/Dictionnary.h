#ifndef LSYS_DICTIONNARY_H
#define LSYS_DICTIONNARY_H


//associate some Element to graphical elements
class Dictionnary
{
public:

	class DictionnaryEntity
	{
		bool isOperator();

	

		bool isOperator(Element);
		//ok pr la detection mais l'interpretation des operators ??
		//Les operators sont forcément des elements dans le graph 


		osg::Group * getTranslation(Element); //if not operator
		//switch avec les types d'element... ou alors un systeme de register 
		//et de reclaration avec un Element et un group...

	};


private:

};


/*
GraphicalEntity
{
	_geode
}

F -> group avec enfant
B -> group sans enfant
[ -> NA
] -> NA
- -> tranform -20°
+ -> tranform +20°

*/
#endif //LSYS_DICTIONNARY_H
