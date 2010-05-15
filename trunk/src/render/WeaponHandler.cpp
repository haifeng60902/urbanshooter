#include <WeaponHandler.h>

#include <WeaponManager.h>

#include <osg/notify>

#include <GameManager.h>


WeaponHandler::WeaponHandler()
{

}

WeaponHandler::~WeaponHandler()
{
}


bool WeaponHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
 /*   osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
    if (!view) return false;
    
    osgViewer::ViewerBase* viewer = view->getViewerBase();
*/

 //   if (ea.getHandled()) return false;
	

    switch(ea.getEventType())
    {
	case(osgGA::GUIEventAdapter::RELEASE):
	//case(osgGA::GUIEventAdapter::DOUBLECLICK):
        {
           //shoot
		//	if(ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				//if(osgGA::GUIEventAdapter::RELEASE == ea.getEventType())
				GameManager::instance()->getWeaponManager()->Tire();
			}	
            break;
        }

    default:
        break;

    }
    return false;
}
