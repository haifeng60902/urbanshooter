#include <graphic/EventHandler.h>

#include <osgViewer/View>

#include <iostream>
#include <game/GameEngine.h>

EventHandler::EventHandler(GameEngine * ge) : 
	_ge( ge )
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

	
    switch(ea.getEventType())
    {
	case(osgGA::GUIEventAdapter::PUSH):
	//case(osgGA::GUIEventAdapter::DOUBLECLICK):
        {


			if(ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				//reset
				_intersection.nodePath.empty();

				//compute intersection
				osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
				if(view)
				{		    
					osgUtil::LineSegmentIntersector::Intersections intersections;
					if (view->computeIntersections(1280/2, 1024/2, intersections, 0xFFFFFFFE))//shoot from the viewFinder
					{
						_intersection = *(intersections.begin());
					}
				}

				
				onMouseLeftClic();
			}

			if(ea.getButtonMask() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
			{
				onMouseRightClic();
			}
            break;
        }

    default:
        break;

    }

	return false;

}

void EventHandler::onMouseLeftClic()
{
	std::cout<<"Mouse left ! " << std::endl;
	

	//notify the game engine
	_ge->onLeftClic(_intersection);
}

void EventHandler::onMouseRightClic()
{
	std::cout<<"Mouse right ! " << std::endl;
}
