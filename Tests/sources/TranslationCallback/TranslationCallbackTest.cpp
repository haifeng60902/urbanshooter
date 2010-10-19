#include <TranslationCallback/TranslationCallbackTest.h>

#include <animation/TranslationCallback.h>
#include <animation/CallbackManager.h>
#include <Utility.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TranslationCallbackTest );


void TranslationCallbackTest::setUp()
{
	_pat = new osg::PositionAttitudeTransform;
	_pat->setPosition( osg::Vec3d( 0, 0, 0) );
}


void TranslationCallbackTest::tearDown()
{
	//no need to delete the _pat, ref_prt will do it
}

void TranslationCallbackTest::timeZero()
{
	osg::Vec3d goal(10,5,2);

	osg::ref_ptr<TranslationCallback> tc =  new TranslationCallback(goal, 0.);

	CallbackManager::addNodeCallback(_pat, tc);


	//run the callbacks
	Utility::runCallbacks(_pat);

	//pat must be at origin position, the translation begin at the second traverse
	CPPUNIT_ASSERT(_pat->getPosition() == osg::Vec3d( 0, 0, 0));


	//run teh callback
	Utility::runCallbacks(_pat);

	//pat must be at origin position, the translation begin at the second traverse
	CPPUNIT_ASSERT(_pat->getPosition() == goal);

}


void TranslationCallbackTest::timeNormal()
{
	osg::Vec3d goal(10,5,2);
	double duration = 1.0;

	osg::ref_ptr<TranslationCallback> tc =  new TranslationCallback(goal, duration);

	CallbackManager::addNodeCallback(_pat, tc);


	//run the callbacks
	Utility::runCallbacks(_pat);

	//firt loop until duration/2.0 : check is the pat is half-way
	osg::Timer_t begin = osg::Timer::instance()->tick();
	osg::Timer_t actual = begin;

	//loop half of the time
	while( osg::Timer::instance()->delta_s(begin, actual) < duration/2.0 )
	{
		Utility::runCallbacks(_pat);
		actual = osg::Timer::instance()->tick();
	}

	//check that the pat is in the middle
	CPPUNIT_ASSERT(_pat->getPosition().length2() < goal.length2() && _pat->getPosition().length2() > 0. );
	//check the scalar
	CPPUNIT_ASSERT(_pat->getPosition() * goal  == _pat->getPosition().length() * goal.length());


	//second loop test if the goal is reached
	while( osg::Timer::instance()->delta_s(begin, actual) <= duration )
	{
		Utility::runCallbacks(_pat);
		actual = osg::Timer::instance()->tick();
	}

	//pat must be at origin position, the translation begin at the second traverse
	CPPUNIT_ASSERT(_pat->getPosition() == goal);
}