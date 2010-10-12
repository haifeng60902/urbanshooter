#ifndef _CALLBACK_LIST_H_
#define _CALLBACK_LIST_H_


#include <Hud/Macros.h>

#include <osg/Node>
#include <string>
#include <vector>

/** Implements a simple callback able to call a list of NodeCallback.
 *	This is a tool to allow having more than one callback on a simple node
 */
class CallbackList : public osg::NodeCallback
{
public:

	CallbackList();
	~CallbackList();

	//not mandatory, but keep consistency
	METADATA(CallbackList);


	/** operator of the callback */
	void operator()(osg::Node* node, osg::NodeVisitor* nv);

	/** Add a new callaback 
	 *	@param[in] callback nodeCallback to add
	 *	@param[in] index index where to insert the callback. default (-1) is in queue
	 */
	void addCallback( osg::NodeCallback * callback, int index = -1);

	/** Remove an existing callback 
	 *	@param[in] name name of the callback (will call className())
	 *	@param[in] remove_all_instances remove all instances of the callback if true, else just the first one
	 */
	void removeCallback( const std::string & name, bool remove_all_instances = false);

private:

	/** List of callbacks based on the className */
	typedef std::vector< std::pair< std::string, osg::ref_ptr< osg::NodeCallback > > > CallbackCallList;
	CallbackCallList _callbackList;

};

#endif //_CALLBACK_LIST_H_

