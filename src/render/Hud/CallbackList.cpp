#include <Hud/CallbackList.h>

CallbackList::CallbackList()
{

}

CallbackList::~CallbackList()
{

}

void CallbackList::operator()(osg::Node* node, osg::NodeVisitor* nv)
{

	//call each callback of the list
	for(CallbackCallList::iterator it = _callbackList.begin(); it != _callbackList.end() ; ++it)
		(*((*it).second.get()))(node, nv);

	//continue graph traverse
	traverse(node, nv);
}


void CallbackList::addCallback( osg::NodeCallback * callback)
{
	_callbackList.push_back(std::make_pair(callback->className(), callback));
}

void CallbackList::removeCallback( const std::string & name)
{

	for(CallbackCallList::iterator it = _callbackList.begin(); it != _callbackList.end() ; ++it)
	{
		if(it->first.compare(name) == 0)
		{
			_callbackList.erase(it);
			return;
		}
	}

}