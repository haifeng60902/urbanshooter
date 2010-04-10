#include <Game.h>

#include <osgDB/readFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <WeaponManager.h>


Game::Game()
{
	_viewer = NULL;
	_weaponManager  = NULL;
}

Game::~Game()
{
	delete _weaponManager;
	_weaponManager = NULL;
}


bool Game::init()
{
	_viewer = new osgViewer::Viewer();
	_viewer->setUpViewInWindow(50,50,1200,800,1);

	_viewer->addEventHandler(new osgViewer::StatsHandler());

	_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );


	_weaponManager = new WeaponManager(_viewer);

	return true;
}


bool Game::loadDatas()
{
	osg::ref_ptr< osg::Node> node = osgDB::readNodeFile("D:/Codage/OSG_2.8.2/sources/data/avatar.osg");
	_viewer->setSceneData( node );

	return node.valid();
}

int Game::run()
{
	return _viewer->run();
}