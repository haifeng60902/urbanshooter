#ifndef _UTILITY_H_
#define _UTILITY_H_


#include <osgUtil/UpdateVisitor>

class Utility
{
public:

	//simulate an update() event.
	static void runCallbacks(osg::Node* n)
	{
		//simulate a callback visitor from the update event of the viewer
		osg::ref_ptr<osgUtil::UpdateVisitor> _updateVisitor = new osgUtil::UpdateVisitor;

		_updateVisitor->reset();
		_updateVisitor->setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);

		//traverse the graph
		n->accept(*_updateVisitor);
	}
};

#endif //_UTILITY_H_
