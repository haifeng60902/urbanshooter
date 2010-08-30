#include <Game.h>

#include <osgDB/readFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <WeaponHandler.h>

#include <GameManager.h>
#include <Sniper.h>

#include <Hud.h>
#include <Hud/HudManager.h>

#include <ProgressiveTransparencyCallback.h>

#include <MyHandler.h>


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
	_viewer->setUpViewOnSingleScreen(1);
	//_viewer->setUpViewInWindow(50,50,800,600,0);

	_viewer->addEventHandler(new osgViewer::StatsHandler());

	//add debug handler
	_viewer->addEventHandler(new MyHandler());


	_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );


	_weaponHandler = new WeaponHandler();
	_viewer->addEventHandler(_weaponHandler);

	
	GameManager::instance()->getWeaponManager()->setWeapon(new Sniper());
	GameManager::instance()->setView(_viewer);
	


//	_viewer->setCameraManipulator(new osgGA::DriveManipulator());

	return true;
}



bool Game::loadDatas()
{
	osg::Group* g = new osg::Group();

	osg::ref_ptr< osg::Node> node = osgDB::readNodeFile("D:/Codage/OSG_2.8.2/sources/data/cessna.osg");
	g->addChild(node);
	
	//create the HUD base
	osg::Camera * cam = Hud::setUpCamera();
	g->addChild(cam);

	//Set Up the dynamic Hud
	HudTest::HudManager::getInstance()->setUpHudOnCamera(cam);
	HudTest::HudManager::getInstance()->display(std::string("coucou lily :-)"));
	HudTest::HudManager::getInstance()->display(std::string("coucou lily :-)"));
	HudTest::HudManager::getInstance()->display(std::string("coucou chaton :-)"));
	HudTest::HudManager::getInstance()->display(std::string("coucou lily :-)"));
	HudTest::HudManager::getInstance()->display(std::string("coucou lily :-)"));
	HudTest::HudManager::getInstance()->display(std::string("coucou moi :-p"));
	HudTest::HudManager::getInstance()->display(std::string("1 :-p"));
	HudTest::HudManager::getInstance()->display(std::string("2 :-p"));


	node->setUpdateCallback(new ProgressiveTransparencyCallback(5.0,3.0));
	

	_viewer->setSceneData( g );

	return node.valid();
}

int Game::run()
{
	return _viewer->run();
}