#ifndef _CALLBACK_MANAGER_H_
#define _CALLBACK_MANAGER_H_

#include <osg/NodeCallback>

/** 
 *	\class CallbackManager
 *	\brief Class to manage the callback list on each node instead of the user himself
 */
class CallbackManager
{
public:

	/** 
	 *	Add a callback on a node callback's list
	 *	@param[in] node node where to add the callback
	 *	@param[in] callback callback instance to add on node
	 *	@param[in] index callback index in the index list. From 0 to n. if n > size of the list, callback will be added
	 *	in queue. -1 is for add in queue.
	 */
	static void addNodeCallback(osg::Node * node, osg::NodeCallback * callback, int index = -1);

	/** 
	 *	Remove a callback on a node callback's list
	 *	@param[in] node node where to remove the callback
	 *	@param[in] name classname of the callback
	 *	@param[in] all_instances remove all instances of this callback, or just the first one.
	 */
	static void removeNodeCallback(osg::Node * node, const std::string & name, bool all_instances = false);

};

#endif //_CALLBACK_MANAGER_H_

