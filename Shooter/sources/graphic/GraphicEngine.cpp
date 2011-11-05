#include <graphic/GraphicEngine.h>

#include <config/Settings.h>
#include <osgDB/readFile>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include <graphic/HudViewFinder.h>
#include <graphic/EventHandler.h>

GraphicEngine::GraphicEngine()
{
	//get config settings to create the view
	_viewer = new osgViewer::Viewer();

	_root = new osg::Group;


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


	_root->addChild(new HudViewFinder(getSettings()->viewFinderRed,getSettings()->viewFinderGreen,getSettings()->viewFinderBlue,getSettings()->viewFinderWidth));
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