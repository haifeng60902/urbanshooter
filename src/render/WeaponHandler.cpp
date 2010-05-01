#include <WeaponHandler.h>

#include <WeaponManager.h>

#include <osg/notify>

#include <Sniper.h>


WeaponHandler::WeaponHandler()
{
	_wm = new WeaponManager();

	//DEBUG
	_wm->setWeapon(new Sniper());
}

WeaponHandler::~WeaponHandler()
{
	delete _wm;
	_wm = NULL;
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
	case(osgGA::GUIEventAdapter::PUSH):
        {
           //shoot
			if(ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				_wm->Tire();
			}	
            break;
        }

    default:
        break;

    }
    return false;
}
