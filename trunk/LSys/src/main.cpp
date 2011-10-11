

#include <Generator.h>

int main(int argc, char* argv[])
{

	Regle regle;
	regle.add(Element('B'), Regle::fromString("F[-B]+B"));
	regle.add(Element('F'), Regle::fromString("FF"));

	Generator g(regle, Regle::fromString("B"));


	int passNum = 0;
	g.printGeneration();

	while( passNum <= 3)
	{
		passNum = g.pass();
		g.printGeneration();
	}
	

	return 0;
}