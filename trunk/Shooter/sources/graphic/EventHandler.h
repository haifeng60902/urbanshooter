#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include <osgGA/GUIEventHandler>
#include <osg/Node>
#include <osgUtil/LineSegmentIntersector>

class GameEngine;

//handle the events and dispatch to other listeners
class EventHandler : public osgGA::GUIEventHandler 
{
public:

	EventHandler(GameEngine * ge);
	~EventHandler();

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	void onMouseLeftClic();
	void onMouseRightClic();

private:

	GameEngine * _ge;

	osgUtil::LineSegmentIntersector::Intersection _intersection;

};

#endif //_EVENT_HANDLER_H_
