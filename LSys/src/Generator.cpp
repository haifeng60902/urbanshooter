
#include <Generator.h>

#include <iostream>
#include <string>


Generator::Generator(Regle r, Elements begin) :
	_regle( r ),
	_generation( begin ), 
	_passNum( 0 )
{}

Generator::~Generator()
{}

void Generator::reset()
{
	_regle.clear();
	_passNum = 0;
	_generation.clear();
}


void Generator::printGeneration()
{
	std::string res;
	for(unsigned int i = 0; i < _generation.size() ; ++i)
		res += _generation.at(i).get();

	std::cout << "Pass number : " << _passNum 
		<< " Generation : " << res
		<< std::endl;
}

Elements Generator::getGeneration()
{
	return _generation;
}


int Generator::pass()
{

	//for each element of the genration, apply the rule
	Elements newGeneration;

	//generate the new generation
	for(unsigned int i = 0; i < _generation.size() ; ++i)
	{
		Elements el = _regle.get(_generation.at(i) );
		
		//if not found, just copy the element
		if(el.empty())
			newGeneration.push_back( _generation.at(i));
		else
			for(unsigned int j=0 ; j<el.size() ; ++j)
				newGeneration.push_back( el.at(j) );
	}
	
	//erase ole generation by new
	_generation = newGeneration;

	//this was one generation
	_passNum++;

	return _passNum;
}