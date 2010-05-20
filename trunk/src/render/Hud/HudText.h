#ifndef _HUD_TEXT_H_
#define _HUD_TEXT_H_

#include <osg/Geode>
#include <osgText/Text>
#include <string>

/** Hud management */
namespace HudTest
{

	/** An entity of the HUD */
	class HudText : public osg::Geode
	{

	public: 
		HudText(int width, int height);
		~HudText();

		void setText(const std::string & text);

	private:
		void buildBackground();

		int _width;
		int _height;

		osg::ref_ptr<osgText::Text> _text;

	};

};

#endif //_HUD_TEXT_H_

