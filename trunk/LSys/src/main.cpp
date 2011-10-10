

#include <Generator.h>

int main(int argc, char* argv[])
{

	Regle regle;
	regle.add(Element('A'), Regle::fromString("B"));
	regle.add(Element('B'), Regle::fromString("AB"));

	Generator g(regle, Regle::fromString("A"));


	int passNum = 0;
	g.printGeneration();

	while( passNum <= 6)
	{
		passNum = g.pass();
		g.printGeneration();
	}
	

	return 0;
}