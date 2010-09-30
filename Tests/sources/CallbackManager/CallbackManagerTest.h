#ifndef _CALLBACK_MANAGER_H_
#define _CALLBACK_MANAGER_H_

#include <cppunit/extensions/HelperMacros.h>

#include <osg/Group>

class CallbackManagerTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( CallbackManagerTest );
	CPPUNIT_TEST( myTest );
	CPPUNIT_TEST_SUITE_END();

private:

	osg::ref_ptr<osg::Group> group;
	osg::ref_ptr<osg::NodeCallback> _callback1;
	osg::ref_ptr<osg::NodeCallback> _callback2;
	
	
	//TODO : viewer pour appeler les callback ?	
/*
    _updateVisitor = new osgUtil::UpdateVisitor;
	
	_updateVisitor->reset();
    _updateVisitor->setFrameStamp(getFrameStamp());
    _updateVisitor->setTraversalNumber(getFrameStamp()->getFrameNumber());

	_updateVisitor->getTraversalMode(); ??

	node->accept(*_updateVisitor);
*/

public:
	void setUp();
	void tearDown();

	void myTest();



};


#endif //_CALLBACK_MANAGER_H_

