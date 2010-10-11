#ifndef _CALLBACK_MANAGER_TEST_H_
#define _CALLBACK_MANAGER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include <osg/Group>
#include <osg/NodeCallback>

#include <Hud/Macros.h>

class CallbackManagerTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( CallbackManagerTest );
	CPPUNIT_TEST( add );
	CPPUNIT_TEST( remove );
	CPPUNIT_TEST_SUITE_END();

private:

	osg::ref_ptr<osg::Group> _group;
	osg::ref_ptr<osg::NodeCallback> _callback1;
	osg::ref_ptr<osg::NodeCallback> _callback2;
	


public:
	void setUp();
	void tearDown();

	void add();
	void remove();

	//not a test
	void runCallbacks();

};


/** CallbackTest1 */
class CallbackTest1 : public osg::NodeCallback
{
public :

	METADATA(CallbackTest1);

	CallbackTest1()
	{};


	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		//concat callback number in the node name
		node->setName( node->getName() + "1" );
		traverse(node,nv);
	}
};

/** CallbackTest2 */
class CallbackTest2 : public osg::NodeCallback
{
public :
	
	METADATA(CallbackTest2);

	CallbackTest2()
	{};


	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		//concat callback number in the node name
		node->setName( node->getName() + "2" );
		traverse(node,nv);
	}
};


#endif //_CALLBACK_MANAGER_TEST_H_

