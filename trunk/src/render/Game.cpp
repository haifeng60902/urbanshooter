#include <Game.h>

#include <osgDB/readFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <WeaponHandler.h>


Game::Game()
{
	_viewer = NULL;
	_weaponHandler  = NULL;
}

Game::~Game()
{
	delete _weaponHandler;
	_weaponHandler = NULL;
}


bool Game::init()
{
	_viewer = new osgViewer::Viewer();
	_viewer->setUpViewInWindow(50,50,800,600,0);

	_viewer->addEventHandler(new osgViewer::StatsHandler());

	_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );


	_weaponHandler = new WeaponHandler();
	_viewer->addEventHandler(_weaponHandler);
	

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