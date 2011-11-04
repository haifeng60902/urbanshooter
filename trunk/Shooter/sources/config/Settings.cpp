#include <config/Settings.h>

#include <config/ConfigFile.h>


Settings::Settings(const std::string & configFilePath):
	screenNum( 0 ) //default value
{
	if(configFilePath.empty())
		return;


	ConfigFile config( configFilePath );

	config.readInto( screenNum, "screenNum" );



}

Settings::~Settings()
{
}
