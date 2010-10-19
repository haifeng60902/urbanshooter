#ifndef _HUDMANAGER_H_
#define _HUDMANAGER_H_

#include <hud/HudTextRoot.h>


namespace HudTest
{

	/** Manage the HUD 
	 * 	based on a singleton
	*/
	class HudManager
	{

	public:

		/** get or create the instance 
		 * 	@return valid instance of the HudManager
		*/
		static HudManager * getInstance();

		/** delete the instance */
		static void deleteInstance();

		/** Display the text in the hud
		 * 	@param[in] text text to display
		*/
		void display(const std::string & text);

		/** SetUp the Hud on the camera
		 * 	@param camera on which set the hud
		*/
		void setUpHudOnCamera(osg::Camera* cam);

	private:
		/** private constructor */
		HudManager();

		/** private destructor */
		~HudManager();

		/** instance of the class */
		static HudManager * _instance;

		/** Head class of the hud */
		HudTextRoot * _hudTextRoot;
	};

};

#endif //_HUDMANAGER_H_

