#include <config/Settings.h>

#include <config/ConfigFile.h>


Settings::Settings(const std::string & configFilePath):
	screenNum( 0 ) //default value
{
	if(configFilePath.empty())
		return;


	ConfigFile config( configFilePath );

	config.readInto( screenNum, "screenNum" );
	config.readInto( enableEventHandler, "enableEventHandler" );
	config.readInto( viewFinderRed, "viewFinderRed" );
	config.readInto( viewFinderGreen, "viewFinderGreen" );
	config.readInto( viewFinderBlue, "viewFinderBlue" );
	config.readInto( viewFinderWidth, "viewFinderWidth" );
	config.readInto( screenShotKey, "screenShotKey" );
	config.readInto( mouseScale, "mouseScale" );


}

Settings::~Settings()
{
}
