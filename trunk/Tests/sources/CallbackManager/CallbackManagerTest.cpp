#include <CallbackManager/CallbackManagerTest.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CallbackManagerTest );

void CallbackManagerTest::setUp()
{
	_group = new osg::Group();

	//create the two callbacks
}


void CallbackManagerTest::tearDown()
{
}


void CallbackManagerTest::myTest()
{
	CPPUNIT_FAIL("not done yet");
}
