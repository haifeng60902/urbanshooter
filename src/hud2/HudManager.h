#ifndef _HUDMANAGER_H
#define _HUDMANAGER_H

#include <string>
#include <deque>
#include <osg/Timer>
#include <osg/Group>

#include <utility/Macros.h>

class HudText;
class DisplaySetting;

/** Singleton to manage the Hud */
class HudManager {

public :


	/**callback pour gerer le pop des txts */
	class ExpiryCallback : public osg::NodeCallback
	{
	public:
		METADATA(ExpiryCallback);

		ExpiryCallback(HudManager * manager) : _manager( manager ) {}

		void operator()(osg::Node * node, osg::NodeVisitor * nv);

	protected:
		~ExpiryCallback(){};

	private:

		HudManager * _manager;
	};


	/** Insertion mode */
	enum Mode {
		INSERT_AT_TOP,
		INSERT_AT_BOTTOM
	};

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

	/** Add a text 
	 *	to insert a text call pushText()
	 */
	void addText(const std::string & text);

	/** Get the display Settings */
    inline DisplaySetting * getDisplaySettings();

	/** Set the display settings */
    void setDisplaySettings(DisplaySetting * value);

	/** get the root node to attach to the graph */
	osg::ref_ptr< osg::Group > getRootNode();

	/** get the texts list */
	HudTexts * getHudTexts(){ return &_hudTexts; }

	/** remove an expired hudText */
	void removeText(HudText * hudText);

protected:

	/** Destructor */
    ~HudManager();


private:

	
	/** Constructor */
	HudManager(Mode mode = INSERT_AT_TOP);

	/** singleton instance */
	static HudManager * _instance;

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

};

inline DisplaySetting * HudManager::getDisplaySettings() {
  return _displaySettings;
}

#endif
