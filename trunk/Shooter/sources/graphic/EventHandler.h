#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include <osgGA/GUIEventHandler>

//handle the events and dispatch to other listeners
class EventHandler : public osgGA::GUIEventHandler 
{
public:

	EventHandler();
	~EventHandler();

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	void onMouseLeftClic();
	void onMouseRightClic();


};

#endif //_EVENT_HANDLER_H_
