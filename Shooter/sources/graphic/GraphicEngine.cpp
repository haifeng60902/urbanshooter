#include <graphic/GraphicEngine.h>

#include <config/Settings.h>
#include <osgDB/readFile>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <graphic/HudViewFinder.h>
#include <graphic/EventHandler.h>
#include <graphic/HudWeapon.h>
#include <graphic/FPSManipulator.h>

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
	//_viewer->setCameraManipulator( new osgGA::TrackballManipulator() );

	FPSManipulator * fps = new FPSManipulator(getSettings()->mouseScale);
	_viewer->setCameraManipulator( fps );

	

#ifdef _DEBUG
	_viewer->setUpViewInWindow(50,50,1280,1024,1);
#else
	_viewer->setUpViewOnSingleScreen(getSettings()->screenNum);
#endif


	_viewer->addEventHandler(new EventHandler(getGameEngine()));

	_viewer->setSceneData(_root);

	//load the scene
	_root->addChild(osgDB::readNodeFile("./datas/level.osg"));




	//attach the hud view finder
	_root->addChild(new HudViewFinder(getSettings()->viewFinderRed,getSettings()->viewFinderGreen,getSettings()->viewFinderBlue,getSettings()->viewFinderWidth));

	//attach the hud weapon
	_hudWeapon = new HudWeapon();
	_hudWeapon->setWeaponRoot(_activeWeapon);
	_root->addChild(_hudWeapon);

	//attach the hud state
	_stateHud = new StateHud();
	_root->addChild(_stateHud);



	//disable cursor
	osgViewer::Viewer::Windows windows; 
	_viewer->getWindows(windows); 
	for(osgViewer::Viewer::Windows::iterator itr = windows.begin();	itr != windows.end();++itr) 
	{
		(*itr)->useCursor(false); 
		//allow the manipulator to move the cursor
		fps->setGW((*itr));
	}

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
	{
		_activeWeapon->addChild(node);
		_stateHud->setBulletCountInLoader( w->GetCapaciteChargeur());
	}

}

void GraphicEngine::setBulletNum(int num)
{
	_stateHud->setTotalBullet( num );
}

void GraphicEngine::setScore(int num)
{
	_stateHud->setScore( num );
}

void GraphicEngine::setRemainingTime(int num)
{
	_stateHud->setchrono( num );
}

void GraphicEngine::setCurrentLoaderBulletNum(int num)
{
	_stateHud->setCurrentBulletCountInLoader( num );
}
