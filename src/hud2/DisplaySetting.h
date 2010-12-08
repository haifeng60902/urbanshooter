#ifndef _DISPLAYSETTING_H
#define _DISPLAYSETTING_H


#include <string>
#include <osg/Vec4>

class DisplayGeometry;

/** This class represent the whole display parameters for each text in the HUD */
class DisplaySetting {
	
public:

	/** Default constructor */
	DisplaySetting();

	/** Destructor */
	~DisplaySetting();


	/** Get display geometry */
    inline DisplayGeometry * getDisplayGeometry();

	/** Set display geometry */
	void setDisplayGeometry(DisplayGeometry * value);

	/** Get visible time (in second) */
	inline const float getVisibleTime() const;

	/** Set visible time (in second) */
	void setVisibleTime(float value);

	/** Get backgroung transparency */
	inline const float getBackgroundTransparency() const;

	/** Set background transparency */
	void setBackgroundTransparency(float value);

	/** Get character size */
	inline const int getCharSize() const;

	/** Set char size */
	void setCharSize(int value);

	/** get font */
	inline const std::string getFont() const;

	/** Set font */
	void setFont(std::string value);

	/** get text color */
	inline const osg::Vec4 getTextColor() const;

	/** Set text color */
	void setTextColor(osg::Vec4 value);


private:

	int _charSize;
	int _width;
	int _height;
	std::string _font;
	osg::Vec4 _textColor;
	float _visibleTime;
	float _backgroundTransparency;
	DisplayGeometry * _displayGeometry;

};

inline DisplayGeometry * DisplaySetting::getDisplayGeometry() {
  return _displayGeometry;
}

inline const float DisplaySetting::getVisibleTime() const {
  return _visibleTime;
}

inline const float DisplaySetting::getBackgroundTransparency() const {
  return _backgroundTransparency;
}

inline const int DisplaySetting::getCharSize() const {
  return _charSize;
}

inline const std::string DisplaySetting::getFont() const {
  return _font;
}

inline const osg::Vec4 DisplaySetting::getTextColor() const {
  return _textColor;
}

#endif
