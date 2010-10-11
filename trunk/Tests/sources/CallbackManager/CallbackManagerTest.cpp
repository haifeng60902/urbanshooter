#include <CallbackManager/CallbackManagerTest.h>
#include <osgUtil/UpdateVisitor>

#include <Hud/CallbackManager.h>
#include <Hud/HudText.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CallbackManagerTest );


void CallbackManagerTest::setUp()
{
	_group = new osg::Group();
	_group->setName("");

	//create the two callbacks
	_callback1 = new CallbackTest1();
	_callback2 = new CallbackTest2();
}


void CallbackManagerTest::tearDown()
{
	_group->setUpdateCallback(NULL);

	//nothing else to delete, the ref_ptr will do it
}


void CallbackManagerTest::runCallbacks()
{
	//simulate a callback visitor from the update event of the viewer
	osg::ref_ptr<osgUtil::UpdateVisitor> _updateVisitor = new osgUtil::UpdateVisitor;
	
	_updateVisitor->reset();
	_updateVisitor->setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);

	//traverse the graph
	_group->accept(*_updateVisitor);

}


void CallbackManagerTest::add()
{

	//add callback 1, then callback 2
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback2);

	// call the callbacks
	runCallbacks();

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("12") == 0);

	//add again n°1 twice
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback1);

	// call the callbacks
	runCallbacks();

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("121211") == 0);

}


void CallbackManagerTest::remove()
{

	//add callback 1, then callback 2
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback2);
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback1);

	// call the callbacks
	runCallbacks(); //result "1211"

	//remove callback 2
	CallbackManager::removeNodeCallback(_group, "CallbackTest2");

	// call the callbacks
	runCallbacks(); //result "1211+111"


	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1211111") == 0);


	//add callback 2
	//remove callback 1 (first instance)
	CallbackManager::addNodeCallback(_group, _callback2);
	CallbackManager::removeNodeCallback(_group, "CallbackTest1");

		
	// call the callbacks
	runCallbacks(); //result "1211111 + 112"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1211111112") == 0);


	//remove all
	CallbackManager::removeNodeCallback(_group, "CallbackTest1");
	CallbackManager::removeNodeCallback(_group, "CallbackTest1");
	CallbackManager::removeNodeCallback(_group, "CallbackTest2");


	// call the callbacks (no callbacks)
	runCallbacks(); //result "1211111112"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1211111112") == 0);

}
