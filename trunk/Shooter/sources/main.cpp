#include <iostream>

#include <manager/GameManager.h>

int main()
{
	std::cout << "Hello Developpez.com ! " << std::endl;



	GameManager gm("./config/config.txt");

	gm.initialize();

	gm.run();


	return 0;

}