#ifndef _HUDTEXT_H
#define _HUDTEXT_H

#include <osg/PositionAttitudeTransform>
#include <osgText/Text>

class DisplaySetting;

/** Text representation */
class HudText : public osg::PositionAttitudeTransform
{
	
public:

	/** Constructor */
	HudText(const std::string & text, DisplaySetting * ds);

protected :

	/** Destructor */
    ~HudText();


private:
	//drawable
	//TODO : utile de garder en membre ?
	osg::ref_ptr<osgText::Text> _text;

};
#endif
