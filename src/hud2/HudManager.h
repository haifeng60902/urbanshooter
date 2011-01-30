#ifndef _HUDMANAGER_H
#define _HUDMANAGER_H

#include <string>
#include <deque>
#include <queue>
#include <osg/Timer>
#include <osg/Group>

#include <OpenThreads/mutex>

#include <utility/Macros.h>

class HudText;
class DisplaySetting;

/** Singleton to manage the Hud */
class HudManager {

public :


	/** Callback managing the pop of the hudText when they have expired */
	class TextsUpdateCallback : public osg::NodeCallback
	{
	public:
		METADATA(TextsUpdateCallback);

		TextsUpdateCallback(HudManager * manager) : _manager( manager ) {}

		void operator()(osg::Node * node, osg::NodeVisitor * nv);

	protected:
		~TextsUpdateCallback(){};

	private:

		HudManager * _manager;
	};


	/** Insertion mode */
	enum Mode {
		INSERT_AT_TOP,
		INSERT_AT_BOTTOM
	};



	/** stack of orders of add, to be done in the updateCallback */
	typedef std::queue< std::string > TextStack;


	/** list of instance of HudTexts
	 *	First is the instance, second is the creation time
	 *	The list is ordered : new element are added at the end
	 */
	typedef std::deque< std::pair< HudText *, osg::Timer_t > > HudTexts;


	/** Insert a new text */
	static void pushText(const std::string & text);

	/** Delete the instance */
	static void deleteInstance();

	/** get the instance */
	static HudManager * getInstance();

	void setUpHudOnRootNode(osg::Group* root);
	void setMode(Mode m);

	/** Get the display Settings */
    inline DisplaySetting * getDisplaySettings();

	/** Set the display settings */
    void setDisplaySettings(DisplaySetting * value);

	/** get the root node to attach to the graph */
	osg::ref_ptr< osg::Group > getRootNode();

	/** get the texts list */
	HudTexts * getHudTexts(){ return &_hudTexts; }



protected:

	/** Destructor */
    ~HudManager();


private:

	
	/** Constructor */
	HudManager(Mode mode = INSERT_AT_TOP);

	/** singleton instance */
	static HudManager * _instance;

	/** Insert the text into waiting list 
	 *	Warning : To insert a text call pushText()
	*/
	void pushTextInList(const std::string & text);


	/** Add a text 
	 */
	void addText(const std::string & text);

	/** remove an expired hudText */
	void removeText(HudText * hudText);



	/** Texts list 
	 *	Pair : instance, expire time
	 */
	HudTexts _hudTexts;

	/** Setting of the display */
    DisplaySetting * _displaySettings;

	/** insertion mode */
    Mode _mode;

	/** Group to attach the texts */
	osg::ref_ptr< osg::Group > _group;

	/** stack of texts to add */
	TextStack _textToAddStack;

	/** mutex of the textStack */
	OpenThreads::Mutex _TestToAddStackMutex;
};

inline DisplaySetting * HudManager::getDisplaySettings() {
  return _displaySettings;
}

#endif
