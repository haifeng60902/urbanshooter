#include <graphic/FPSManipulator.h>

#include <iostream>


FPSManipulator::FPSManipulator()
{
	_center = osg::Vec3(50,0,5);
	_rotation = osg::Quat();

	home(0.);
}


FPSManipulator::~FPSManipulator()
{

}



void FPSManipulator::home(double /*currentTime*/)
{

	computePosition( osg::Vec3(50,0,5),  osg::Vec3(0,0,5), osg::Z_AXIS);

}


void FPSManipulator::setByMatrix(const osg::Matrixd& matrix)
{
   
}

osg::Matrixd FPSManipulator::getMatrix() const
{
    return /*osg::Matrixd::translate(0.0,0.0,_distance)**/osg::Matrixd::rotate(_rotation)*osg::Matrixd::translate(_center);
}

osg::Matrixd FPSManipulator::getInverseMatrix() const
{
    return osg::Matrixd::translate(-_center)*osg::Matrixd::rotate(_rotation.inverse())/**osg::Matrixd::translate(0.0,0.0,-_distance)*/;
}


void FPSManipulator::computePosition(const osg::Vec3& eye,const osg::Vec3& center,const osg::Vec3& up)
{

    osg::Vec3 lv(center-eye);

    osg::Vec3 f(lv);
    f.normalize();
    osg::Vec3 s(f^up);
    s.normalize();
    osg::Vec3 u(s^f);
    u.normalize();
    
    osg::Matrix rotation_matrix(s[0],     u[0],     -f[0],     0.0f,
                                s[1],     u[1],     -f[1],     0.0f,
                                s[2],     u[2],     -f[2],     0.0f,
                                0.0f,     0.0f,     0.0f,      1.0f);
                   
    _center = eye;
    //_distance = lv.length();
    _rotation = rotation_matrix.getRotate().inverse();
}

void FPSManipulator::addMouseEvent(const osgGA::GUIEventAdapter& ea)
{
    _ga_t1 = _ga_t0;
    _ga_t0 = &ea;
}


void FPSManipulator::flushMouseEventStack()
{
    _ga_t1 = NULL;
    _ga_t0 = NULL;
}

void FPSManipulator::init(const osgGA::GUIEventAdapter& ,osgGA::GUIActionAdapter& )
{
    flushMouseEventStack();
}




bool FPSManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
{
   /* switch(ea.getEventType())
    {
        case(GUIEventAdapter::FRAME):
            if (_thrown)
            {
                if (calcMovement()) us.requestRedraw();
            }
            return false;
        default:
            break;
    }*/

    if (ea.getHandled()) return false;

    switch(ea.getEventType())
    {
		//if a key is pressed flush the previous states
       /* case(GUIEventAdapter::PUSH):
        {
            flushMouseEventStack();
            addMouseEvent(ea);
           
            return true;
        }

        case(GUIEventAdapter::RELEASE):
        {
            if (ea.getButtonMask()==0)
            {
            
                double timeSinceLastRecordEvent = _ga_t0.valid() ? (ea.getTime() - _ga_t0->getTime()) : DBL_MAX;
                if (timeSinceLastRecordEvent>0.02) flushMouseEventStack();

                calcMovement();
                 

            }
            else
            {
                flushMouseEventStack();
                addMouseEvent(ea);

            }
            return true;
        }*/

     /*   case(GUIEventAdapter::DRAG):
        {
            addMouseEvent(ea);
            if (calcMovement()) us.requestRedraw();
            us.requestContinuousUpdate(false);
            _thrown = false;
            return true;
        }*/

       /* case(GUIEventAdapter::MOVE):
        {
            return false;
        }*/

        case(osgGA::GUIEventAdapter::KEYDOWN):
            if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Space) //home on space bar
            {
                flushMouseEventStack();

                home(0.);

                return true;
            }
            return false;

        case(osgGA::GUIEventAdapter::FRAME):
			{
                addMouseEvent(ea);

				calcMovement();
			}
				return false;
        default:
            return false;
    }
}




bool FPSManipulator::calcMovement()
{
    // return if less then two events have been added.
    if (_ga_t0.get()==NULL || _ga_t1.get()==NULL) return false;

    float dx = _ga_t0->getXnormalized()-_ga_t1->getXnormalized();
    float dy = _ga_t0->getYnormalized()-_ga_t1->getYnormalized();

    float distance = sqrtf(dx*dx + dy*dy);
   
    
    // return if there is no movement.
    if (distance==0.0f)
    {
        return false;
    }

  //  unsigned int buttonMask = _ga_t1->getButtonMask();
  //  if (buttonMask==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)//pk for test, to be removed after
    {

        // rotate camera.

        float px0 = _ga_t0->getXnormalized();
        float py0 = _ga_t0->getYnormalized();
											
        float px1 = _ga_t1->getXnormalized();
        float py1 = _ga_t1->getYnormalized();
        
		//test the border to reset the position
		if(px0>0.9 || px0<-0.9 || py0>0.9 || py0<-0.9)
		{
			_gw->requestWarpPointer((_ga_t0->getXmax() - _ga_t0->getXmin())/2,(_ga_t0->getYmax() - _ga_t0->getYmin())/2);
			flushMouseEventStack(); //rest to avoid big move
		}

		double speed = 50.0;


		//horizontal rotation
		osg::Quat qh(osg::DegreesToRadians((px1-px0)*speed), osg::Z_AXIS);


		//vertical rotation
			//rotation axis //here axis is more complex

		osg::Vec3d geteye, getcenter, getup;
		getInverseMatrix().getLookAt(geteye, getcenter, getup);

		osg::Vec3d front = getcenter - geteye;
		front.normalize();
		osg::Vec3d axis = front ^ osg::Z_AXIS;
		axis.normalize();

		//test and stop the vertical rotation
		double scalar = front * osg::Z_AXIS;
		osg::Quat qv;

		qv = osg::Quat(osg::DegreesToRadians((py0-py1)*speed), axis);

		if((scalar > 0.9 && py0 > py1 ) || (scalar < -0.9 && py0 < py1 )) //going up or down near vertical axis
		{
			qv = osg::Quat(-osg::DegreesToRadians((py0-py1)*speed), axis); //inverse rotation
		}
		



        _rotation = _rotation*qv*qh;


        return true;

    }
  /*  else if (buttonMask==GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
        buttonMask==(GUIEventAdapter::LEFT_MOUSE_BUTTON|GUIEventAdapter::RIGHT_MOUSE_BUTTON))
    {

        // pan model.

        float scale = -0.3f*_distance;

        osg::Matrix rotation_matrix;
        rotation_matrix.makeRotate(_rotation);

        osg::Vec3 dv(dx*scale,dy*scale,0.0f);

        _center += dv*rotation_matrix;
        
        return true;

    }
    else if (buttonMask==GUIEventAdapter::RIGHT_MOUSE_BUTTON)
    {

        // zoom model.

        float fd = _distance;
        float scale = 1.0f+dy;
        if (fd*scale>_modelScale*_minimumZoomScale)
        {

            _distance *= scale;

        }
        else
        {

            // notify(DEBUG_INFO) << "Pushing forward"<<std::endl;
            // push the camera forward.
            float scale = -fd;

            osg::Matrix rotation_matrix(_rotation);

            osg::Vec3 dv = (osg::Vec3(0.0f,0.0f,-1.0f)*rotation_matrix)*(dy*scale);

            _center += dv;

        }

        return true;

    }*/

    return false;
}
