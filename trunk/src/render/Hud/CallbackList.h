#ifndef _CALLBACK_LIST_H_
#define _CALLBACK_LIST_H_


#include <Hud/Macros.h>

#include <osg/Node>
#include <string>
#include <vector>

/** Implements a simple callback able to call a list of NodeCallback.
 *	This is a tool to allow having more than one callback on a simple node
 */

//TODO : class pour add/remove en utilisant le callbackList : transparence a l'utilisation + doc doxygen avec exemple et tout

class CallbackList : public osg::NodeCallback
{
public:

	CallbackList();
	~CallbackList();

	METADATA(CallbackList);


	/** operator of the callback */
	void operator()(osg::Node* node, osg::NodeVisitor* nv);

	/** Add a new callaback */
	void addCallback( osg::NodeCallback * callback);

	/** Remove an existing callback */
	void removeCallback( const std::string & name);

private:

	/** List of callbacks based on the className */
	typedef std::vector< std::pair< std::string, osg::ref_ptr< osg::NodeCallback > > > CallbackCallList;
	CallbackCallList _callbackList;

};

#endif //_CALLBACK_LIST_H_

