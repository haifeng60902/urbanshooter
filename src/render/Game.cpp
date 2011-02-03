#include <render/Game.h>

#include <osgDB/readFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <render/WeaponHandler.h>

#include <render/GameManager.h>
#include <render/Sniper.h>

#include <hud/HudManager.h>

#include <animation/ProgressiveTransparencyCallback.h>
#include <animation/CallbackManager.h>

#include <render/MyHandler.h>


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
	//_viewer->setUpViewOnSingleScreen(0);
	_viewer->setUpViewInWindow(50,50,800,600,0);

	_viewer->addEventHandler(new osgViewer::StatsHandler());

	//add debug handler
	_viewer->addEventHandler(new MyHandler());

	//default camera manipulator
	_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );


	_weaponHandler = new WeaponHandler();
	_viewer->addEventHandler(_weaponHandler);

	
	GameManager::instance()->getWeaponManager()->setWeapon(new Sniper());
	GameManager::instance()->setView(_viewer);
	

	return true;
}



bool Game::loadDatas()
{
	osg::Group* g = new osg::Group();

	osg::ref_ptr< osg::Node> node = osgDB::readNodeFile("D:/Codage/OSG_2.8.2/sources/data/cessna.osg");
	g->addChild(node);
	

	//Set Up the dynamic Hud
	HudManager::getInstance()->setUpHudOnRootNode(g);


	//HudManager::setInsertMode(HudManager::INSERT_AT_TOP);
	HudManager::setInsertMode(HudManager::INSERT_AT_BOTTOM);

	//HudManager::pushText(std::string("coucou lily :-)"));
	/*HudManager::pushText(std::string("coucou lily :-)"));
	HudManager::pushText(std::string("coucou chaton :-)"));
	HudManager::pushText(std::string("coucou lily :-)"));
	HudManager::pushText(std::string("coucou lily :-)"));
	HudManager::pushText(std::string("coucou moi :-p"));
	HudManager::pushText(std::string("1 :-p"));
	HudManager::pushText(std::string("2 :-p"));*/


	CallbackManager::addNodeCallback(node, new ProgressiveTransparencyCallback(1.0, 0.0, 2.0, 4.0));

	_viewer->setSceneData( g );

	return node.valid();
}

int Game::run()
{
	return _viewer->run();
}