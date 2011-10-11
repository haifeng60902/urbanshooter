#ifndef LSYS_GENERATOR_H
#define LSYS_GENERATOR_H

#include <Regle.h>

//generate the L-System
class Generator
{
public:
	Generator(Regle r, Elements begin);
	~Generator();


	//reset all
	void reset();
	
	//pass and return the total pass number
	int pass();

	//print the result
	void printGeneration();

	//get the generation
	Elements getGeneration();

private:
	
	//number of passes
	int _passNum;
	Elements _generation;
	Regle _regle;
	
};

#endif //LSYS_GENERATOR_H
