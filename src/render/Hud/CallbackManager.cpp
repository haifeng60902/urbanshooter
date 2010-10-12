#include <Hud/CallbackManager.h>

#include <Hud/CallbackList.h>


void CallbackManager::addNodeCallback(osg::Node *node, osg::NodeCallback *callback, int index)
{
	if(!node || !callback)
		return;

	osg::ref_ptr<CallbackList> list = NULL;

	//check if the node have a callback list
	list = dynamic_cast<CallbackList*>( node->getUpdateCallback() );
	
	//if not, create it
	if(!list.valid())
	{
		list = new CallbackList();
		node->setUpdateCallback(list);
	}


	//if true, add the callback to the list
	list->addCallback(callback, index);
	
}


void CallbackManager::removeNodeCallback(osg::Node *node, const std::string &name, bool all_instances)
{
	if(!node || name.empty())
		return;

	osg::ref_ptr<CallbackList> list = NULL;

	//check if the node have a callback list
	list = dynamic_cast<CallbackList*>( node->getUpdateCallback() );

	if(list.valid())
	{
		list->removeCallback(name, all_instances);
	}

}