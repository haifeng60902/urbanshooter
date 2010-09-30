#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


int main()
{
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( suite );

	std::filebuf fb;
	fb.open("UnitTestResults.xml",std::ios::out);
	std::ostream ouput(&fb);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter( new CppUnit::XmlOutputter( &runner.result(),
													   ouput ) );
	// Run the tests.
	runner.run();

	return 0;
}