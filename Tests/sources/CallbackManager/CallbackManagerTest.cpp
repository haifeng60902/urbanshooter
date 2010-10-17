#include <CallbackManager/CallbackManagerTest.h>

#include <Hud/CallbackManager.h>
#include <Hud/HudText.h>

#include <Utility.h>

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


void CallbackManagerTest::add()
{

	//add callback 1, then callback 2
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback2);

	// call the callbacks
	Utility::runCallbacks(_group);

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("12") == 0);

	//add again n°1 twice
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback1);

	// call the callbacks
	Utility::runCallbacks(_group);

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
	Utility::runCallbacks(_group); //result "1211"

	//remove callback 2
	CallbackManager::removeNodeCallback(_group, "CallbackTest2");

	// call the callbacks
	Utility::runCallbacks(_group); //result "1211+111"


	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1211111") == 0);


	//add callback 2
	//remove callback 1 (first instance)
	CallbackManager::addNodeCallback(_group, _callback2);
	CallbackManager::removeNodeCallback(_group, "CallbackTest1");

		
	// call the callbacks
	Utility::runCallbacks(_group); //result "1211111 + 112"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1211111112") == 0);


	//remove all
	CallbackManager::removeNodeCallback(_group, "CallbackTest1");
	CallbackManager::removeNodeCallback(_group, "CallbackTest1");
	CallbackManager::removeNodeCallback(_group, "CallbackTest2");


	// call the callbacks (no callbacks)
	Utility::runCallbacks(_group); //result "1211111112"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1211111112") == 0);

}


void CallbackManagerTest::insert()
{
	//add callback sequence :  1 2 1 1, then insert 2 : begin, middle, end

	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback2);
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback1);

	CallbackManager::addNodeCallback(_group, _callback2, 0); //begin
	CallbackManager::addNodeCallback(_group, _callback2, 10); //end
	CallbackManager::addNodeCallback(_group, _callback2, 4); //middle


	// call the callbacks
	Utility::runCallbacks(_group); //result "2121212"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("2121212") == 0);

}


void CallbackManagerTest::removeall()
{
	//121122
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback2);
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback1);
	CallbackManager::addNodeCallback(_group, _callback2);
	CallbackManager::addNodeCallback(_group, _callback2);

	//remove first instance of callback 2
	CallbackManager::removeNodeCallback(_group, "CallbackTest2"); 

	// call the callbacks
	Utility::runCallbacks(_group); //result "11122"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("11122") == 0);



	//remove all instance of callback 1
	CallbackManager::removeNodeCallback(_group, "CallbackTest1", true); 

	// call the callbacks
	Utility::runCallbacks(_group); //result "11122+22"

	//the callback have been run in the good order
	CPPUNIT_ASSERT(_group->getName().compare("1112222") == 0);


}