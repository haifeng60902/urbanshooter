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


void CallbackList::addCallback( osg::NodeCallback * callback, int index)
{
	if( index < 0 || index >= (int)_callbackList.size() )
	{
		_callbackList.push_back(std::make_pair(callback->className(), callback));
	}
	else
	{
		//put iterator on next element before insertion
		CallbackCallList::iterator it = _callbackList.begin() + index;
		_callbackList.insert(it , std::make_pair(callback->className(), callback));
	}
}

void CallbackList::removeCallback( const std::string & name, bool remove_all_instances)
{

	for(CallbackCallList::iterator it = _callbackList.begin(); it != _callbackList.end() ; )
	{
		if(it->first.compare(name) == 0)
		{
			//no incrementation in this case
			it = _callbackList.erase(it);
			
			if(!remove_all_instances)
				return;
		}
		else
			++it;
	}

}