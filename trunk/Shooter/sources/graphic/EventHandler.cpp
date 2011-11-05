#include <graphic/EventHandler.h>

#include <iostream>

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

	 /*   osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
    if (!view) return false;
    
    osgViewer::ViewerBase* viewer = view->getViewerBase();
*/

 //   if (ea.getHandled()) return false;
	

    switch(ea.getEventType())
    {
	case(osgGA::GUIEventAdapter::PUSH):
	//case(osgGA::GUIEventAdapter::DOUBLECLICK):
        {


			if(ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
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
}

void EventHandler::onMouseRightClic()
{
	std::cout<<"Mouse right ! " << std::endl;
}
