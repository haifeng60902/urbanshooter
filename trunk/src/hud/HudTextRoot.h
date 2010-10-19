#ifndef _HUDTEXTROOT_H_
#define _HUDTEXTROOT_H_


#include <osg/PositionAttitudeTransform>
#include <hud/HudText.h>
#include <queue>

namespace HudTest
{

	class HudTextRoot : public osg::PositionAttitudeTransform
	{
	public:
		HudTextRoot();
		~HudTextRoot();

		void addText(const std::string & text);

	private:

		osg::Vec2 _nextPos;
		std::queue<osg::ref_ptr<HudText> > _texts;

	};

};

#endif //_HUDTEXTROOT_H_
