
#include <DisplaySetting.h>
#include <DisplayGeometry.h>


DisplaySetting::DisplaySetting()
{
	//default values
	_charSize = 10;
	_font = "arial.ttf";
	_textColor = osg::Vec4(0., 0., 0., 1.); //black
	_visibleTime = 2.0; //visible 2 seconds
	_backgroundTransparency = 0.5;

	_width = 150.f;
	_height = 40.f;

	_displayGeometry = new DisplayGeometry(_width, _height);

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

void DisplaySetting::setWidth(float w){
	_width = w;
}

void DisplaySetting::setHeight(float h){
	_height = h;
}