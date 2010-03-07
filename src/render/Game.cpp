#include <Game.h>

Game::Game()
{
	_viewer = NULL;
}

Game::~Game()
{

}


bool Game::init()
{
	_viewer = new osgViewer::Viewer();
	_viewer->setUpViewInWindow(50,50,1200,800,1);

	return true;
}

int Game::run()
{
	return _viewer->run();
}