#include <Hud/CallbackList.h>

CallbackList::CallbackList()
{
	_running  = false;
}

CallbackList::~CallbackList()
{

}

void CallbackList::operator()(osg::Node* node, osg::NodeVisitor* nv)
{

	_running = true;

	//call each callback of the list
	for(CallbackCallList::iterator it = _callbackList.begin(); it != _callbackList.end() ; ++it)
	{
		if((*it).second.valid())
			(*((*it).second.get()))(node, nv);
	}

	_running  = false;

	//continue graph traverse
	traverse(node, nv);


	//flush callback that auto-delete themselves
	flushWaitingElementToRemove();
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
	//stack the entity to be removed
	_remStack.push_back( std::make_pair( name, remove_all_instances ) );

	if(!_running)
	{
		flushWaitingElementToRemove();
	}
}


void CallbackList::flushWaitingElementToRemove()
{
	//for each element of the wating list, remove one or all its instances
	for(RemoveEntityStack::iterator its = _remStack.begin(); its != _remStack.end(); ++its)
		for(CallbackCallList::iterator it = _callbackList.begin(); it != _callbackList.end() ; )
			{
				if(it->first.compare(its->first) == 0)
				{
					//no incrementation in this case
					it = _callbackList.erase(it);
					
					if(!its->second)
						break;
				}
				else
					++it;
			}


	_remStack.clear();
}
