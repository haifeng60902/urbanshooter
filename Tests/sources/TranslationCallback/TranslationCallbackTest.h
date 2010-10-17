#ifndef _TRANSLATION_CALLBACK_TEST_H_
#define _TRANSLATION_CALLBACK_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include <osg/PositionAttitudeTransform>


class TranslationCallbackTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( TranslationCallbackTest );
	CPPUNIT_TEST( timeZero );
	CPPUNIT_TEST( timeNormal );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void timeZero();
	void timeNormal();

private:
	osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

};



#endif //_TRANSLATION_CALLBACK_TEST_H_

