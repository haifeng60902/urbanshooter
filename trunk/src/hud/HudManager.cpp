#include <hud/HudManager.h>

//initialize the instance to null
HudTest::HudManager * HudTest::HudManager::_instance = NULL;


HudTest::HudManager::HudManager()
{
	//instanciate the member
	_hudTextRoot = new HudTextRoot();
}
	
HudTest::HudManager::~HudManager()
{
	//delete the hudTextRoot
	delete _hudTextRoot;
	_hudTextRoot = NULL;
}


HudTest::HudManager * HudTest::HudManager::getInstance()
{
	//test if the instance as already been set, if not then do it
	if(!_instance)
	{
		_instance = new HudManager();
	}
	
	return _instance;
}


void HudTest::HudManager::deleteInstance()
{
	if(_instance)
		delete _instance;

	_instance = NULL;
}

void HudTest::HudManager::display(const std::string &text)
{
	//add a new item in the HudTextRoot
	_hudTextRoot->addText(text);
}


void HudTest::HudManager::setUpHudOnCamera(osg::Camera* cam)
{
	if(cam)
		cam->addChild(_hudTextRoot);
}
