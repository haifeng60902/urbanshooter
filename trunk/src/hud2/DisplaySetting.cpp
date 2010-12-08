
#include <hud2/DisplaySetting.h>
#include <hud2/DisplayGeometry.h>


DisplaySetting::DisplaySetting()
{
	//default values
	_displayGeometry = new DisplayGeometry();
	_charSize = 10;
	_font = "arial.ttf";
	_textColor = osg::Vec4(0., 0., 0., 1.); //black
	_visibleTime = 2.0; //visible 2 seconds
	_backgroundTransparency = 0.5;
}

DisplaySetting::~DisplaySetting()
{
	delete _displayGeometry;
}


void DisplaySetting::setDisplayGeometry(DisplayGeometry * value) {
  _displayGeometry = value;
}

void DisplaySetting::setVisibleTime(float value) {
  _visibleTime = value;
}

void DisplaySetting::setBackgroundTransparency(float value) {
  _backgroundTransparency = value;
}

void DisplaySetting::setCharSize(int value) {
  _charSize = value;
}

void DisplaySetting::setFont(std::string value) {
  _font = value;
}

void DisplaySetting::setTextColor(osg::Vec4 value) {
  _textColor = value;
}

