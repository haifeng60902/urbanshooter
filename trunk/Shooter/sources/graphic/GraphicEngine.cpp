#include <graphic/GraphicEngine.h>

#include <config/Settings.h>
#include <osgDB/readFile>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <graphic/HudViewFinder.h>
#include <graphic/EventHandler.h>
#include <graphic/HudWeapon.h>

#include <game/Weapon.h>

GraphicEngine::GraphicEngine()
{
	//get config settings to create the view
	_viewer = new osgViewer::Viewer();

	_root = new osg::Group;

	_hudWeapon = NULL;

	_activeWeapon = new osg::PositionAttitudeTransform();
	_activeWeapon->setPosition(osg::Vec3(1100,100,0));//1280*1024
	_activeWeapon->setScale(osg::Vec3d(5,5,5)); 

}

GraphicEngine::~GraphicEngine()
{
	
}

void GraphicEngine::initialize()
{
	if(getSettings()->enableEventHandler)
		_viewer->addEventHandler(new osgViewer::StatsHandler());
	
	//add screenshot handler
	osgViewer::ScreenCaptureHandler* sch = new osgViewer::ScreenCaptureHandler();
	sch->setKeyEventTakeScreenShot(getSettings()->screenShotKey);
	_viewer->addEventHandler(sch);
	

	//DEBUG
	_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );


	_viewer->setUpViewOnSingleScreen(getSettings()->screenNum);
//	_viewer->setUpViewInWindow(50,50,1280,1024,1);


	_viewer->addEventHandler(new EventHandler(getGameEngine()));

	_viewer->setSceneData(_root);

	_root->addChild(osgDB::readNodeFile("D:/Codage/OSG_2.8.2/sources/data/cow.osg"));

	//attach the view finder
	_root->addChild(new HudViewFinder(getSettings()->viewFinderRed,getSettings()->viewFinderGreen,getSettings()->viewFinderBlue,getSettings()->viewFinderWidth));

	//attach the hud weapon
	_hudWeapon = new HudWeapon();
	_hudWeapon->setWeaponRoot(_activeWeapon);
	_root->addChild(_hudWeapon);

}

bool GraphicEngine::isValid()
{
	if(_viewer.valid())
		return !(_viewer->done());
	else
		return false;
}

void GraphicEngine::frame()
{
	_viewer->frame();
}

void GraphicEngine::setActiveWeapon( Weapon * w )
{
	//load the file
	osg::Node * node = osgDB::readNodeFile(w->getFileName());
	if(node)
		_activeWeapon->addChild(node);

}
