
#include <HudManager.h>
#include <HudText.h>
#include <DisplaySetting.h>

#include <osg/Timer>

#include <OpenThreads/ScopedLock>

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


HudManager::HudManager() {

	//init values
	_displaySettings = new DisplaySetting();
	_group = new osg::Group;

	setInsertMode(INSERT_AT_BOTTOM);
	

	//set the callback on the texts root node
	_group->setUpdateCallback(new TextsUpdateCallback(this));
}

HudManager::~HudManager() {
	
	_hudTexts.clear();
	
	while(!_textToAddStack.empty())
		_textToAddStack.pop();

	delete _displaySettings;
	_displaySettings = NULL;

}

void HudManager::setAnimationMode(AnimationMode m){
	HudManager::getInstance()->setAnimMode(m);
}

void HudManager::setAnimMode(AnimationMode m){
	_animMode = m;
}

void HudManager::setInsertMode(InsertMode m){
	HudManager::getInstance()->setInsMode(m); 
}

void HudManager::setInsMode(InsertMode m){
	_insertMode = m; 
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
	//insert the text into a waiting list
	getInstance()->pushTextInList(text);
}


void HudManager::pushTextInList(const std::string & text)
{
	//lock the stack and push the message
	OpenThreads::ScopedLock<OpenThreads::Mutex> mylock(_TestToAddStackMutex);
	_textToAddStack.push(text);

}

void HudManager::addText(const std::string & text) 
{

	//position of the new hudtext
	osg::Vec3 position;

	if(_insertMode == INSERT_AT_TOP)
	{
		//position is the (height + 5) + last text position along Y
		osg::Vec3 lastPosition;
		if(_hudTexts.empty())
			position = osg::Vec3(0,0,0); //Y axis deplacement
		else
			position = osg::Vec3(0,(_displaySettings->getHeight() + 5) + _hudTexts.back().first->getPosition().y() ,0); //Y axis deplacement

	}
	else //INSERT_AT_BOTTOM
	{
		position = osg::Vec3(0,0,0);

		//decal each old txt to the top
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


	if(_animMode == TRANSLATION || _animMode == TRANSLATION_AND_TRANSPARENCY)
	{
		//TODO
			//3. set the transparency callback on it (0 to 1)
				//careful with the bg transparency
	}

	if(_animMode == TRANSPARENCY || _animMode == TRANSLATION_AND_TRANSPARENCY)
	{
		//TODO
			//4. set the transparency callbcak on the one which will be removed (1 to 0)
				//careful with the bg transparency
			//5. set animation callback on each one
	}
			//all callback will be removed by themselves

}


void HudManager::removeText(HudText * hudText)
{
	_group->removeChild(hudText);
	
	//remove it from the list
	_hudTexts.pop_front();

	//TODO : callback of animation should be removed too (unless if they remove themselves
}


void HudManager::TextsUpdateCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{

	//test if the head elements are ready to be removed. if true, ask for remove them
	HudTexts * texts = _manager->getHudTexts();

	//get the timer only once, it can make a little time difference, but the optimization is
	//better than the precision here
	osg::Timer_t actual = osg::Timer::instance()->tick();


	//First remove texts
	if(texts->size() > 0)
	{
		bool stopRemoving = false;

		while(!stopRemoving && texts->size() > 0)
		{
			//compare actual with text begin time + duration
			float duration = osg::Timer::instance()->delta_s(texts->front().second, actual);
			
			if(duration >= _manager->getDisplaySettings()->getVisibleTime())
				_manager->removeText(texts->front().first);
			else
				stopRemoving = true;
		}
	}


	//Now add texts
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> mylock(_manager->_TestToAddStackMutex);

		while(!_manager->_textToAddStack.empty())
		{
			_manager->addText(_manager->_textToAddStack.front());
			_manager->_textToAddStack.pop();
		}


	}

	traverse(node,nv);
}