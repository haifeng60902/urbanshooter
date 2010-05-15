#include <Game.h>

#include <osgDB/readFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <WeaponHandler.h>

#include <GameManager.h>
#include <Sniper.h>

#include <Hud.h>

#include <ProgressiveTransparencyCallback.h>


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

	_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );


	_weaponHandler = new WeaponHandler();
	_viewer->addEventHandler(_weaponHandler);

	
	GameManager::instance()->getWeaponManager()->setWeapon(new Sniper());
	GameManager::instance()->setView(_viewer);
	


//	_viewer->setCameraManipulator(new osgGA::DriveManipulator());

	return true;
}

#include <osg/Material>

#include <NodeCollector.h>

bool Game::loadDatas()
{
	osg::Group* g= new osg::Group();

	osg::ref_ptr< osg::Node> node = osgDB::readNodeFile("D:/Codage/OSG_2.8.2/sources/data/cessna.osg");
	g->addChild(node);
	
	g->addChild(Hud::setUpCamera());

	//node->setUpdateCallback(new ProgressiveTransparencyCallback(5.0,3.0));


		osg::ref_ptr<osg::StateSet> stateset = node->getOrCreateStateSet();
		stateset->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
        stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//	stateset->setDataVariance(osg::Object::DYNAMIC);
	//	stateset->setRenderBinDetails(11, "DepthSortedBin");


		osg::Material* _material = dynamic_cast<osg::Material*>( stateset->getAttribute(osg::StateAttribute::MATERIAL) );

		if(!_material)
			_material = new osg::Material;

		_material->setColorMode(osg::Material::AMBIENT);
		/*_material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1, 1, 1, 1));
		_material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1, 1, 1, 1));
		_material->setShininess(osg::Material::FRONT_AND_BACK, 64.0f);*/
		_material->setAlpha(osg::Material::FRONT_AND_BACK, 0.2);
		stateset->setAttributeAndModes(_material, osg::StateAttribute::ON);

        stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);



		//NodeCollector nc;
		std::vector<osg::Geode*> geodes = NodeCollector::collect<osg::Geode>(g);



	_viewer->setSceneData( g );

	return node.valid();
}

int Game::run()
{
	return _viewer->run();
}