
#include <render/Game.h>


int main(int argc, char** argv)
{

	Game * game = new Game();

	game->init();
	game->loadDatas();
	
	return game->run();

}
