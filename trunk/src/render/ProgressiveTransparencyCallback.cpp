#include <ProgressiveTransparencyCallback.h>

#include <osg/Node>
#include <osg/StateSet>
#include <osg/Notify>

#include <Effects.h>

ProgressiveTransparencyCallback::ProgressiveTransparencyCallback(double durationVisible , double duration_blur)
{
	_duration_visible = durationVisible;
	_duration_blur = duration_blur;

	_first_traverse = false;
	_material = NULL;
}

ProgressiveTransparencyCallback::~ProgressiveTransparencyCallback()
{

}


void ProgressiveTransparencyCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{
	osg::Timer_t actual_tick = osg::Timer::instance()->tick();


	//first traverse : init start_tick
	if(!_first_traverse)
	{
		_start_tick = actual_tick;
		_first_traverse = true;

	}
	else
	{
		//when duration visible is done : start
		double duration = osg::Timer::instance()->delta_s(_start_tick , actual_tick);

		
		//End of callback duration
		if(duration >= (_duration_visible + _duration_blur))
		{
			
			Effects::setTransparency(node, 1.0);


			//auto-destruction
			traverse(node,nv);
			node->setUpdateCallback(NULL);
			return;

		}
		else if(duration >= _duration_visible)
		{
			//start blur
			double transparency = 1 - ( duration - _duration_visible ) / _duration_blur;

			Effects::setTransparency(node,transparency);
			
			
		}
		//else do nothing : let it be displayed

	}

	


    
	traverse(node,nv);
	
}