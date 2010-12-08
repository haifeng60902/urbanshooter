
#include <hud2/HudManager.h>
#include <hud2/HudText.h>
#include <hud2/DisplaySetting.h>

#include <osg/Timer>

HudManager * HudManager::_instance = NULL;

void HudManager::deleteInstance()
{
	if(_instance)
		delete _instance;
	_instance = NULL;
}

HudManager * HudManager::getInstance()
{
	if(!_instance)
		_instance = new HudManager();
	
	return _instance;
}


HudManager::HudManager(Mode mode) {

	//TODO : use mode
	//init values
	_displaySettings = new DisplaySetting();
	_group = new osg::Group;

	//set the callback on the texts root node
	_group->setUpdateCallback(new ExpiryCallback(this));
}

HudManager::~HudManager() {
	
	_hudTexts.clear();
	
	delete _displaySettings;
	_displaySettings = NULL;

}


void HudManager::setMode(Mode m){
	_mode = m; 
}


void HudManager::setUpHudOnRootNode(osg::Group* root)
{
	// create a camera to set up the projection and model view matrices, and the subgraph to drawn in the HUD
    osg::Camera* camera = new osg::Camera;

    // set the projection matrix
    camera->setProjectionMatrix(osg::Matrix::ortho2D(0,1280,0,1024));
	

    // set the view matrix    
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());

    // only clear the depth buffer
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);

    // draw subgraph after main camera view.
    camera->setRenderOrder(osg::Camera::POST_RENDER);

    // we don't want the camera to grab event focus from the viewers main camera(s).
    camera->setAllowEventFocus(false);

	camera->addChild(_group);

	root->addChild(camera);
}


osg::ref_ptr< osg::Group > HudManager::getRootNode()
{
	return _group;
}


void HudManager::setDisplaySettings(DisplaySetting * value) {
  _displaySettings = value;
}

void HudManager::pushText(const std::string & text)
{  
	getInstance()->addText(text);
}

void HudManager::addText(const std::string & text) 
{

	//TODO

	osg::Vec3 position;

	if(_mode == INSERT_AT_TOP)
	{
		//position is the (height + 5) * nb_txts along Y
		position = osg::Vec3(0,(_displaySettings->getHeight() + 5) * _hudTexts.size(),0); //Y axis deplacement
	}
	else //INSERT_AT_BOTTOM
	{
		position = osg::Vec3(0,0,0);

		//decal each old txt
		osg::Vec3 decal = osg::Vec3(0,_displaySettings->getHeight() + 5,0);
		for(unsigned int i = 0 ; i < _hudTexts.size() ; ++i)
			_hudTexts.at(i).first->setPosition(_hudTexts.at(i).first->getPosition() + decal);
	}


	//1. create a new instance of text
	HudText * ht = new HudText(text, _displaySettings);
	ht->setPosition(ht->getPosition() + position);
	
	//2. add it to the end of the list and in the graph
	_hudTexts.push_back(std::make_pair(ht, osg::Timer::instance()->tick()));
	_group->addChild(ht);

			//3. set the transparency callback on it (0 to 1)
				//careful with the bg transparency

			//4. set the transparency callbcak on the one which will be removed (1 to 0)
				//careful with the bg transparency
			//5. set animation callback on each one

			//all callback will be removed by themselves


	//remove from the list (done by expirycallback) and from the graph (in this order, graph is ref_counted)


}


void HudManager::removeText(HudText * hudText)
{
	_group->removeChild(hudText);
}


void HudManager::ExpiryCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{

	//test if the head element is ready to be removed. it true, ask for remove it
	HudTexts * texts = _manager->getHudTexts();

	osg::Timer_t actual = osg::Timer::instance()->tick();

	if(texts->size() > 0)
	{

		//compare actual with text begin time + duration
		float duration = osg::Timer::instance()->delta_s(texts->front().second, actual);
		
		if(duration >= _manager->getDisplaySettings()->getVisibleTime())
		{
			_manager->removeText(texts->front().first);
			//remove it from the list
			texts->pop_front();
		}
	}

	traverse(node,nv);
}