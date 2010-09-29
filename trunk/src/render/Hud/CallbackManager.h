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
	 */
	static void addNodeCallback(osg::Node * node, osg::NodeCallback * callback);

	/** 
	 *	Remove a callback on a node callback's list
	 *	@param[in] node node where to remove the callback
	 *	@param[in] name classname of the callback
	 */
	static void removeNodeCallback(osg::Node * node, const std::string & name);

};

#endif //_CALLBACK_MANAGER_H_

