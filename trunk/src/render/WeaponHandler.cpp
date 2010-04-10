#include <WeaponHandler.h>

#include <osg/notify>


bool WeaponHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
 /*   osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
    if (!view) return false;
    
    osgViewer::ViewerBase* viewer = view->getViewerBase();
*/

 //   if (ea.getHandled()) return false;

    switch(ea.getEventType())
    {
	case(osgGA::GUIEventAdapter::PUSH):
        {
           //shoot
			if(ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
				osg::notify(osg::ALWAYS) << "PAN !! " << std::endl; //play sound

            break;
        }

    default:
        break;

    }
    return false;
}
